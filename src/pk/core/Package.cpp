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

#include <sqlite3.h>
#include <utility>

#include "m_package.hpp"

namespace Pk {
    Package::Package(
        std::string name,
        std::string version,
        std::string description,
        std::string author,
        std::string last_updated,
        std::string created_at,
        std::string install_location,
        std::string license,

        uint repository,

        const Platforms::Arch &arch,
        const Platforms::Platform &platform,

        const std::vector<File> &files
    )
        : name(std::move(name)),
          version(std::move(version)),
          description(std::move(description)),
          author(std::move(author)),
          last_updated(std::move(last_updated)),
          created_at(std::move(created_at)),
          install_location(std::move(install_location)),
          license(std::move(license)),
          arch(arch),
          platform(platform),
          repository(std::move(repository)),
          files(files) {
    }

    Package::~Package() = default;

    std::string Package::toSQL() const {
        char *sql_raw = sqlite3_mprintf(
            "INSERT INTO packages (name, version, description, author, install_location, license, arch, platform, last_updated, created_at, repository) "
            "VALUES ('%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', %lld, %lld, %lld);",
            name.c_str(),
            version.c_str(),
            description.c_str(),
            author.c_str(),
            install_location.c_str(),
            license.c_str(),
            Platforms::archToString.at(arch).c_str(),
            Platforms::platformToString.at(platform).c_str(),
            last_updated,
            created_at,
            repository
        );

        std::string sql(sql_raw);
        sqlite3_free(sql_raw);

        return sql;
    }

} // namespace Pk
