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

#include <utility>

#include "m_repository.hpp"

namespace Pk {
    Repository::Repository(
        std::string name,
        std::string description,
        std::string author,
        std::string url,
        std::string last_updated,
        std::string created_at,
        std::string license,

        const std::vector<Package> &packages
    )
        : name(move(name)),
          description(move(description)),
          author(move(author)),
          url(move(url)),
          last_updated(move(last_updated)),
          created_at(move(created_at)),
          license(move(license)),
          packages(packages) {
    }

    Repository::~Repository() = default;
} // namespace Pk
