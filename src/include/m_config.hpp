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

#ifndef CONFIG_PROVIDER_HPP
#define CONFIG_PROVIDER_HPP

#include <memory>
#include <string>

namespace Pk {
	class ConfigProvider {
	public:
		const std::string& get_token() const { return token; }
		const std::string& get_config_file() const { return config_file; }

		const std::string* get_config_dir() const {
			return config_dir ? config_dir.get() : nullptr;
		}

		static std::string get_env_value(const std::string& key);

		void set_token(const std::string& token);

		void set_config_dir(const std::string& config_dir);

		bool load_config(const std::string& file_path);

		bool save_config(const std::string& file_path) const;
		bool init_config_dir();

	private:
		std::string token;
		std::string config_file;
		std::unique_ptr<std::string> config_dir;
	};
}  // namespace Pk

#endif  // CONFIG_PROVIDER_HPP
