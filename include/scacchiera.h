//Author: 

#ifndef SCACCHIERA_H
#define SCACCHIERA_H

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "board.h"
#include "computer_player.h"
#include "human_player.h"
#include "player_id.h"

const std::string nome_file{"log.txt"};

int create_file(board& main_board);

#endif //SCACCHIERA_H