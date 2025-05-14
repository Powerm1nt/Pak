/**
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
#include <string>
#include <argh.h>
#include <PkFramework.hpp>
#include <unordered_map>

enum class Command {
    Unknown,
    Auth,
    Logout,
    Whoami,
    PkgInfo,
    MkRepo,
    Retrieve,
    MkPkg,
    BuildPkg,
    PushPkg,
    RmPkg,
    RmRepo
};

Command getCommand(const std::string &cmd) {
    static const std::unordered_map<std::string, Command> commandMap = {
        {"auth", Command::Auth},
        {"logout", Command::Logout},
        {"whoami", Command::Whoami},
        {"pkginfo", Command::PkgInfo},
        {"mkrepo", Command::MkRepo},
        {"retrieve", Command::Retrieve},
        {"mkpkg", Command::MkPkg},
        {"buildpkg", Command::BuildPkg},
        {"pushpkg", Command::PushPkg},
        {"rmpkg", Command::RmPkg},
        {"rmrepo", Command::RmRepo}
    };

    if (const auto it = commandMap.find(cmd); it != commandMap.end()) {
        return it->second;
    }

    return Command::Unknown;
}


int main(int argc, char *argv[]) {
    // Testing PkFramework

    auto pktest = new Pk::PkFramework();

    argh::parser cmdl;

    cmdl.add_params({
        "-v", "--version",
        "-h", "--help",
        "-D", "--debug",
        "-k", "--keep",
        "-a", "--arch",
        "-p", "--platform"
    });

    cmdl.parse(argc, argv);
    bool debugMode = cmdl[{"-D", "--debug"}];

    if (cmdl[{"-v", "--version"}]) {
        std::cout << "Pakagify CLI v2.0.0\n";
        return 0;
    }

    // Get the command (first positional argument)
    std::string commandStr;
    if (cmdl.size() > 0) {
        commandStr = cmdl[1];
    }

    // Help message
    if (commandStr.empty() || cmdl[{"-h", "--help"}]) {
        std::cout << "Pakagify CLI v2.0.0\n\n"
                << "Commands:\n"
                << "  auth <token>                 Authenticate with Github Token.\n"
                << "  logout                       Logout from Pakagify CLI.\n"
                << "  whoami                       Get the current authenticated user.\n"
                << "  pkginfo <repo> <name>        Get info about a package.\n"
                << "  mkrepo <name>                Make a new repository.\n"
                << "  retrieve <name>              Download a whole repository of packages.\n"
                << "    -k, --keep                 Keep compressed package files after download.\n"
                << "  mkpkg <name>                 Make a new empty package.\n"
                << "    -a, --arch <arch>          Architecture of the pkg (x64, i386, arm64, noarch).\n"
                << "    -p, --platform <platform>  Platform of the pkg (win32, darwin, linux, any).\n"
                << "  buildpkg <repo> <name>       Build a package.\n"
                << "  pushpkg <repo> <name>        Upload a package.\n"
                << "  rmpkg <repo> <name>          Delete a package.\n"
                << "  rmrepo <name>                Delete a repository.\n\n"
                << "Options:\n"
                << "  -D, --debug                  Enable debug mode.\n"
                << "  -v, --version                Show version.\n"
                << "  -h, --help                   Show this help message.\n";
        return 0;
    }

    switch (getCommand(commandStr)) {
        case Command::Auth: {
            if (cmdl.size() < 2) {
                std::cerr << "Error: auth requires a token\nUsage: pkcli auth <token>\n";
                return 1;
            }
            std::string token = cmdl[1];
            authCmd(token.c_str(), debugMode);
            break;
        }
        case Command::Logout: {
            logoutCmd();
            break;
        }
        case Command::Whoami: {
            whoamiCmd(debugMode);
            break;
        }
        case Command::PkgInfo: {
            if (cmdl.size() < 3) {
                std::cerr << "Error: pkginfo requires repo and name\nUsage: pkcli pkginfo <repo> <name>\n";
                return 1;
            }
            std::string repo = cmdl[1];
            std::string name = cmdl[2];
            pkgInfoCmd(repo, name, debugMode);
            break;
        }
        case Command::MkRepo: {
            if (cmdl.size() < 2) {
                std::cerr << "Error: mkrepo requires a name\nUsage: pkcli mkrepo <name>\n";
                return 1;
            }
            std::string name = cmdl[1];
            mkRepoCmd(name, debugMode);
            break;
        }
        case Command::Retrieve: {
            if (cmdl.size() < 2) {
                std::cerr << "Error: retrieve requires a name\nUsage: pkcli retrieve <name> [-k, --keep]\n";
                return 1;
            }
            std::string name = cmdl[1];
            retrieveCmd(name, cmdl, debugMode);
            break;
        }
        case Command::MkPkg: {
            if (cmdl.size() < 2) {
                std::cerr <<
                        "Error: mkpkg requires a name\nUsage: pkcli mkpkg <name> [-a, --arch <arch>] [-p, --platform <platform>]\n";
                return 1;
            }
            std::string name = cmdl[1];
            mkPkgCmd(name, cmdl, debugMode);
            break;
        }
        case Command::BuildPkg: {
            if (cmdl.size() < 3) {
                std::cerr << "Error: buildpkg requires repo and name\nUsage: pkcli buildpkg <repo> <name>\n";
                return 1;
            }
            std::string repo = cmdl[1];
            std::string name = cmdl[2];
            buildPkgCmd(repo, name, cmdl, debugMode);
            break;
        }
        case Command::PushPkg: {
            if (cmdl.size() < 3) {
                std::cerr << "Error: pushpkg requires repo and name\nUsage: pkcli pushpkg <repo> <name>\n";
                return 1;
            }
            std::string repo = cmdl[1];
            std::string name = cmdl[2];
            pushPkgCmd(repo, name, cmdl, debugMode);
            break;
        }
        case Command::RmPkg: {
            if (cmdl.size() < 3) {
                std::cerr << "Error: rmpkg requires repo and name\nUsage: pkcli rmpkg <repo> <name>\n";
                return 1;
            }
            std::string repo = cmdl[1];
            std::string name = cmdl[2];
            deleteCmd("package", repo, name, cmdl, debugMode);
            break;
        }
        case Command::RmRepo: {
            if (cmdl.size() < 2) {
                std::cerr << "Error: rmrepo requires a name\nUsage: pkcli rmrepo <name>\n";
                return 1;
            }
            std::string name = cmdl[1];
            deleteCmd("repository", name, cmdl, debugMode);
            break;
        }
        case Command::Unknown: {
            std::cerr << "Error: Unknown command '" << commandStr << "'\nUse 'pkcli --help' for a list of commands.\n";
            return 1;
        }
    }

    return 0;
}
