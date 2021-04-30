cmake_minimum_required(VERSION 3.5)

project(miniboost)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(miniboost
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/utils)

target_link_libraries(miniboost ${PROJECT_SOURCE_DIR}/lib/libyaml-cpp.a)
