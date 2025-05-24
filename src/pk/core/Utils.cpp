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

#include <algorithm>
#include <utils.hpp>

#include <iostream>
#include <filesystem>
#include <vector>
#include <chrono>
#include <iomanip>

#include <cppcodec/base64_rfc4648.hpp>

namespace Utils {
    namespace fs = std::filesystem;

    std::vector<std::string> listFilesRecursively(
        const std::string &parent,
        const std::vector<std::string> &directories
    ) {
        std::vector<std::string> fileList;

        for (const auto &element: directories) {
            if (
                fs::path fullPath = fs::path(parent) / element;
                fs::is_directory(fullPath)
            ) {
                for (const auto &entry: fs::recursive_directory_iterator(fullPath)) {
                    if (fs::is_regular_file(entry.path())) {
                        fileList.push_back(entry.path().string());
                    }
                }
            } else if (fs::is_regular_file(fullPath)) {
                fileList.push_back(fullPath.string());
            }
        }

        return fileList;
    }

    std::string calculateBitrate(const size_t &bytesDownloaded, const double &downloadTimeSeconds) {
        const double bytesPerSecond = bytesDownloaded / downloadTimeSeconds;
        const double megabytesPerSecond = bytesPerSecond / (1024.0 * 1024.0);

        std::string unit = "B/s";
        double bitrate = bytesPerSecond;

        if (megabytesPerSecond >= 1) {
            unit = "MB/s";
            bitrate = megabytesPerSecond;
        } else if (bytesPerSecond >= 1024) {
            unit = "KB/s";
            bitrate = bytesPerSecond / 1024.0;
        }

        return std::to_string(bitrate) + " " + unit;
    }

    std::string formatTime(const int &seconds) {
        const int hours = seconds / 3600;
        const int minutes = seconds % 3600 / 60;
        const int remainingSeconds = seconds % 60;

        std::ostringstream formattedTime;
        formattedTime << std::setw(2) << std::setfill('0') << hours << ":"
                << std::setw(2) << std::setfill('0') << minutes << ":"
                << std::setw(2) << std::setfill('0') << remainingSeconds;
        return formattedTime.str();
    }

    std::string decodeToken(const std::string &token) {
        try {
            std::vector<unsigned char> decodedTok = cppcodec::base64_rfc4648::decode(token);
            return std::string(decodedTok.begin(), decodedTok.end());
        } catch (const std::exception &e) {
            std::cerr << "Error decoding Base64: " << e.what() << std::endl;
            return "";
        }
    }


    bool validateArch(const std::string &arch) {
        std::vector<std::string> validArchitectures = {"x86", "x64", "armv7", "arm64", "noarch"};
        if (std::ranges::find(validArchitectures, arch) == validArchitectures.end()) {
            std::cerr << "Error: Invalid architecture." << std::endl;
            return false;
        }
        return true;
    }

    bool validatePlatform(const std::string &platform) {
        if (std::vector<std::string> validPlatforms = {"linux", "windows", "win32", "darwin", "any"};
            std::ranges::find(validPlatforms, platform) == validPlatforms.end()) {
            std::cerr << "Error: Invalid platform." << std::endl;
            return false;
        }
        return true;
    }
}
