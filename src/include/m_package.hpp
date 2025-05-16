#ifndef MODEL_PACKAGE_HPP
#define MODEL_PACKAGE_HPP

#include <string>
#include <vector>
#include "m_os.hpp"

namespace Pk {
    class Package {
    public:
        Package(std::string name,
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

                bool restart_required);

        const std::string &get_name() const { return name; }
        const std::string &get_version() const { return version; }
        const std::string &get_description() const { return description; }
        const std::string &get_author() const { return author; }
        const std::string &get_release_url() const { return release_url; }
        const std::string &get_last_updated() const { return last_updated; }
        const std::string &get_created_at() const { return created_at; }
        const std::string &get_install_location() const { return install_location; }
        const Platforms::Arch &get_arch() const { return arch; }
        const Platforms::Platform &get_platform() const { return platform; }
        const std::vector<std::string> &get_files() const { return files; }
        bool is_restart_required() const { return restart_required; }

    private:
        std::string name;
        std::string version;
        std::string description;
        std::string author;
        std::string release_url;
        std::string last_updated;
        std::string created_at;
        std::string install_location;

        Platforms::Arch arch;
        Platforms::Platform platform;

        std::vector<std::string> files;
        const bool restart_required = false;

        struct scripts {
            std::string pre_inst;
            std::string post_inst;
        };
    };
} // namespace Pk

#endif // MODEL_PACKAGE_HPP
