#ifndef SERVERCHILD_HPP
#define SERVERCHILD_HPP

#include "../config/Config.hpp"
#include "../HTTP/HTTPHead.hpp"
#include <map>
#include <set>
#include <sstream>
#include <limits>

namespace ft
{
	class ServerChild
	{

	public:
		typedef std::map<std::string, std::string>		header_map;

		typedef struct
		{
			std::string uri;
			int status_code;
			std::string dest_uri;
		} redirectConf;
		// typedef std::pair<const int, const std::string> redirectConf;
		ServerChild();
		~ServerChild();
		ServerChild(const ServerConfig &server_config);
		ServerChild(const ServerChild &src);
		ServerChild& operator=(const ServerChild &rhs);

		void	SetUp(HTTPHead& head);
		void	Parse(const std::string& content);

		bool	is_redirect_(const std::string &url);
		int		get_response_code() const;
		const HTTPParseStatus&	get_parse_status() const;
		const HTTPHead&			get_HTTPHead() const;
		const std::string&		get_body() const;

		void	SetServerConf(const ServerConfig& serverConfig);

	private:
		ServerConfig server_config_;
		LocationConfig location_config_;
		//std::map<const std::string, Location> location_map_;
		std::map<const std::string, redirectConf> redirectList_map_;

		int			response_code_;
		HTTPParseStatus	parse_status_;
		HTTPHead		HTTP_head_;
		unsigned int	content_length_;
		unsigned int	read_bytes_;
		unsigned int	max_body_size_;
		std::string		body_;
		std::string		save_;
		std::string		path_;
		unsigned int	hex_bytes_;

    	unsigned int	strBase_to_UI_(const std::string& str, std::ios_base& (*base)(std::ios_base&));
		void    throw_(int responseCode, const std::string& message);
		void	setUp_locationConfig_();
		void	check_headers_();
		void	check_method_();
		void	decide_parse_status_();
		void	read_body_(unsigned int len);
        void	read_straight_();
        void	read_chunks_();
		void	get_hex_read_bytes_();
	};
}

#endif
