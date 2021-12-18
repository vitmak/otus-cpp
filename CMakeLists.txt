cmake_minimum_required(VERSION 3.5)

project(Bayan VERSION 0.0.1)

find_package(Boost COMPONENTS program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(Bayan main.cpp Config.h Config.cpp FileSeacher.h FileSeacher.cpp DirectoryTraversal.h HashedFile.h HashedFile.cpp Hasher.h CRC32Hasher.h CRC32Hasher.cpp MD5Hasher.h MD5Hasher.cpp)

target_link_libraries(Bayan ${Boost_LIBRARIES})

set_target_properties(Bayan 
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(Bayan PRIVATE /W4)
else ()
    target_compile_options(Bayan PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS Bayan RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)