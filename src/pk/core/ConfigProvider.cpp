/*
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
#include <json/json.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "m_config.hpp"
#include "utils.hpp"

namespace Pk {
	std::string ConfigProvider::get_env_value(const std::string &key) {
#ifdef WIN32
		char* value = nullptr;
		size_t size = 0;

		if (_dupenv_s(&value, &size, key.c_str()) == 0 && value != nullptr) {
			std::string result(value);
			free(value);
			return result;
		}
#else
		if (const char *value = secure_getenv(key.c_str()); value != nullptr) {
			return value;
		}
#endif
		return "";
	}

	void ConfigProvider::set_token(const std::string &new_token) {
		token = new_token;
	}

	void ConfigProvider::set_config_dir(const std::string &new_config_dir) {
		config_dir = make_unique<std::string>(new_config_dir);
	}

	bool ConfigProvider::init_config_dir() {
		if (!config_dir || config_dir->empty()) {
			throw std::runtime_error("Configuration directory is invalid or missing");
		}

		if (!std::filesystem::create_directory(config_dir->c_str()) && errno != EEXIST) {
			std::cout << "Configuration directory is empty, using default."
					<< std::endl;
			return false; // Directory already exists
		}

		return true;
	}

	bool ConfigProvider::load_config(const std::string &file_path) {
		Json::Value root;
		std::string errors;

		std::ifstream config_file(file_path, std::ifstream::binary);

		// We create a new file with a fresh new config if empty
		if (
			Json::CharReaderBuilder reader;
			!config_file.is_open() || Utils::fileSize(file_path.c_str()) == 0 ||
			!Json::parseFromStream(reader, config_file, &root, &errors) || root.empty()) {
			root["token"] = "";
			root["config_dir"] = "";

			Json::StreamWriterBuilder builder;

			std::ofstream new_config_file(file_path, std::ios::binary);

			new_config_file << Json::writeString(builder, root);
		}

		if (root.empty()) {
			std::cout << "Config is empty" << std::endl;
		}

		if (root.isMember("token")) {
			token = root["token"].asString();
		}
		if (root.isMember("config_dir")) {
			config_dir = make_unique<std::string>(root["config_dir"].asString());
		}

		return true;
	}

	bool ConfigProvider::save_config(const std::string &file_path) const {
		Json::Value root;
		root["token"] = token;
		if (config_dir) {
			root["config_dir"] = *config_dir;
		}

		std::ofstream config_file(file_path, std::ofstream::binary);
		if (!config_file.is_open()) {
			return false; // Error: Cannot open config file for writing
		}

		Json::StreamWriterBuilder writer;
		config_file << Json::writeString(writer, root);

		return true;
	}
} // namespace Pk
