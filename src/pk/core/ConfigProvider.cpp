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
#include "m_config.hpp"
#include <cstdlib>
#include <fstream>
#include <json/json.h>

namespace Pk {
    ConfigProvider::ConfigProvider(const std::string &token, const std::string &config_file,
                                   std::unique_ptr<std::string> config_dir)
        : token(token), config_file(config_file), config_dir(std::move(config_dir)) {
    }

    char *ConfigProvider::get_env_value(const std::string &key) {
        char *value = nullptr;
        size_t size = 0;

        if (_dupenv_s(&value, &size, key.c_str()) == 0 && value != nullptr) {
            return value; // Caller must free this memory
        }

        return nullptr;
    }

    void ConfigProvider::set_token(const std::string &new_token) {
        token = new_token;
    }

    void ConfigProvider::set_config_dir(const std::string &new_config_dir) {
        config_dir = std::make_unique<std::string>(new_config_dir);
    }

    // Load configuration from a JSON file
    bool ConfigProvider::load_config(const std::string &file_path) {
        std::ifstream config_file(file_path, std::ifstream::binary);
        if (!config_file.is_open()) {
            return false; // Error: Cannot open config file
        }

        Json::Value root;
        Json::CharReaderBuilder reader;
        std::string errs;

        if (!Json::parseFromStream(reader, config_file, &root, &errs)) {
            return false; // Error parsing JSON
        }

        if (root.isMember("token")) {
            token = root["token"].asString();
        }
        if (root.isMember("config_dir")) {
            config_dir = std::make_unique<std::string>(root["config_dir"].asString());
        }

        return true;
    }

    // Save configuration to a JSON file
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
