cmake_minimum_required (VERSION 3.5)

project(IPFilter VERSION 0.0.1)

add_executable(ip_filter ip_filter.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld PRIVATE
        /W4
    )
    target_compile_options(boost_test_version PRIVATE
        /W4
    )
    target_compile_options(google_test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(boost_test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(google_test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()