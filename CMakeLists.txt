cmake_minimum_required(VERSION 3.10)
project(experiment)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

add_executable(locality_performance locality_performance.cpp)

add_executable(pagesize_ub pagesize_ub.cpp)

add_executable(ipc ipc.cpp)


find_package(Threads REQUIRED)
add_executable(condition_variables condition_variables.cpp)
target_link_libraries(condition_variables PRIVATE Threads::Threads)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Debug build")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g3")
    # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")
elseif(CMAKE_BUILD_TYPE MATCHES Release)    
    message(STATUS "Release build")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
    #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto")
    #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
endif()