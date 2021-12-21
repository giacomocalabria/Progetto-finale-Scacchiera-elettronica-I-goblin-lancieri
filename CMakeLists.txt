cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)

include_directories(include)
project("Progetto")

# librerie del progetto
add_library(position
    include/position.h
    src/position.cpp
)

add_library(board
    include/board.h
    src/board.cpp
)

add_library(piece
    include/piece.h
    src/piece.cpp
)

add_library(pawn
    include/pawn.h
    src/pawn.cpp
)

#executable scacchiera
add_executable(scacchiera
	src/scacchiera.cpp
)

target_link_libraries(scacchiera
    piece	
    position
    pawn
    board
    
)