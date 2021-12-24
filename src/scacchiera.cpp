#include <iostream>
#include "board.h"
#include <string>

#define space cout << "\n////////////////\n";

using namespace std;

int main(int argc, char* argv[])
{
    if(argv[1][1] != 'c' || argv[1][0] != 'c' && argv[1][0] != 'p'){
        cout << "Parametri da riga di comando non corretti !!";
        return 0;
    }

    bool type_of_match = (argv[1][0] == 'p'); //questa variabile è vera se la partita è del tipo giocatore vs computer. E' falsa nel caso contrario ovvero se è del tipo  computer vs computer

    board b;
    b.print_board();
    
    //b.move_piece(position(6, 3), position(4, 3));
    //space
    //b.print_board();
    //space
    //b.move_piece(position(1, 0), position(2, 0));

    /*pawn p1(position(1, 2), 1);
    std::cout << p1.get_position();*/


    return 0;
} 