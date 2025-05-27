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

#ifndef FILEUTILS_HPP
#define FILEUTILS_HPP

#include <zlib.h>

#include <string>
#include <vector>
#include <fstream>

inline std::streampos get_file_size(const char *filePath) {
    std::streampos fsize = 0;
    std::ifstream file(filePath, std::ios::binary);

    fsize = file.tellg();
    file.seekg(0, std::ios::end);
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}

inline uLong compute_crc32(const std::vector<char> &data) {
    if (data.empty()) {
        return 0;
    }
    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, reinterpret_cast<const Bytef *>(data.data()),
                static_cast<uInt>(data.size()));

    return crc;
}

inline bool validate_crc32(const std::vector<char> &data, const uLong &orig_crc32) {
    const uLong computed_crc32 = compute_crc32(data);
    return computed_crc32 == orig_crc32;
}

inline std::vector<char> compress_data(const std::vector<char> &input) {
    z_stream strm = {};
    if (deflateInit(&strm, Z_DEFAULT_COMPRESSION) != Z_OK) {
        throw std::runtime_error("Failed to initialize zlib compression");
    }

    std::vector<char> output;
    output.resize(deflateBound(&strm, input.size()));

    strm.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(input.data()));
    strm.avail_in = input.size();

    strm.next_out = reinterpret_cast<Bytef *>(output.data());
    strm.avail_out = output.size();

    if (deflate(&strm, Z_FINISH) != Z_STREAM_END) {
        deflateEnd(&strm);
        throw std::runtime_error("Zlib compression failed");
    }

    const size_t compressed_size = strm.total_out;
    output.resize(compressed_size);
    deflateEnd(&strm);
    return output;
}

inline std::vector<char> decompress_data(const std::vector<char> &input) {
    z_stream strm = {};
    if (inflateInit(&strm) != Z_OK) {
        throw std::runtime_error("Failed to initialize zlib decompression");
    }

    std::vector<char> output;

    strm.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(input.data()));
    strm.avail_in = input.size();

    strm.next_out = reinterpret_cast<Bytef *>(output.data());
    strm.avail_out = output.size();

    if (inflate(&strm, Z_FINISH) != Z_STREAM_END) {
        inflateEnd(&strm);
        throw std::runtime_error("Zlib decompression failed");
    }

    const size_t decompressed_size = strm.total_out;
    output.resize(decompressed_size);
    inflateEnd(&strm);
    return output;
}

inline std::vector<char> read_file(const std::string &filepath) {
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }

    const size_t size = get_file_size(filepath.c_str());
    std::vector<char> buffer(size);
    file.read(buffer.data(), size);

    file.close();
    return buffer;
}

inline bool write_file(const std::string &filepath, const std::vector<char> &data) {
    std::ofstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }

    const size_t size = data.size();
    std::vector<char> buffer(size);
    file.write(data.data(), size);

    file.flush();
    file.close();
    return true;
}

inline void writeAlignedData(std::ofstream &file, const char *data, const size_t dataSize, const uint32_t alignment) {
    if (!file.write(data, dataSize)) {
        throw std::runtime_error("Failed to write compressed data to file");
    }

    if (const size_t paddingSize = (alignment - dataSize % alignment) % alignment; paddingSize > 0) {
        const std::vector<char> padding(paddingSize, 0);
        if (!file.write(padding.data(), paddingSize)) {
            throw std::runtime_error("Failed to write padding to file");
        }
    }
}

// inline uint get_file_permissions(const std::string &filepath) {
//     std::ifstream file(filepath);
//     if (!file) {
//         throw std::runtime_error("Cannot open file: " + filepath);
//     }
//
//     file.close();
//     return std::filesystem::status(filepath).permissions();
// }

#endif //FILEUTILS_HPP
