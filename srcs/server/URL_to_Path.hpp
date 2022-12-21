#ifndef URL_to_Path_HPP
#define URL_to_Path_HPP

#include "../config/Config.hpp"

namespace ft
{
	class URL_to_Path
	{
	public:
		URL_to_Path(const ServerConfig &server_config);

		const std::string &getFilePath(const std::string &url);

	private:
		const std::map<std::string, LocationConfig> &location_config_map_;
		std::vector<const std::string, const std::string> redirectList_vec_;

		bool is_redirect_(const std::string &url);
	};

} // namespace ft

#endif
