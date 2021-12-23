cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)

include_directories(include)

project("scacchiera_elettronica")

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

add_library(pawn        #pedone
    include/pawn.h
    src/pawn.cpp
)

add_library(knight      #cavallo
    include/knight.h
    src/knight.cpp
)

add_library(queen       #regina
    include/queen.h
    src/queen.cpp
)

#add_library(rook        #torre
#    include/rook.h
#    src/rook.cpp
#)

add_library(king        #re
    include/king.h
    src/king.cpp
)

add_library(bishop       #alfiere
    include/bishop.h
    src/bishop.cpp
)

#executable scacchiera
add_executable(scacchiera
    #susmake lists
	src/scacchiera.cpp
    src/position.cpp
    src/pawn.cpp
    src/piece.cpp
    src/board.cpp
    src/knight.cpp
    src/queen.cpp
    src/king.cpp
    #src/bishop.cpp
    #src/rook.cpp
)

target_link_libraries(scacchiera
    position
    board
    piece	
    pawn
    knight
    rook
    king
    #queen
    #bishop
)