﻿#include <iostream>
#include <type_traits>
#include <bitset>
#include <vector>
#include <string>

//
// print_ip  - function for integral types
//
template <typename T> 
typename std::enable_if_t<std::is_integral_v<T>> print_ip(const T& value) {
	const auto ByteSize = 8;
	
	std::bitset<sizeof(T) * ByteSize> bytes = value;

	std::vector <unsigned long> ip;
	ip.reserve(sizeof(T));

	std::bitset<ByteSize> byte;
	for (size_t i = 0; i < bytes.size(); i += ByteSize) {
		for (size_t j = 0; j < ByteSize; ++j) {
			byte[j] = bytes[i + j];
		}
		ip.emplace_back(byte.to_ulong());
	}
	
	for (auto it = ip.crbegin(); it != ip.crend(); ++it) {
		if (it != ip.crbegin())
			std::cout << ".";

		std::cout << *it;
	}
	std::cout << std::endl;
}

//
// print_ip  - function for string type
//
template <typename S>
typename std::enable_if_t<std::is_same_v<S, std::string>> print_ip(const S& str) {
	std::cout << str << std::endl;
}

//template <typename T>
//void print_ip(T&& container) {
//	std::cout << __PRETTY_FUNCTION__ << std::endl;
//	for (auto it = container.cbegin(); it != container.cend(); ++it) {
//		if (it != container.cbegin())
//			std::cout << ".";
//		std::cout << *it;
//	}
//	std::cout << std::endl;
//}

int main() {
	print_ip(char{-1});
	print_ip(short{ 0 });
	print_ip(int{ 2130706433 });
	print_ip(long long{ 8875824491850138409 });
	
	print_ip(std::string{"trololo"});
	
	//std::vector<int> vec{0, 1, 2, 3};
	//print_ip(vec);

	/*
	std::list<short> arr;
	arr.push_back(short{1});
	arr.push_back(short{ 2 });*/

/*
	- Печать адреса как char(-1)
	- Печать адреса как short(0)
	- Печать адреса как int(2130706433)
	- Печать адреса как long(8875824491850138409)
	- Печать адреса как std::string
	- Печать адреса как std::vector
	- Печать адреса как std::list
	- Опционально.Печать адреса как std::tuple
*/

	return 0;
}