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

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

namespace Utils {
    std::vector<std::string> listFilesRecursively(const std::string &parent,
                                                  const std::vector<std::string> &directories);

    std::string calculateBitrate(const size_t &bytesDownloaded, const double &downloadTimeSeconds);

    std::string formatTime(const int &seconds);

    std::string decodeToken(const std::string &token);

    bool validateArch(const std::string &arch);

    bool validatePlatform(const std::string &platform);

    inline std::streampos fileSize(const char *filePath) {
        std::streampos fsize = 0;
        std::ifstream file(filePath, std::ios::binary);

        fsize = file.tellg();
        file.seekg(0, std::ios::end);
        fsize = file.tellg() - fsize;
        file.close();

        return fsize;
    }
}


#endif //UTILS_HPP
