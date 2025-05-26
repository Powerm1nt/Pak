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

#include <iostream>
#include <sqlite3.h>

#include <string>

#include "database.hpp"

SQLiteTransaction::SQLiteTransaction(sqlite3* db)
: db(db), errmsg(nullptr) {
    if (!db) {
        throw std::invalid_argument("Database pointer cannot be null");
    }

    try {
        execute("BEGIN TRANSACTION");
    } catch (std::runtime_error &error) {
        std::cerr << "Unable to do the transaction: " << error.what() << std::endl;
        throw;
    }
}

SQLiteTransaction::~SQLiteTransaction() {
    if (errmsg != nullptr) sqlite3_free(errmsg);
    execute("COMMIT");
}

void SQLiteTransaction::execute(const std::string &sql) {
    if (const int req = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errmsg); req != SQLITE_OK) {
        const std::string error_msg = errmsg;
        sqlite3_free(errmsg);
        errmsg = nullptr;
        throw std::runtime_error("Database error: " + error_msg);
    }
}
