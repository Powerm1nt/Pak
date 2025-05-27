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

#ifndef Pak_LIBRARY_H
#define Pak_LIBRARY_H

#include <sqlite3.h>

#include "helper_cli.hpp"
#include "m_config.hpp"
#include "m_repository.hpp"
#include "m_package.hpp"
#include "pak_file.hpp"
#include "utils.hpp"

namespace Pk {
    class Pak {
        std::unique_ptr<ConfigProvider> config;

    public:
        Pak();

        ~Pak() = default;

        static bool build_package(
            const std::string &image_path,
            const std::string &pkg_dir,
            Package &package,
            const Repository &repository
        );

    private:
        static std::vector<char> build_package_db(Package &package,
                                                  const Repository &repository
        );

        static void init_metadata_db(sqlite3 *db);

        static void add_repository_db(sqlite3 *db, const Repository &repository);

        static void add_files_of_package_db(sqlite3 *db, Package &package);

        static std::vector<std::vector<char> > build_package_body
        (
            PakFile &header,
            const std::string &pkg_dir,
            const std::vector<std::string> &file_list, uint32_t alignment, Package &package
        );

        static void calculate_header_sizes
        (
            PakFile &header,
            uint64_t size,
            uint64_t compressed_size,
            uint64_t metadata_size
        );
    };
}

#endif //Pak_LIBRARY_H
