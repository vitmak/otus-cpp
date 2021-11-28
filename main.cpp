#include"Config.h"
#include<iostream>


int main(int argc, const char* argv[]) {
	auto config = Config::ParseCmdArguments(argc, argv);

	/*for (const auto& v : config.m_incudeDirs) {
		std::cout << v << "\t";
	}
	std::endl;*/


	return 0;
}