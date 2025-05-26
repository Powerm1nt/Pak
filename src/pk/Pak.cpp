/**
 * Pakagify, Pak, PkCli
 * Copyright (C) 2025 NukaWorks
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Pak.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>

#include <sqlite3.h>

#include "database.hpp"
#include "fileutils.hpp"
#include "m_config.hpp"
#include "m_file.hpp"
#include "pak_file.hpp"

namespace Pk {
	Pak::Pak() : config(std::make_unique<ConfigProvider>()) {
#ifdef WIN32
		const std::filesystem::path appdata =
			ConfigProvider::get_env_value("APPDATA");
#else
		const std::filesystem::path appdata = ConfigProvider::get_env_value("HOME");
#endif  // WIN32

		const std::filesystem::path &wdir = "pakagify";
		const std::filesystem::path &app_path(appdata / wdir);

		if (appdata.empty()) {
			std::cerr << "Fail: Cannot access to appdir :/" << std::endl;
			exit(EXIT_FAILURE);
		}

		try {
			config->set_config_dir(app_path.string());
			if (!config->init_config_dir())
				throw std::runtime_error("Fail: Cannot read config dir");
		} catch (const std::exception &e) {
			std::cerr << "Critical: Failed to initialize config directory: " << e.what()
					<< std::endl;

			exit(EXIT_FAILURE);
		}

		try {
			if (config->load_config(std::filesystem::path(app_path / "pkcli.json").string())) {
				const std::string &dec_token = Utils::decodeToken(config->get_token());
				std::cout << dec_token << std::endl;
			}
		} catch (const std::exception &e) {
			std::cerr << "Critical: Failed to load config file: " << e.what() << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	std::vector<char> Pak::build_package_db
	(
		const std::unique_ptr<Package> &package,
		const std::unique_ptr<Repository> &repository
	) {
		sqlite3 *db = nullptr;

		if (const int req = sqlite3_open(":memory:", &db); req != SQLITE_OK) {
			const std::string req_err = sqlite3_errmsg(db);
			sqlite3_close(db);
			throw std::runtime_error("Critical: Failed to open database: " + req_err);
		}

		try {
			init_metadata_db(db);
			add_repository_db(db, repository);
			add_files_of_package_db(db, package);
		} catch (std::exception &error) {
			std::cerr << "Critical: Failed to do transactions: " << error.what() << std::endl;
			sqlite3_close(db);
			throw;
		}

		// Output the database
		sqlite3_int64 size;
		void *db_data = sqlite3_serialize(db, "main", &size, 0);
		if (!db_data) {
			sqlite3_close(db);
			throw std::runtime_error("Failed to serialize SQLite database");
		}

		std::vector db_buffer(static_cast<char *>(db_data), static_cast<char *>(db_data) + size);

		sqlite3_free(db_data);
		sqlite3_close(db);
		return db_buffer;
	}

	void Pak::init_metadata_db(sqlite3 *db) {
		SQLiteTransaction transaction(db);
		transaction.execute(pak_initial_sql);
	}

	void Pak::add_repository_db
	(
		sqlite3 *db,
		const std::unique_ptr<Repository> &repository
	) {
		SQLiteTransaction transaction(db);
		transaction.execute(repository->toSQL());
	}

	void Pak::add_files_of_package_db(
		sqlite3 *db,
		const std::unique_ptr<Package> &package
	) {
		SQLiteTransaction transaction(db);

		transaction.execute(package->toSQL());

		std::string files_sql;
		for (const File &file: package->get_files()) {
			files_sql += file.toSQL() + "; ";
		}

		if (!files_sql.empty()) {
			transaction.execute(files_sql);
		}
	}

	std::vector<char> Pak::build_package_body
	(
		PakFile &header,
		std::vector<std::unique_ptr<File> > &pak_files,
		const std::string &pkg_dir,
		const std::vector<std::string> &file_list,
		const std::unique_ptr<Package> &package
	) {
		std::vector<char> body = {};

		for (const std::string &fpath: file_list) {
			try {
				uint64_t pNum = 0;
				constexpr u_int32_t alignment = 4;
				std::string fname = fpath.substr(pkg_dir.size() + 1);

				std::vector<char> file = read_file(fpath);
				std::vector<char> zFile = compress_data(file);
				uLong crc32 = compute_crc32(zFile);

				body.insert(body.end(), zFile.begin(), zFile.end());

				const uint32_t padding = (alignment - zFile.size() % alignment) % alignment;

				uint64_t size = file.size();
				uint64_t compressed_size = zFile.size();
				uint64_t offset_start = body.size();
				uint64_t offset_end = offset_start + compressed_size + padding;

				// File chunks are not implemented for now.
				uint64_t chunk_size = compressed_size + padding;
				uint32_t chunk_count = 1;

				uint32_t attributes = static_cast<uint32_t>(std::filesystem::status(fpath).permissions());

				uint64_t last_updated = std::filesystem::last_write_time(fpath).time_since_epoch().count();
				uint64_t created_at = std::filesystem::last_write_time(fpath).time_since_epoch().count();

				// FIXME: We need to use some another link solution link a littleUUID
				// uint64_t pNum = 0;
				// uint64_t repository = 0;

				auto new_file = std::make_unique<File>(
					fname,
					fpath,
					"",
					std::to_string(crc32),
					size,
					compressed_size,
					offset_start,
					offset_end,
					chunk_size,
					chunk_count,
					attributes,
					last_updated,
					created_at,
					pNum
				);

				pak_files.push_back(std::move(new_file));

				// We recalculate the computed size into the header
				calculate_header_sizes(header, size, compressed_size, header.metadata_size);
				pNum++;
			} catch (std::exception &error) {
				std::cerr << "Critical: Failed to read file: " << error.what() << std::endl;
				throw;
			}
		}

		return body;
	}

	void Pak::calculate_header_sizes
	(
		PakFile &header,
		const uint64_t size,
		const uint64_t compressed_size,
		const uint64_t metadata_size
	) {
		header.body_compressed_size += compressed_size;
		header.body_decompressed_size += size;
		header.metadata_size = metadata_size;
		header.total_size = header.header_size + header.metadata_size;
		header.header_size = sizeof(PakFile);
	}

	bool Pak::build_package
	(
		const std::string &image_path,
		const std::string &pkg_dir,
		const std::unique_ptr<Package> &package,
		const std::unique_ptr<Repository> &repository
	) {
		PakFile headerObj = {
			.magic = 0x50414B, // "PAK"
			.version = 1,
			.header_size = sizeof(PakFile),
			.metadata_size = 0,
			.total_size = 0,
			.body_compressed_size = 0,
			.body_decompressed_size = 0
		};

		PakFile &header = headerObj;

		std::ofstream pak_file(image_path, std::ios::binary);
		// const u_int32_t header_size = sizeof(PakFile);
		// const u_int32_t alignment = 4;


		if (!pak_file.is_open()) {
			throw std::runtime_error("Cannot open file: " + image_path);
		}

		const std::vector<std::string> file_list = Utils::listFilesRecursively(pkg_dir);
		std::vector<std::unique_ptr<File> > pak_files = {};

		const std::vector<char> metadata = build_package_db(package, repository);
		const std::vector<char> body = build_package_body(header, pak_files, pkg_dir, file_list, package);

		calculate_header_sizes(header, header.total_size, header.body_compressed_size, metadata.size());

		pak_file.write(reinterpret_cast<const char *>(&header), sizeof(PakFile));
		if (!pak_file)
			throw std::runtime_error("Cannot write to file: " + image_path);

		pak_file.write(metadata.data(), metadata.size());
		if (!pak_file)
			throw std::runtime_error("Cannot write to file: " + image_path);

		pak_file.write(body.data(), body.size());
		if (!pak_file)
			throw std::runtime_error("Cannot write to file: " + image_path);

		pak_file.flush();
		pak_file.close();
		return true;
	}
} // namespace Pk
