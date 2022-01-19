#Author: GIACOMO CALABRIA

#Questo è il file CMakeLists che contiene l'insieme delle direttive
#e istruzioni che descrivono il codice sorgente del progetto e
#i vari target per la compilazione (eseguibili, librerie)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR) #Check della versione di CMake
set (CMAKE_CXX_STANDARD 11) #Abilita il codice allo standard C++11
set (CMAKE_CXX_FLAGS "-O2") #Attivazione delle opzioni di ottimizzazione

include_directories(include) 

project(Scacchiera_elettronica #Crea il progetto "Scacchiera_elettronica"
    VERSION
        1.0
    DESCRIPTION
        "Corso di Laboratorio di Programmazione: progetto finale"
    LANGUAGES
        CXX
)

# *** librerie del progetto ***

#libreria della scacchiera
add_library(board
    include/position.h
    include/board.h
    src/position.cpp
    src/board.cpp
)

#libreria dei pezzi
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

#libreria dei giocatori
add_library(player
    include/player.h
    include/human_player.h
    include/computer_player.h
    include/player_id.h
    src/player.cpp
    src/human_player.cpp
    src/computer_player.cpp
)

#libreria dedicata al replay
add_library(replay_player
    include/replay_player.h
    include/replay.h
    src/replay_player.cpp
)


# *** eseguibili del progetto ***

#eseguibile della scacchiera
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

#eseguibile per il replay
add_executable(replay
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