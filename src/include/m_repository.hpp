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

#ifndef MODEL_REPOSITORY_HPP
#define MODEL_REPOSITORY_HPP

#include <string>
#include <vector>
#include "m_package.hpp"

namespace Pk {
    using namespace std;

    class Repository {
    public:
        Repository(
            string name,
            string description,
            string author,
            string url,
            string last_updated,
            string created_at,
            string license,

            const vector<Package> &packages
        );

        ~Repository();

        const string &get_name() const { return name; }
        const string &get_description() const { return description; }
        const string &get_author() const { return author; }
        const string &get_url() const { return url; }
        const string &get_last_updated() const { return last_updated; }
        const string &get_created_at() const { return created_at; }
        const string &get_license() const { return license; }

        const vector<Package> &get_packages() const { return packages; }

    private:
        string name;
        string description;
        string author;
        string url;
        string last_updated;
        string created_at;
        string license;

        vector<Package> packages;
    };
} // namespace Pk

#endif // MODEL_REPOSITORY_HPP
