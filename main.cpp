#include <iostream>

#include <type_traits>

#include <bitset>

#include <string>
#include <vector>
#include <list>


//
// print_ip  - function for integral types
//
template <typename T> 
typename std::enable_if<std::is_integral<T>::value>::type print_ip(T&& value) {
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
typename std::enable_if<std::is_same<S, std::string>::value>::type print_ip(S&& str) {
	std::cout << str << std::endl;
}

//
// print_ip  - function for containers type
//
template <typename T, typename Allocator = std::allocator<typename T::value_type>
	/*typename T::value_type,
	typename T::allocator_type,
	typename T::size_type,
	typename T::difference_type,
	typename T::reference,
	typename T::const_reference,
	typename T::pointer,
	typename T::const_pointer,
	typename T::iterator,
	typename T::const_iterator,
	typename T::reverse_iterator,
	typename T::const_reverse_iterator,
	decltype(std::declval<T>().size()),
	decltype(std::declval<T>().begin()),
	decltype(std::declval<T>().end()),
	decltype(std::declval<T>().cbegin()),
	decltype(std::declval<T>().cend())*/
>
typename std::enable_if<!std::is_same<T, std::string>::value>::type print_ip(const T& container) {
	for (auto it = container.cbegin(); it != container.cend(); ++it) {
		if (it != container.cbegin())
			std::cout << ".";
		std::cout << *it;
	}
	std::cout << std::endl;
}

int main() {
	print_ip(char{-1});
	print_ip(short{ 0 });
	print_ip(int{ 2130706433 });
	print_ip(long ( 8875824491850138409 ));
	
	print_ip(std::string{"trololo"});
	
	std::vector<int> vec{0, 1, 2, 3};
	print_ip(vec);
		
	std::list<short> arr;
	arr.push_back(short{1});
	arr.push_back(short{ 2 });
	print_ip(arr);

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