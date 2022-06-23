CMAKE_MINIMUM_REQUIRED(VERSION 3.13...3.20)

project(dumper)  #项目名

set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(../common)  #头文件路径

ADD_DEFINITIONS(-g)

add_executable(dumper main_dumper.cpp ../common/crash_handler_dump.cpp)
add_executable(crasher main_crasher.cpp ../common/crash_handler_register.cpp)

TARGET_LINK_LIBRARIES(dumper DbgHelp)
TARGET_LINK_LIBRARIES(crasher DbgHelp)