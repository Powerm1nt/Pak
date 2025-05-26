/**
 * Pakagify, PkFramework, PkCli
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

#include "PkFramework.hpp"

#include <filesystem>
#include <iostream>

#include <sqlite3.h>

#include "database.hpp"
#include "m_config.hpp"
#include "m_file.hpp"
#include "pak_file.hpp"

namespace Pk {
	PkFramework::PkFramework() : config(std::make_unique<ConfigProvider>()) {
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

	std::vector<char> PkFramework::build_package_db
	(
		const std::string &filename,
		const std::vector<Package *> &packages,
		const std::vector<Repository *> &repositories
	) {
		sqlite3 *db = nullptr;

		if (const int req = sqlite3_open(":memory:", &db); req != SQLITE_OK) {
			const std::string req_err = sqlite3_errmsg(db);
			sqlite3_close(db);
			throw std::runtime_error("Critical: Failed to open database: " + req_err);
		}

		try {
			init_metadata_db(db);
			add_repositories_db(db, repositories);
			add_packages_and_files_db(db, packages);
		} catch (std::exception &error) {
			std::cerr << "Critical: Failed to do transactions: " << error.what() << std::endl;
			sqlite3_close(db);
			throw;
		}

		// Output the database data to a vector
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

	void PkFramework::init_metadata_db(sqlite3 *db) {
		SQLiteTransaction transaction(db);
		transaction.execute(pak_initial_sql);
	}

	void PkFramework::add_repositories_db(sqlite3 *db, const std::vector<Repository *> &repositories) {
		SQLiteTransaction transaction(db);

		for (const Repository *repo: repositories) {
			transaction.execute(repo->toSQL());
		}
	}

	void PkFramework::add_packages_and_files_db(sqlite3 *db, const std::vector<Package *> &packages) {
		SQLiteTransaction transaction(db);

		for (const Package *package: packages) {
			transaction.execute(package->toSQL());

			std::string files_sql;
			for (const File &file: package->get_files()) {
				files_sql += file.toSQL() + "; ";
			}

			if (!files_sql.empty()) {
				transaction.execute(files_sql);
			}
		}
	}


	void PkFramework::build_package_body(std::string &filename, std::vector<int> &payload) {
	}

	PakFile PkFramework::build_package_header(
		const uint16_t &version,
		const uint32_t &metadata_size,
		const uint64_t &body_size,
		const uint64_t &total_size,
		const uint64_t &body_compressed_size,
		const uint64_t &body_decompressed_size
	) {
		return {
			.magic = 0x50414B, // "PAK"
			.version = version,
			.header_size = sizeof(PakFile),
			.metadata_size = metadata_size,
			.body_size = body_size,
			.total_size = total_size,
			.body_compressed_size = body_compressed_size,
			.body_decompressed_size = body_decompressed_size
		};
	}

	bool PkFramework::build_package(std::string &filename, uint &repo_id, std::string &repo_folder) {
		return true;
	}
} // namespace Pk
