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

//
// Created by Powerm1nt on 26/05/2025.
//

#ifndef M_FILE_HPP
#define M_FILE_HPP
#include <string>

#include "m_object.hpp"

namespace Pak {
    class File : public Object {
    public:
        File(
            std::string filename,
            std::string path,
            std::string symlink_path,

            uint32_t attributes,

            uint64_t package_id
        );

        ~File();

        [[nodiscard]] std::string toSQL() const;

        [[nodiscard]] const std::string &get_filename() const { return filename; }
        [[nodiscard]] const std::string &get_path() const { return path; }
        [[nodiscard]] const std::string &get_symlink_path() const { return symlink_path; }

        [[nodiscard]] uint32_t get_attributes() const { return attributes; }
        [[nodiscard]] uint64_t get_package_id() const { return package_id; }

    private:
        std::string filename;
        std::string path;
        std::string symlink_path;

        uint32_t attributes;

        uint64_t package_id;
    };
}

#endif //M_FILE_HPP
