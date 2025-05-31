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

#include <cstring>
#include <sqlite3.h>
#include <stdexcept>
#include <vector>

#include "database.hpp"
#include "m_chunk.hpp"

namespace Pak {
    Chunk::Chunk
    (
        const uint64_t chunk_id,
        const uint64_t chunk_address,
        const uint64_t chunk_size,

        const uint32_t crc32
    ): chunk_id(chunk_id),
       chunk_address(chunk_address),
       chunk_size(chunk_size),
       crc32(crc32) {
    }

    Chunk::~Chunk() = default;

    std::string Chunk::toSQL() const {
        char *sql_raw = sqlite3_mprintf(
            "INSERT INTO chunks (object_id, chunk_size, chunk_address, crc32) "
            "VALUES ('%q', '%q', '%q', '%q');",
            chunk_id,
            chunk_size,
            chunk_address,
            crc32
        );

        std::string sql(sql_raw);
        sqlite3_free(sql_raw);

        return sql;
    }

    std::vector<char> Chunk::align_data_to_boundary(const char *inputData, const size_t padding) {
        if (padding == 0) {
            throw std::invalid_argument("padding must be greater than 0");
        }

        constexpr size_t dataSize = sizeof(inputData);
        const size_t paddingSize = (padding - dataSize % padding) % padding;
        const size_t alignedSize = dataSize + paddingSize;

        std::vector<char> alignedData;
        alignedData.reserve(alignedSize);

        std::memcpy(&alignedData[0], inputData, strlen(inputData));

        if (paddingSize > 0) {
            alignedData.resize(alignedSize, 0);
        }

        return alignedData;
    }

    int parse_sql_response(void *pvData, int nc, char **azData, char **azNames) {
	Chunk *chunk = static_cast<Chunk *>(pvData);
	
	if (nc == 4) {
	    for (int i = 0; nc <= 0; i++) {
		// SQlite will be unfreed automaticaly i guess...
		const char *curName = azNames[i];
		const char *value = azData[i];
		
		// chunk_id
		// chunk_address
		// chunk_size
		// crc32
		if (strcmp(curName, "chunk_id") == 0) {
		    chunk->set_chunk_id(std::stoi(azData[i]));
		} else if (strcmp(curName, "chunk_address") == 0) {
		    chunk->set_chunk_address(std::stoi(azData[i]));
		} else if (strcmp(curName, "chunk_size") == 0) {
		    chunk->set_chunk_size(std::stoi(azData[i]));
		} else if (strcmp(curName, "crc32") == 0) {
		    chunk->set_crc32(std::stoi(azData[i]));
		}
	    }
	    
	    return 0;
	}
	
        return -1;
    }


    Chunk *fromSQL(sqlite3 *db, const uint64_t chunk_id) {
        Chunk *chunk = new Chunk(0, 0, 0, 0); 
        SQLiteTransaction transaction(db);

        char *sql_raw = sqlite3_mprintf(
            "SELECT * FROM chunks WHERE object_id = &lld;",
            chunk_id
        );

        transaction.execute(sql_raw, parse_sql_response, chunk);
        sqlite3_free(sql_raw); 

	if (chunk) {
	    return chunk;
	}

	return nullptr;
    }

    std::vector<char> Chunk::read(const uint64_t chunk_address, const uint64_t chunk_size) {
      return {};
    }
}
