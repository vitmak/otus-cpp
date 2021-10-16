cmake_minimum_required(VERSION 3.5)

project(Matrix VERSION 0.0.1)

add_executable(Matrix main.cpp matrix.h)

set_target_properties(Matrix 
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(Matrix PRIVATE /W4)
else ()
    target_compile_options(Matrix PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS Matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)