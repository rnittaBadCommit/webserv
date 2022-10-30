#include <iostream>
#include <map>
int main(){
	try{
		std::string hey = "hey";
		std::string b;
		b = hey;
		hey.clear();
		std::cout << b << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
	return 0;
}
