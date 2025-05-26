/*
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

#include <sqlite3.h>
#include <utility>

#include "m_repository.hpp"

namespace Pk {
    Repository::Repository(
        std::string name,
        std::string description,
        std::string author,
        std::string url,

        uint64_t last_updated,
        uint64_t created_at,

        const std::vector<Package *> &packages
    )
        : name(std::move(name)),
          description(std::move(description)),
          author(std::move(author)),
          url(std::move(url)),
          last_updated(std::move(last_updated)),
          created_at(std::move(created_at)),
          packages(packages) {
    }

    std::string Repository::toSQL() const {
        char *sql_raw = sqlite3_mprintf(
            "INSERT INTO repositories (name, description, author, url, last_updated, created_at) "
            "VALUES ('%q', '%q', '%q', '%q', %lld, %lld);",
            name.c_str(),
            description.c_str(),
            author.c_str(),
            url.c_str(),
            last_updated,
            created_at
        );

        std::string sql(sql_raw);
        sqlite3_free(sql_raw);

        return sql;
    }

    Repository::~Repository() = default;
} // namespace Pk
