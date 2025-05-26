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

#ifndef PAK_FILE_HPP
#define PAK_FILE_HPP

#include <string>

inline const std::string pak_initial_sql =
        "create table main.repositories"
        "("
        "id           integer not null"
        "constraint repositories_pk"
        "primary key autoincrement,"
        "name         TEXT    not null,"
        "description  TEXT,"
        "author       TEXT    not null,"
        "url          TEXT,"
        "last_updated integer not null,"
        "created_at   integer not null"
        ");"

        "create table main.packages"
        "("
        "id               integer not null"
        "constraint packages_pk"
        "primary key autoincrement,"
        "name             TEXT    not null,"
        "version          TEXT    not null,"
        "description      TEXT,"
        "author           TEXT    not null,"
        "install_location TEXT    not null,"
        "license          TEXT,"
        "arch             TEXT    not null,"
        "platform         TEXT    not null,"
        "last_updated     integer not null,"
        "created_at       integer not null,"
        "repository       integer not null"
        "constraint packages_repositories_id_fk"
        "references main.repositories"
        ");"

        "create table main.files"
        "("
        "id             integer not null"
        "constraint files_pk"
        "primary key autoincrement,"
        "filename           TEXT    not null,"
        "path               TEXT    not null,"
        "symlink_path       TEXT," // TODO: Add symlinks support
        "crc32              TEXT    not null," // Decompressed file state
        "size               integer not null,"
        "compressed_size    integer not null,"
        "offset_start       integer not null,"
        "offset_end         integer not null,"
        "chunk_size         integer not null,"
        "chunk_count        integer not null,"
        "attributes         integer not null," // like chmod 775 (int value)
        "last_updated       integer not null,"
        "created_at         integer not null,"
        "package            integer not null"
        "constraint files_packages_id_fk"
        "references main.packages"
        ");"

        "create index main.packages_id_author_repository_index"
        "on main.packages (id, author, repository);"

        "create index main.repositories_id_author_name_index"
        "on main.repositories (id, author, name);"

        "create index main.files_id_filename_package"
        "on main.files (id, filename, package);";


namespace Pk {
    struct PakFile {
        uint32_t magic;
        uint16_t version;

        uint32_t header_size;
        uint32_t metadata_size;
        uint64_t total_size;

        uint64_t body_compressed_size;
        uint64_t body_decompressed_size;
    };
}

#endif // PAK_FILE_HPP
