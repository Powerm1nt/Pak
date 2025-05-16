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

#include "m_config.hpp"

namespace Pk {
	PkFramework::PkFramework() : config(std::make_unique<ConfigProvider>()) {
#ifdef WIN32
		const std::filesystem::path appdata =
			ConfigProvider::get_env_value("APPDATA");
#else
		const filesystem::path appdata = ConfigProvider::get_env_value("HOME");
#endif  // WIN32

		const std::filesystem::path& wdir = "pakagify";
		const  std::filesystem::path& app_path(appdata / wdir);

		if (appdata.empty()) {
			std::cerr << "Fail: Cannot access to appdir :/" << std::endl;
			exit(-1);
		}

		try {
			config->set_config_dir(app_path.string());
			config->init_config_dir();
		}
		catch (const std::exception& e) {
			std::cerr << "Critical: Failed to initialize config directory: " << e.what()
				<< std::endl;

			exit(EXIT_FAILURE);
		}

		try {
			if (config->load_config(std::filesystem::path(app_path / "pkcli.json").string())) {
				const std::string& dec_token = Utils::decodeToken(config->get_token());
				std::cout << dec_token << std::endl;
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Critical: Failed to load config file: " << e.what() << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}  // namespace Pk
