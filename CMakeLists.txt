cmake_minimum_required(VERSION 3.5)

project(async VERSION 0.0.1)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(async_cli main.cpp)

set(ASYNC_LIB Command.h 
               BlockHandler.h BlockHandler.cpp 
               CommandPackage.h CommandPackage.cpp 
               Logger.h ConsoleLogger.h FileLogger.h 
               ThreadManager.h 
               CommandQueue.h
               async.h async.cpp
               AsyncBulkApp.h)

add_library(libasync_static STATIC ${ASYNC_LIB})
add_library(libasync SHARED ${ASYNC_LIB})

set_target_properties(async_cli libasync libasync_static PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(libasync PRIVATE "${CMAKE_BINARY_DIR}")

target_link_libraries(libasync PRIVATE Threads::Threads)

if (MSVC)
    target_link_libraries(async_cli libasync_static)
else ()
    target_link_libraries(async_cli libasync)
endif()

if (MSVC)
    target_compile_options(libasync PRIVATE /W4)
endif()

install(TARGETS async_cli RUNTIME DESTINATION bin)
install(TARGETS libasync LIBRARY DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)