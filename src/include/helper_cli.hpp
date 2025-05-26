/**
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

#ifndef HELPER_CLI_H
#define HELPER_CLI_H

#include <string>
#include <argh.h>

int authCmd(const std::string& token, bool debugMode);
int whoamiCmd(bool debugMode);
int pkgInfoCmd(const std::string& repo, const std::string& name, bool debugMode);
int mkRepoCmd(const std::string& name, bool debugMode);
int retrieveCmd(const std::string& name, argh::parser& options, bool debugMode);
int mkPkgCmd(const std::string& name, argh::parser& options, bool debugMode);
int buildPkgCmd(const std::string& repo, const std::string& name, argh::parser& options, bool debugMode);
int pushPkgCmd(const std::string& repo, const std::string& name, argh::parser& options, bool debugMode);
int deleteCmd(const std::string& type, const std::string& repoOrName, argh::parser& options, bool debugMode);
int deleteCmd(const std::string& type, const std::string& repo, const std::string& name, argh::parser& options, bool debugMode);
int logoutCmd();

#endif // HELPER_CLI_H
