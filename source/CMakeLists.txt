cmake_minimum_required(VERSION 3.5)

project(06.allocator)

add_executable(allocator reserving_allocator.h memory_manager.h custom_list.h main.cpp)
set_target_properties(allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(allocator PRIVATE /W4)
else ()
    target_compile_options(allocator PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
