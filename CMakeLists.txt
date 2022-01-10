cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-O2")

include_directories(include)

project("Scacchiera_elettronica")

# librerie del progetto
add_library(board
    include/position.h
    include/board.h
    src/position.cpp
    src/board.cpp
)

add_library(pieces
    include/piece.h
    src/piece.cpp
    include/pawn.h      #pedone
    src/pawn.cpp
    include/knight.h    #cavallo
    src/knight.cpp
    include/queen.h     #regina
    src/queen.cpp
    include/rook.h      #torre
    src/rook.cpp
    include/king.h      #re
    src/king.cpp
    include/bishop.h    #alfiere
    src/bishop.cpp
)

add_library(player
    include/player.h
    include/human_player.h
    include/computer_player.h
    include/player_id.h
    src/player.cpp
    src/human_player.cpp
    src/computer_player.cpp
    include/scacchiera.h
)

add_library(replay_player
    include/replay_player.h
    include/replay.h
    src/replay_player.cpp
)

#executable scacchiera
add_executable(scacchiera
	src/scacchiera.cpp
    src/position.cpp
    src/pawn.cpp
    src/piece.cpp
    src/board.cpp
    src/knight.cpp
    src/queen.cpp
    src/king.cpp
    src/bishop.cpp
    src/rook.cpp
    src/player.cpp
    src/human_player.cpp
    src/computer_player.cpp
)

target_link_libraries(scacchiera
    board
    pieces	
    player
)

#executable replay
add_executable(replay
    #susmake lists
	src/replay.cpp
    src/position.cpp
    src/pawn.cpp
    src/piece.cpp
    src/board.cpp
    src/knight.cpp
    src/queen.cpp
    src/king.cpp
    src/bishop.cpp
    src/rook.cpp
    src/replay_player.cpp
)

target_link_libraries(replay
    board
    pieces	
    replay_player
)