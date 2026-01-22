cmake_minimum_required(VERSION 3.14)
project(DiskMonitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  SQLiteCpp
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
  GIT_TAG        3.3.1
)
FetchContent_MakeAvailable(SQLiteCpp)

add_executable(DiskMonitor src/main.cpp)
target_link_libraries(DiskMonitor SQLiteCpp)
