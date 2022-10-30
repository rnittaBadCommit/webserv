#include "serverChild.hpp"
#include <iostream>
namespace ft
{

	ServerChild::ServerChild(): server_config_(ServerConfig())
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

	ServerChild::ServerChild(const ServerChild &src) {
		server_config_ = src.server_config_;
		location_config_ = src.location_config_;	
		redirectList_map_ = src.redirectList_map_;
		response_code_ = src.response_code_;
		parse_status_ = src.parse_status_;
		HTTP_head_ = src.HTTP_head_;
		content_length_ = src.content_length_;
		read_bytes_ = src.read_bytes_;
		max_body_size_ = src.max_body_size_;
		body_ = src.body_;
		save_ = src.save_;
		path_ = src.path_;
	}

	ServerChild& ServerChild::operator=(const ServerChild &rhs){
		if (this != &rhs) {
			HTTP_head_ = rhs.HTTP_head_;
			server_config_ = rhs.server_config_;
			location_config_ = rhs.location_config_;	
			location_config_ = rhs.location_config_;	
			redirectList_map_ = rhs.redirectList_map_;
			response_code_ = rhs.response_code_;
			parse_status_ = rhs.parse_status_;
			content_length_ = rhs.content_length_;
			read_bytes_ = rhs.read_bytes_;
			max_body_size_ = rhs.max_body_size_;
			body_ = rhs.body_;
			save_ = rhs.save_;
			path_ = rhs.path_;	
		}
		return (*this);
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
		// set up httRequest head
		HTTP_head_ = head;
		save_ = HTTP_head_.getSave();
		max_body_size_ = strBase_to_UI_(server_config_.getClientMaxBodySize(), std::dec);

		// Find location conf
		setUp_locationConfig_();
		// redirect?

		// validate request method and headers
		check_method_();
		check_headers_();
		// check IS CGI?

		// decide parse status and get content-length if needed
		decide_parse_status_();

		if (parse_status_ == readStraight) {
			header_map::iterator content_length = HTTP_head_.GetHeaderFields().find("content-length");

          	content_length_ = strBase_to_UI_(content_length->second, std::dec);
           	if (content_length_ > max_body_size_) {
               	throw_(413, "Payload Too Large");
           	}
           	read_bytes_ = content_length_;
		}
	}
	
	void	ServerChild::Parse(const std::string& content) {
		save_ += content;
        if (parse_status_ == readChunks) {
            read_chunks_();
        } else if (parse_status_ == readStraight) {
            read_straight_();
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
       // ***location config parser:
       // location uri must have beginning / and no ending /

        std::string     httpReqURI = HTTP_head_.GetRequestURI();	
        std::map<std::string, LocationConfig>           serverLocMap = server_config_.getLocationConfig();
        std::map<std::string, LocationConfig>::iterator locConfIt;
        std::string     pathParts;

        while ((locConfIt = serverLocMap.find(httpReqURI)) == serverLocMap.end() && !httpReqURI.empty()) {
            size_t i =  httpReqURI.find_last_of('/');
            pathParts.insert(0, httpReqURI.substr(i)); // from index to npos
            httpReqURI.erase(i); // from index to npos
        }
         
        if (locConfIt == serverLocMap.end()) {
			locConfIt = serverLocMap.find("/");
			if (locConfIt == serverLocMap.end()) {
				throw_(404, "Not Found - no default server exists");
			}
        }

        location_config_ = locConfIt->second;
		if (location_config_.getRedirect().first != LocationConfig::NO_REDIRECT) {
			// create redirect response
		} else {
	        path_ = location_config_.getAlias() + pathParts;
		}

    }

	void	ServerChild::check_method_ () {
		std::set<std::string> valid_methods = location_config_.getAllowMethod();
		std::set<std::string>::iterator end = valid_methods.end();

		if (std::find(valid_methods.begin(), end, HTTP_head_.GetRequestMethod()) == end) {
            throw_(501, "Not Implemented - invalid request method");
        }
	}

	void	ServerChild::check_headers_() {
		header_map headers = HTTP_head_.GetHeaderFields();
		for (header_map::iterator it = headers.begin(); it != headers.end(); ++it) {
			// check for WSP in key
        	if (isspace(it->first[it->first.size() - 1])) {
            	throw_(400, "Bad Request - trailing white space after header key");
			}
        	// Check for obs-fold in value
        	if (it->second[it->second.size() - 1] == '\\') {
            	throw_(400, "Bad Request - obs-fold in header value");
        	}
			// Check for Trailer
			if (it->first == "trailer") {
				throw_(400, "Bad Request - Trailer included");
			}
			// check transfer-encoding
			if (it->first == "transfer-encoding" && it->second != "chunked") {
                throw_(501, "Not Implemented - does not understand transfer-encoding");
            }
			// check and set content-length and read_bytes
			if (it->first == "content-length" && it->second.find(',') != std::string::npos) {
                throw_(400, "Bad Request - comma separated content-length");
			}
		}
	}

	void	ServerChild::decide_parse_status_() {
		header_map headers = HTTP_head_.GetHeaderFields();
		header_map::iterator transfer_encoding = headers.find("transfer-encoding");
        header_map::iterator content_length = headers.find("content-length");

        if (transfer_encoding != headers.end() && content_length != headers.end()) {
            headers.erase(content_length); 
            throw_(400, "Bad Request - both transfer-encoding and content-length exist");
        } else if (transfer_encoding != headers.end()) {
            parse_status_ = readChunks;
        } else if (content_length!= headers.end()) { 
            parse_status_ = readStraight;
        } else {
            if (HTTP_head_.GetRequestMethod() == "POST") {
                throw_(400, "Bad Request - POST expects content-length or transfer-encoding");
            }
            response_code_ = 200;
            parse_status_ = complete;
        }
	}

	void	ServerChild::read_body_() {
 	    read_bytes_ -= save_.size();
     	body_ += save_;
       	save_.clear();
	}

    void	ServerChild::read_straight_() {
		if (read_bytes_ >= save_.size()) {
			read_body_();
		} else {
            body_ += save_.substr(0, read_bytes_);
            save_.erase(0, read_bytes_);
            read_bytes_ = 0;
            throw_(400, "Bad Request - unexpected body bytes");
        }	
        if (read_bytes_ == 0) {
            response_code_ = 200;
            parse_status_ = complete;
        }
		/* if read_bytes doesn't become 0, but no more message comes*/
	}

    void	ServerChild::read_chunks_() {
		//size_t i = 0;
        while (save_.find(DELIM) != std::string::npos) { // while delim can be found in save
    		if (!read_bytes_) { 
				get_hex_read_bytes_();
		        if (read_bytes_ == 0) {
					response_code_ = 200;
					parse_status_ = complete;
					break ;
				}
				/* if never recieve 0?? */
            }
			if (read_bytes_ >= save_.size() - DELIM.size()) {
				if (read_bytes_ == save_.size() - DELIM.size()) {// rb=1   save= a\r\n
					save_.erase(read_bytes_, DELIM.size()); // from read_bytes index to end 
				}
				read_body_();
			} else {
	            body_ += save_.substr(0, read_bytes_);
            	save_.erase(0, read_bytes_);
            	read_bytes_ = 0;
            	throw_(400, "Bad Request - unexpected body bytes");			
			}
	        if (read_bytes_ == 0) {
   	        	response_code_ = 200;
  	        	parse_status_ = complete;
 	       }
        }
	}

	void	ServerChild::get_hex_read_bytes_() {
        size_t i = save_.find(DELIM);

        read_bytes_ = strBase_to_UI_(save_.substr(0, i), std::hex);
		save_.erase(0, i + DELIM.size());

        if (read_bytes_ > max_body_size_) {
            throw_(413, "Payload Too Large");
		}
	}

	void	ServerChild::PrintBody() {
		std::cout << body_ << std::endl;
	}
} // namespace ft
