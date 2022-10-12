NAME := webserv
CXX := c++
CXXFLAGS := -std=c++98 -pedantic -Wall -Wextra -Werror
SRCS := main.cpp HTTP/HTTPRequest.cpp
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