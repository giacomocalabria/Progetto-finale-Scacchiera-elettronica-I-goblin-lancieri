//Author: 

#include <iostream>
#include <string>

#include "board.h"
#include "computer_player.h"
#include "human_player.h"

#define space std::cout << "\n------------------------\n";
#define pause system("pause"); system("cls"); 

using namespace std;

int main(int argc, char *argv[])
{
    if(argv[1][1] != 'c' || argv[1][0] != 'c' && argv[1][0] != 'p'){ // se l'argomento non è nè pc nè cc allora il programma termina
        cerr << "[ERROR] Parametri da riga di comando non corretti !!" << endl;
        return -1;
    }

    bool type_of_match = (argv[1][0] == 'p'); //questa variabile è vera se la partita è del tipo giocatore vs computer. E' falsa nel caso contrario ovvero se è del tipo  computer vs computer


    board b;
    space
    b.print_board();

    b.move_piece(position(6, 4), position(4, 4));
    cout << "porcodio\n";
    space
    b.print_board();

    b.move_piece(position(4, 4), position(3, 4));
    space
    b.print_board();

    b.move_piece(position(6, 5), position(5, 5));
    space
    b.print_board();

    b.move_piece(position(5, 5), position(4, 5));
    space
    b.print_board();

    b.move_piece(position(7, 4), position(6, 4));
    space
    b.print_board();

    b.move_piece(position(6, 4), position(5, 4));
    space
    b.print_board();

    b.move_piece(position(5, 4), position(4, 4));
    space
    b.print_board();

    b.move_piece(position(4, 4), position(4, 3));
    space
    b.print_board();

    b.move_piece(position(7, 3), position(6, 4));
    space
    b.print_board();

    b.move_piece(position(6, 4), position(4, 4));
    space
    b.print_board();

    b.move_piece(position(4, 4), position(3, 4));
    space
    b.print_board();

    b.move_piece(position(4, 4), position(4, 3));
    space
    b.print_board();

    b.move_piece(position(4, 4), position(3, 3));
    space
    b.print_board();

    /*computer_player cp1(&b, player_id::player_1);
    computer_player cp2(&b, player_id::player_2);

    b.print_board();

    b.move_piece(position(6, 4), position(4, 4));
    space
    b.print_board();

    b.move_piece(position(5, 4), position(4, 4));
    space
    b.print_board();

    b.move_piece(position(1, 5), position(3, 5));
    space
    b.print_board();

    b.move_piece(position(3, 5), position(4, 5));
    space
    b.print_board();

    b.move_piece(position(4, 5), position(5, 4));
    space
    b.print_board();

    b.move_piece(position(6, 3), position(5, 4));
    space
    b.print_board();*/

    return 0;
}