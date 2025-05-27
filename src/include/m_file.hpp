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

//
// Created by Powerm1nt on 26/05/2025.
//

#ifndef M_FILE_HPP
#define M_FILE_HPP
#include <string>

namespace Pk {
    class File {
    public:
        File(
            std::string filename,
            std::string path,
            std::string symlink_path,
            std::string crc32,

            uint64_t size,
            uint64_t compressed_size,
            uint64_t offset_start,
            uint64_t offset_end,

            uint64_t chunk_size,
            uint64_t chunk_count, //TODO move into Object
            uint64_t object_id,

            uint32_t attributes,

            uint64_t last_updated,
            uint64_t created_at,
            uint64_t package
        );

        ~File();

        std::string toSQL() const;

        const std::string &get_filename() const { return filename; }
        const std::string &get_path() const { return path; }
        const std::string &get_symlink_path() const { return symlink_path; }
        const std::string &get_crc32() const { return crc32; }

        const uint64_t &get_size() const { return size; }
        const uint64_t &get_compressed_size() const { return compressed_size; }
        const uint64_t &get_offset_start() const { return offset_start; }
        const uint64_t &get_offset_end() const { return offset_end; }
        const uint64_t &get_chunk_size() const { return chunk_size; }

        const uint32_t &get_chunk_count() const { return chunk_count; }
        const uint32_t &get_attributes() const { return attributes; }

        const uint64_t &get_last_updated() const { return last_updated; }
        const uint64_t &get_created_at() const { return created_at; }
        const uint64_t &get_package() const { return package; }

    private:
        std::string filename;
        std::string path;
        std::string symlink_path;
        std::string crc32;

        uint64_t size;
        uint64_t compressed_size;
        uint64_t offset_start;
        uint64_t offset_end;
        uint64_t chunk_size;

        uint32_t chunk_count;
        uint32_t attributes;

        uint64_t last_updated;
        uint64_t created_at;
        uint64_t package;
    };
}

#endif //M_FILE_HPP
