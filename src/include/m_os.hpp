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

#ifndef M_OS_HPP
#define M_OS_HPP

#include <string>
#include <unordered_map>

namespace Platforms {
    enum Arch {
        x86,
        x86_64,
        aarch64,
        noarch
    };

    enum Platform {
        Windows,
        Linux,
        Unix,
        Darwin,
        Unknown,
        Any
    };

    const std::unordered_map<Arch, std::string> archToString = {
        {x86, "x86"},
        {x86_64, "x64"},
        {aarch64, "arm64"},
        {noarch, "noarch"}
    };

    const std::unordered_map<Platform, std::string> platformToString = {
        {Windows, "windows"},
        {Linux, "linux"},
        {Unix, "unix"},
        {Darwin, "darwin"},
        {Unknown, "unknown"},
        {Any, "any"}
    };

    inline std::string get_arch(const Arch &arch) {
        return archToString.at(arch);
    }

    inline std::string get_platform(const Platform &platform) {
        return platformToString.at(platform);
    }
}

#endif //M_OS_HPP
