#include <iostream>
#include "board.h"

#define space std::cout << "\n////////////////\n";

int main()
{
    board b;
    b.print_board();

    b.move_piece(position(6, 3), position(4, 3));
    space
    b.print_board();
    space
    //b.move_piece(position(1, 0), position(2, 0));

    /*pawn p1(position(1, 2), 1);
    std::cout << p1.get_position();*/


    return 0;
}