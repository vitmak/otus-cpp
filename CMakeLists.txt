cmake_minimum_required(VERSION 3.5)

project(AsyncCmdProcessing VERSION 0.0.1)

add_executable(AsyncCmdProcessing Command.h CommandProcessing.cpp BlockHandler.h BlockHandler.cpp CommandPackage.h CommandPackage.cpp Logger.h ConsoleLogger.h FileLogger.h)

set_target_properties(AsyncCmdProcessing 
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(AsyncCmdProcessing PRIVATE /W4)
endif()

install(TARGETS AsyncCmdProcessing RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)