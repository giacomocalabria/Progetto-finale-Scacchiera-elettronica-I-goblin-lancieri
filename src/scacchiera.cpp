#include <iostream>
#include "board.h"

#define space std::cout << "\n------------------------\n";

int main()
{
    board b;
    b.print_board();
    
    b.move_piece(position(6, 3), position(4, 3));
    space
    b.print_board();
    space
    b.move_piece(position(1, 0), position(2, 0));

    /*pawn p1(position(1, 2), 1);
    std::cout << p1.get_position();*/

    //b.move_piece(position(2,6), position(2,4));
    //b.print_board();

    b.move_piece(position(6,4), position(4,4));
    b.print_board();
    space
    b.move_piece(position(7,2), position(6,3));
    b.print_board();
    space
    b.move_piece(position(7,5), position(5,3));
    b.print_board();
    space
    b.move_piece(position(5,3), position(6,4));
    //b.move_piece(position(7, 7), position(4, 7));
    b.move_piece(position(7, 7), position(7, 4));
    b.move_piece(position(7, 7), position(0, 7));
    b.move_piece(position(0, 7), position(0, 6));
    b.move_piece(position(0, 6), position(3, 6));
    b.move_piece(position(3, 6), position(2, 5));   // non valida

    b.move_piece(position(3, 6), position(0, 6));   // ritorno su
    b.move_piece(position(0, 6), position(0, 2));
    space
    b.print_board();


    return 0;
}