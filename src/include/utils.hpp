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

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

namespace Utils {
    std::vector<std::string> listFilesRecursively(const std::string &source);

    std::string calculateBitrate(const double &bytesDownloaded, const double &downloadTimeSeconds);

    std::string formatTime(const int &seconds);

    std::string decodeToken(const std::string &token);

    bool validateArch(const std::string &arch);

    bool validatePlatform(const std::string &platform);
}


#endif //UTILS_HPP
