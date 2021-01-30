cmake_minimum_required (VERSION 3.5)

project(IPFilter VERSION 0.0.1)

add_executable(ip_filter ip_filter.cpp)

set_target_properties(
	configure PROPERTIES
	CXX_STANDART 14
	CXX_STANDART_REQUIRED ON
)