NAME := webserv
CXX := c++
CXXFLAGS := -std=c++98 -pedantic -Wall -Wextra -Werror
CONFIGSRCS := srcs/config/Config.cpp srcs/config/ConfigParser.cpp srcs/config/LocationConfig.cpp srcs/config/ServerConfig.cpp
HTTPSRCS := srcs/HTTP/HTTPHead.cpp
SOCKETSRCS := srcs/server/Cgi.cpp srcs/server/server.cpp srcs/server/serverChild.cpp srcs/server/socket.cpp srcs/server/URL_to_Path.cpp
SRCS := main.cpp srcs/utils.cpp $(CONFIGSRCS) $(HTTPSRCS) $(SOCKETSRCS)
OBJS := $(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re