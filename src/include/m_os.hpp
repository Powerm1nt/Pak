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

namespace Platforms {
    enum arch {
        x86,
        x86_64,
        aarch64,
        noarch
    };

    enum platform {
        windows,
        linux,
        unix,
        darwin,
        unknown,
        any
    };

    // TODO: use unordered_map to conv platform to string
    std::string get_platform(platform &platform);

    std::string get_arch(arch &arch);
}

#endif //M_OS_HPP
