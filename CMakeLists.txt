cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)

#imposto il nome del progetto
project(scacchiera_elettronica)

include_directories(include)

add_library(position
	include/position.h
	src/position.cpp
)

#executable scacchiera
add_executable(scacchiera

)

target_link_libraries(scacchiera

)

#executable replay
add_executable(replay

)

target_link_libraries(replay
    
)