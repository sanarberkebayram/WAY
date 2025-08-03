cmake_minimum_required(VERSION 3.10)
project(WAY)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include extern/cpp-httplib extern/sqlite_orm/include)

# Add library for the framework
add_library(way_framework src/server.cpp src/PasswordStrategy.cpp src/JwtStrategy.cpp src/GoogleOAuth2Strategy.cpp src/AuthenticationService.cpp src/SQLiteDatabase.cpp src/DatabaseFactory.cpp src/InMemorySessionManager.cpp src/RateLimiter.cpp)

# Add jwt-cpp library
add_subdirectory(extern/jwt-cpp)

# Link framework to external libraries
target_link_libraries(way_framework PUBLIC jwt-cpp::jwt-cpp sqlite3)

# Add executable
add_executable(way_server src/main.cpp)

# Link library to the executable
target_link_libraries(way_server way_framework)

# Add CLI executable
add_executable(way_cli cli/main.cpp)

# Link CLI executable to the framework
target_link_libraries(way_cli way_framework)

# Add testing
enable_testing()

# Add test executable
add_executable(way_tests tests/test_framework.cpp)

# Link test executable to the framework
target_link_libraries(way_tests way_framework)

# Add test to CTest
add_test(NAME framework_tests COMMAND way_tests)
