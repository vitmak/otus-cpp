cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
    project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(helloworld VERSION 0.0.99)
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(GTest)

configure_file(
	version.h.in
	${CMAKE_CURRENT_BINARY_DIR}/version.h
)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_executable(boost_test_version boost_test_version.cpp)
add_executable(google_test_version google_test_version.cpp)

set_target_properties(helloworld_cli helloworld boost_test_version google_test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
	helloworld
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(boost_test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(helloworld_cli PRIVATE
    helloworld
)
target_link_libraries(boost_test_version
    ${Boost_LIBRARIES}
    helloworld
)

target_include_directories(google_test_version
    PRIVATE "${GTEST_INCLUDE_DIRS}"
)

target_link_libraries(google_test_version
    ${GTEST_BOTH_LIBRARIES}
    helloworld
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



install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(boost_test_version boost_test_version)
