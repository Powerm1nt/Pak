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
// Created by powerm1nt on 5/27/25.
//

#ifndef M_OBJECT_HPP
#define M_OBJECT_HPP
#include <cstdint>

namespace Pk {
    class Object {
    public:
        Object
        (
            uint64_t object_id,
            uint64_t chunk_size,
            uint64_t chunk_count,
            uint64_t last_updated,
            uint64_t created_at,
            uint64_t last_modified
        );

        ~Object() = default;

        [[nodiscard]] uint64_t get_last_updated() const { return last_updated; }
        [[nodiscard]] uint64_t get_last_accessed() const { return last_accessed; }
        [[nodiscard]] uint64_t get_created_at() const { return created_at; }

    private:
        uint64_t object_id;
        uint64_t size;
        uint64_t compressed_size;

        uint64_t chunk_size;
        uint64_t chunk_count;

        uint64_t last_updated;
        uint64_t last_accessed;
        uint64_t created_at;
    };
}

#endif //M_OBJECT_HPP
