#include "socket.hpp"

int main()
{
	std::vector<in_port_t> port_vec;

	port_vec.push_back(8081);
	// port_vec.push_back(8081);
	ft::ft_socket socket("127.0.0.1", port_vec);

	while (1)
	{
		try
		{
			std::cout << socket.recieve_msg();
		} catch (const std::exception e)
		{
			(void)e;
		}
	}
}
