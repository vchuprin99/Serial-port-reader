cmake_minimum_required(VERSION 3.25)

project(SerialReader)

set(PRIVATE_SOURCES
	src/main.cpp
	src/Serial.cpp
)
set(PRIVATE_INCLUDES
	src/Serial.h
)
add_executable(SerialReader ${PRIVATE_SOURCES} ${PRIVATE_INCLUDES})
target_include_directories(SerialReader PRIVATE src)

set (CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")