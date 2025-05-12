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
    PkFramework::PkFramework()
        : config(make_unique<ConfigProvider>()) {
#ifdef WIN32
        const filesystem::path appdata = ConfigProvider::get_env_value("APPDATA");
#else
        const filesystem::path appdata = ConfigProvider::get_env_value("HOME");
#endif // WIN32

        const filesystem::path &wdir = "pakagify";

        if (appdata.empty()) {
            std::cout << "Fail: Cannot access to appdir :/" << std::endl;
            exit(-1);
        }

        config->set_config_dir(filesystem::path(appdata / wdir).string());
        const std::string *dir = config->get_config_dir();

        std::cout << "Application data: " << *dir << std::endl;
    }
}
