cmake_minimum_required(VERSION 3.10)
project(WAY)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include extern/cpp-httplib)

# Add executable
add_executable(way_server src/main.cpp)

# Add library for the framework
add_library(way_framework src/server.cpp src/PasswordStrategy.cpp src/JwtStrategy.cpp src/GoogleOAuth2Strategy.cpp src/AuthenticationService.cpp)

# Add jwt-cpp library
add_subdirectory(extern/jwt-cpp)
target_link_libraries(way_framework PRIVATE jwt-cpp::jwt-cpp)

# Link library to the executable
target_link_libraries(way_server way_framework)

# Add testing
enable_testing()

# Add test executable
add_executable(way_tests tests/test_framework.cpp)

# Link test executable to the framework
target_link_libraries(way_tests way_framework)

# Add test to CTest
add_test(NAME framework_tests COMMAND way_tests)
