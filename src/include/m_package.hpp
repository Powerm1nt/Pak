#ifndef MODEL_PACKAGE_HPP
#define MODEL_PACKAGE_HPP

#include <string>
#include <vector>
#include <json/config.h>

#include "m_file.hpp"
#include "m_os.hpp"

namespace Pk {
    class Package {
    public:
        Package(
                std::string name,
                std::string version,
                std::string description,
                std::string author,
                std::string last_updated,
                std::string created_at,
                std::string install_location,
                std::string license,

                uint repository,

                const Platforms::Arch &arch,
                const Platforms::Platform &platform,

                const std::vector<File> &files
        );

        ~Package();

        const std::string &get_name() const { return name; }
        const std::string &get_version() const { return version; }
        const std::string &get_description() const { return description; }
        const std::string &get_author() const { return author; }
        const std::string &get_last_updated() const { return last_updated; }
        const std::string &get_created_at() const { return created_at; }
        const std::string &get_install_location() const { return install_location; }
        const std::string &get_license() const { return license; }

        const uint &get_repository() const { return repository; }

        const Platforms::Arch &get_arch() const { return arch; }
        const Platforms::Platform &get_platform() const { return platform; }
        const std::vector<File> &get_files() const { return files; }

        std::string toSQL() const;

    private:
        std::string name;
        std::string version;
        std::string description;
        std::string author;
        std::string last_updated;
        std::string created_at;
        std::string install_location;
        std::string license;

        Platforms::Arch arch;
        Platforms::Platform platform;

        uint repository;

        std::vector<File> files;

        struct scripts {
            std::string pre_inst;
            std::string post_inst;
        };
    };
} // namespace Pk

#endif // MODEL_PACKAGE_HPP
