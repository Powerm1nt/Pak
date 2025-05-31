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

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>

#include <string>
#include <functional>

class SQLiteTransaction {
    sqlite3 *db;
    char *errmsg;

public:
    explicit SQLiteTransaction(sqlite3 *db);

    using SQLiteCallback = std::function<void(int columns, char **values, char **names)>;

    ~SQLiteTransaction();

    void execute
    (
       const std::string &sql,
       int (*callback)(void *pvData, int nc, char **azData, char **azNames),
       void *cbArg
    );
};

#endif //DATABASE_HPP
