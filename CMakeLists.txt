cmake_minimum_required(VERSION 3.5)

project(CommandProcessing VERSION 0.0.1)

add_executable(CommandProcessing CommandProcessing.cpp)

set_target_properties(CommandProcessing 
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(CommandProcessing PRIVATE /W4)
else ()
    target_compile_options(CommandProcessing PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS CommandProcessing RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)