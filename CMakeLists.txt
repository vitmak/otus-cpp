cmake_minimum_required(VERSION 3.5)

project(GraphicEditor VERSION 0.0.1)

add_executable(GraphicEditor main.cpp Model.h Model.cpp View.h Controller.h Controller.cpp)

set_target_properties(GraphicEditor 
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(GraphicEditor PRIVATE /W4)
else ()
    target_compile_options(GraphicEditor PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS GraphicEditor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)