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

#ifndef M_CHUNK_HPP
#define M_CHUNK_HPP
#include <cstdint>
#include <string>
#include <vector>

namespace Pak {
    class Chunk {
    public:
        Chunk
        (
            uint64_t chunk_id,
            uint64_t chunk_address,
            uint64_t chunk_size,

            uint32_t crc32
        );

        ~Chunk();

        [[nodiscard]] std::string toSQL() const;

	[[nodiscard]] std::vector<char> read(const uint64_t chunk_address, const uint64_t chunk_size);
      
        [[nodiscard]] static std::vector<char> align_data_to_boundary(const char *inputData, size_t padding);

        [[nodiscard]] uint64_t get_chunk_size() const { return chunk_size; }
        [[nodiscard]] uint64_t get_chunk_address() const { return chunk_address; }
        [[nodiscard]] uint64_t get_chunk_id() const { return chunk_id; }
	
        [[nodiscard]] uint32_t get_crc32() const { return crc32; }


	void set_chunk_id(uint64_t chunk_id) { this->chunk_id = chunk_id;  }
	void set_chunk_address(uint64_t chunk_address) { this->chunk_address = chunk_address;  }
	void set_chunk_size(uint64_t chunk_size) { this->chunk_size = chunk_size; }
	void set_crc32(uint32_t crc32) { this->crc32 = crc32; }
    private:
        uint64_t chunk_id;
        uint64_t chunk_address;
        uint64_t chunk_size;
	
        uint32_t crc32;
    };
}

#endif //M_CHUNK_HPP
