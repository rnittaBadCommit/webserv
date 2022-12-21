NAME := webserv
CXX := c++
CXXFLAGS := -std=c++98 -pedantic -Wall -Wextra -Werror
CONFIGSRCS := 	srcs/config/Config.cpp \
				srcs/config/ConfigParser.cpp \
				srcs/config/LocationConfig.cpp \
				srcs/config/ServerConfig.cpp
HTTPSRCS := srcs/HTTP/HTTPHead.cpp
SOCKETSRCS := 	srcs/server/server.cpp \
				srcs/server/serverChild.cpp \
				srcs/server/socket.cpp
HTTPMETHODSRCS :=	srcs/cgi/Cgi.cpp \
					srcs/httpMethod/AutoIndex.cpp \
					srcs/httpMethod/HTTPMethod.cpp \
					srcs/httpMethod/HTTPProcess.cpp \
					srcs/httpMethod/MethodUtils.cpp \
					srcs/httpMethod/Redirection.cpp
HTTPRESPONSESRCS :=	srcs/httpResponse/HttpResponse.cpp
SRCS := main.cpp srcs/utils/utils.cpp $(CONFIGSRCS) $(HTTPSRCS) $(SOCKETSRCS) $(HTTPMETHODSRCS) $(HTTPRESPONSESRCS)
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