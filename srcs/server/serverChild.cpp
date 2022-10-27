#include "serverChild.hpp"
#include <iostream>
namespace ft
{

	ServerChild::ServerChild()
		: server_config_(ServerConfig()) 
	{
	}

	ServerChild::ServerChild(const ServerConfig &server_config)
		: server_config_(server_config)
	{
		std::map<std::string, LocationConfig>::const_iterator itend = server_config.getLocationConfig().end();
		for (std::map<std::string, LocationConfig>::const_iterator it = server_config.getLocationConfig().begin(); it != itend; ++it)
		{
			LocationConfig location_config = (*it).second;
			if (location_config.getRedirect().first != LocationConfig::NO_REDIRECT)
			{ // LocationConfig にredirectが設定されている
				std::pair<int, const std::string> tmp = location_config.getRedirect();
				const std::string &redirect_uri = location_config.getUri();
				redirectList_map_[redirect_uri].uri = redirect_uri;
				redirectList_map_[redirect_uri].status_code = tmp.first;
				redirectList_map_[redirect_uri].dest_uri = tmp.second;
			}
		}
	}

	bool ServerChild::is_redirect_(const std::string &url)
	{

		// std::cout <<"url" <<url << std::endl;
		// std::cout <<"url.dest" << redirectList_map_[url].dest_uri << std::endl;
		// std::cout << redirectList_map_["/redirect/"].dest_uri << std::endl;
		std::map<std::string, redirectConf>::const_iterator it = redirectList_map_.upper_bound(url);
		if (it == redirectList_map_.begin())
			return (false);
		--it;
		if ((*it).second.uri.compare(0, (*it).second.uri.size(), url, 0, (*it).second.uri.size()) == 0)
			return (true);
		return (false);
	}

	int		ServerChild::get_response_code() const { return response_code_; }
	const HTTPParseStatus&	ServerChild::get_parse_status() const { return parse_status_;}
	const HTTPHead&			ServerChild::get_HTTPHead() const { return HTTP_head_; }
	const std::string&		ServerChild::get_body() const { return body_; }

	void	ServerChild::SetUp(HTTPHead& head) {
		HTTP_head_ = head;
		save_ = HTTP_head_.getSave();
		max_body_size_ = strBase_to_UI_(server_config_.getClientMaxBodySize(), std::dec);
		HTTP_head_.FilterRequestURI(server_config_.getListen());
		setUp_locationConfig_();
		check_headers_();
		decide_parse_status_();
		
	}
	
	void	ServerChild::Parse(const std::string& content) {
		save_ += content;
        if (parse_status_ == readChunks) {
            read_chunks_();
        } else if (parse_status_ == readStraight) {
            read_body_();
        }
	}

    unsigned int     ServerChild::strBase_to_UI_(const std::string& str, std::ios_base& (*base)(std::ios_base&)) {
        std::stringstream  stream(str);
        unsigned long int  num;

        stream >> base >> num;

        if (num > std::numeric_limits<unsigned int>::max()) {
            throw_(400, "Bad Request - invalid length");
        }
        return (static_cast<unsigned int>(num));
    }

	void    ServerChild::throw_(int responseCode, const std::string& message) {
        response_code_ = responseCode;
        throw std::runtime_error(message);
    }

	void    ServerChild::setUp_locationConfig_() {
        // this function expects _requestURI to start with / and does not have final / (FilterRequestURI() will handle)
        /*
        POST /aaa/bbb/eee/fff HTTP/1.1
        locaiton / {
            alias ./hoge
        }
        location /aaa/bbb { ***
            alias /var/www
        }
        /var/www/eee/fff
        */

       // ***location config parser:
       // location uri must have beginning / and no ending /
       // if no default / location exists, create it and put it in the map
       // alias beginning is decided by user, but please erase ending /

        std::string     httpReqURI = HTTP_head_.GetRequestURI();
		if (is_redirect_(httpReqURI)) {

		}

        std::map<std::string, LocationConfig>           serverLocMap = server_config_.getLocationConfig();
        std::map<std::string, LocationConfig>::iterator locConfIt;
        std::string     pathParts;

        while ((locConfIt = serverLocMap.find(httpReqURI)) == serverLocMap.end() && !httpReqURI.empty()) {
            size_t i =  httpReqURI.find_last_of('/');
            pathParts.insert(0, httpReqURI.substr(i)); // from index to npos
            httpReqURI.erase(i); // from index to npos
        }
         
        if (locConfIt == serverLocMap.end()) {
			throw_(404, "Not Found");
        } else {
            location_config_ = locConfIt->second;
        }

        path_ = location_config_.getAlias() + pathParts;
    }
	void	ServerChild::check_headers_() {
		header_map headers = HTTP_head_.GetHeaderFields();
		for (header_map::iterator it = headers.begin(); it != headers.end(); ++it) {
			// check for WSP in key
        	if (isspace(it->first[it->first.size() - 1])) {
            	TrimWSP(it->first);// maybe we don't need to worry abou it........ 
            	throw_(400, "Bad Request - trailing white space after header key");
			}
        	// Check for obs-fold in value
        	if (it->second[it->second.size() - 1] == '\\') {
            	throw_(400, "Bad Request - obs-fold in header value");
        	}
			// check content-length
			if (it->first == "content-length") {
            	if (it->second.find(',') != std::string::npos) {
                	throw_(400, "Bad Request - comma separated content-length");
            	}
            	content_length_ = strBase_to_UI_(it->second, std::dec);
            	if (content_length_ > max_body_size_) {
                	throw_(413, "Payload Too Large");
            	}
            	read_bytes_ = content_length_;
			}
		}
		// check valid methods
	}
	void	ServerChild::decide_parse_status_() {}
    void	ServerChild::read_chunks_() {}
    void	ServerChild::read_body_() {}
} // namespace ft
