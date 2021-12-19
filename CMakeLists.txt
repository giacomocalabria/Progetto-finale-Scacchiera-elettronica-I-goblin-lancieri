cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

#imposto il nome del progetto
project(scacchiera_elettronica)

include_directories(include)

add_library(

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