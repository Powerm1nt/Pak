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

#include "m_package.hpp"

namespace Pk {
    Package::Package(const std::string &name, const std::string &version, const std::string &description,
                     const std::string &author, const std::string &release_url, const std::string &last_updated,
                     const std::string &created_at, const std::string &install_location,
                     const Platforms::arch &arch, const Platforms::platform &platform,
                     const std::vector<std::string> &files, bool restart_required)
        : name(name), version(version), description(description), author(author),
          release_url(release_url), last_updated(last_updated), created_at(created_at),
          install_location(install_location), arch(arch), platform(platform),
          files(files), restart_required(restart_required) {
    }
} // namespace Pk
