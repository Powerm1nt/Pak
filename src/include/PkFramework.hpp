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

#ifndef PKFRAMEWORK_LIBRARY_H
#define PKFRAMEWORK_LIBRARY_H

#include <sqlite3.h>

#include "helper_cli.hpp"
#include "m_config.hpp"
#include "m_repository.hpp"
#include "m_package.hpp"
#include "pak_file.hpp"
#include "utils.hpp"

namespace Pk {
    class PkFramework {
        std::unique_ptr<ConfigProvider> config;

    public:
        PkFramework();

        ~PkFramework() = default;

        static bool build_package(std::string &filename, uint &repo_id, std::string &repo_folder);

    private:
        static PakFile build_package_header(
            const uint16_t &version,
            const uint32_t &metadata_size,
            const uint64_t &body_size,
            const uint64_t &total_size,
            const uint64_t &body_compressed_size,
            const uint64_t &body_decompressed_size
        );

        static std::vector<char> build_package_db(const std::string &filename, const std::vector<Package *> &packages,
                                                  const std::vector<Repository *> &repositories);

        static void init_metadata_db(sqlite3 *db);

        static void add_repositories_db(sqlite3 *db, const std::vector<Repository *> &repositories);

        static void add_packages_and_files_db(sqlite3 *db, const std::vector<Package *> &packages);

        static void build_package_body(std::string &filename, std::vector<int> &payload);
    };
}

#endif //PKFRAMEWORK_LIBRARY_H
