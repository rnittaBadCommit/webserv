NAME := webserv
CXX := c++
CXXFLAGS := -std=c++98 -pedantic -Wall -Wextra -Werror
CONFIGSRCS := srcs/config/Config.cpp srcs/config/ConfigParser.cpp srcs/config/LocationConfig.cpp srcs/config/ServerConfig.cpp
HTTPSRCS := srcs/HTTP/HTTPRequest.cpp
SOCKETSRCS := srcs/socket/server.cpp srcs/socket/socket.cpp

# ymori--

HTTPSRCSDIR := srcs/httpMethod
HTTPSRCS += ${HTTPSRCSDIR}/HTTPMethod.cpp srcs/httpResponse/HttpResponse.cpp

# ymori--

SRCS := main.cpp $(CONFIGSRCS) $(HTTPSRCS) $(SOCKETSRCS)
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