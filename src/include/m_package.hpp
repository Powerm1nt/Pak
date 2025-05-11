#ifndef MODEL_PACKAGE_HPP
#define MODEL_PACKAGE_HPP

#include <string>
#include <vector>
#include "m_os.hpp"

namespace Pk {
    class Package {
    public:
        Package(const std::string &name,
                const std::string &version,
                const std::string &description,
                const std::string &author,
                const std::string &release_url,
                const std::string &last_updated,
                const std::string &created_at,
                const std::string &install_location,
                const Platforms::arch &arch,
                const Platforms::platform &platform,
                const std::vector<std::string> &files,
                bool restart_required = false);

        const std::string &get_name() const { return name; }
        const std::string &get_version() const { return version; }
        const std::string &get_description() const { return description; }
        const std::string &get_author() const { return author; }
        const std::string &get_release_url() const { return release_url; }
        const std::string &get_last_updated() const { return last_updated; }
        const std::string &get_created_at() const { return created_at; }
        const std::string &get_install_location() const { return install_location; }
        const Platforms::arch &get_arch() const { return arch; }
        const Platforms::platform &get_platform() const { return platform; }
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

        Platforms::arch arch;
        Platforms::platform platform;

        std::vector<std::string> files;
        bool restart_required = false;

        struct scripts {
            std::string pre_inst;
            std::string post_inst;
        };
    };
} // namespace Pk

#endif // MODEL_PACKAGE_HPP
