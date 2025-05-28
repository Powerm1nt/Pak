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

#include <cstdint>
#include <string>

#include "m_file.hpp"

namespace Pk {
    File::File(
        std::string filename,
        std::string path,
        std::string symlink_path,
        std::string crc32,

        const uint64_t size,
        const uint64_t compressed_size,

        const uint64_t chunk_size,
        const uint64_t chunk_count,
        const uint64_t object_id,

        const uint32_t attributes,

        const uint64_t last_updated,
        const uint64_t created_at,
        const uint64_t package
    ): filename(std::move(filename)),
       path(std::move(path)),
       symlink_path(std::move(symlink_path)),
       crc32(std::move(crc32)),
       size(size),
       compressed_size(compressed_size),
       chunk_size(chunk_size),
       chunk_count(chunk_count),
       attributes(attributes),
       last_updated(last_updated),
       created_at(created_at),
       package_id(package) {
    }

    File::~File() = default;

    std::string File::toSQL() const {
        char *sql_raw = sqlite3_mprintf(
            "INSERT INTO files (filename, path, symlink_path, crc32, size, compressed_size, offset_start, offset_end, chunk_size, chunk_count, attributes, last_updated, created_at, package) "
            "VALUES ('%q', '%q', '%q', '%q', '%lld', '%lld', '%lld', '%lld', '%lld', '%lld', '%lld', '%lld', '%lld', '%lld');",
            filename.c_str(),
            path.c_str(),
            symlink_path.c_str(),
            crc32.c_str(),
            size,
            compressed_size,
            offset_start,
            offset_end,
            chunk_size,
            chunk_count,
            attributes,
            last_updated,
            created_at,
            package_id
        );

        std::string sql(sql_raw);
        sqlite3_free(sql_raw);

        return sql;
    }
}
