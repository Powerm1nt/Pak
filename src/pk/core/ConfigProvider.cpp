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
    using namespace std;

    string ConfigProvider::get_env_value(const string &key) {
        char *value = nullptr;
        size_t size = 0;

        if (_dupenv_s(&value, &size, key.c_str()) == 0 && value != nullptr) {
            string result(value);
            free(value);
            return result;
        }

        return "";
    }

    void ConfigProvider::set_token(const string &new_token) {
        token = new_token;
    }

    void ConfigProvider::set_config_dir(const string &new_config_dir) {
        config_dir = make_unique<string>(new_config_dir);
    }

    bool ConfigProvider::load_config(const string &file_path) {
        ifstream config_file(file_path, ifstream::binary);
        if (!config_file.is_open()) {
            return false; // Error: Cannot open config file
        }

        Json::Value root;
        Json::CharReaderBuilder reader;
        string errs;

        if (!Json::parseFromStream(reader, config_file, &root, &errs)) {
            return false; // Error parsing JSON
        }

        if (root.isMember("token")) {
            token = root["token"].asString();
        }
        if (root.isMember("config_dir")) {
            config_dir = make_unique<string>(root["config_dir"].asString());
        }

        return true;
    }

    bool ConfigProvider::save_config(const string &file_path) const {
        Json::Value root;
        root["token"] = token;
        if (config_dir) {
            root["config_dir"] = *config_dir;
        }

        ofstream config_file(file_path, ofstream::binary);
        if (!config_file.is_open()) {
            return false; // Error: Cannot open config file for writing
        }

        Json::StreamWriterBuilder writer;
        config_file << Json::writeString(writer, root);

        return true;
    }
} // namespace Pk
