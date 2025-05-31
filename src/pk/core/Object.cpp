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
// Created by powerm1nt on 5/29/25.
//

#include <sqlite3.h>

#include "m_object.hpp"

namespace Pak {
    Object::Object(
        const uint64_t object_id,
        const uint64_t size,
        const uint64_t z_size,
        const uint64_t last_updated,
        const uint64_t last_accessed,
        const uint64_t created_at
    ) : object_id(object_id),
        size(size),
        compressed_size(z_size),
        last_updated(last_updated),
        last_accessed(last_accessed),
        created_at(created_at) {
    }

    Object::~Object() = default;

    std::string Object::toSQL() const {
        char *sql_raw = sqlite3_mprintf(
            "INSERT INTO objects (object_id, size, compressed_size, last_updated, last_accessed, created_at) "
            "VALUES ('%q', '%q', '%q', '%q', '%q', '%q');",
            object_id,
            size,
            compressed_size,
            last_updated,
            last_accessed,
            created_at
        );

        std::string sql(sql_raw);
        sqlite3_free(sql_raw);

        return sql;
    }
}
