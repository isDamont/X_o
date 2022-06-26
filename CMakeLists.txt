cmake_minimum_required(VERSION 3.0)
project(X_o)

set(CMAKE_CXX_STANDARD 17)

add_executable(X_o main.cpp X_o.cpp head.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(X_o sfml-system sfml-window sfml-graphics sfml-audio sfml-network)