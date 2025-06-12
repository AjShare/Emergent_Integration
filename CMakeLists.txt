
cmake_minimum_required(VERSION 3.14)
project(CPP_GitHub_Actions)

set(CMAKE_CXX_STANDARD 14)

find_package(vsomeip3 REQUIRED)

include_directories(include)

add_executable(main src/main.cpp src/functions.cpp)
add_executable(test tests/test_main.cpp src/functions.cpp)

add_executable(Sensor_server Sensor_server/main.cpp)
add_executable(Display_client Display_client/main.cpp)

target_link_libraries(Sensor_server vsomeip3)
target_link_libraries(Display_client vsomeip3)


