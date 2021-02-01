cmake_minimum_required(VERSION 3.5)

project(homework1 VERSION 0.0.1)

add_subdirectory(Task1)
add_subdirectory(Task2)

enable_testing()

add_test(boost_test_version boost_test_version)
add_test(google_test_version google_test_version)