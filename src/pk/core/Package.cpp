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

#include "m_package.hpp"

namespace Pk {
    Package::Package(
        std::string name,
        std::string version,
        std::string description,
        std::string author,
        std::string release_url,
        std::string last_updated,
        std::string created_at,
        std::string install_location,

        const Platforms::Arch &arch,
        const Platforms::Platform &platform,

        const std::vector<std::string> &files,

        const bool restart_required
    )
        : name(std::move(name)),
          version(std::move(version)),
          description(std::move(description)),
          author(std::move(author)),
          release_url(std::move(release_url)),
          last_updated(std::move(last_updated)),
          created_at(std::move(created_at)),
          install_location(std::move(install_location)),
          arch(arch),
          platform(platform),
          files(files),
          restart_required(restart_required) {
    }
} // namespace Pk
