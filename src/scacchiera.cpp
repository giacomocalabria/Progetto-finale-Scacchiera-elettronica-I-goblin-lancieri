//Author: 

#include <iostream>
#include "board.h"
#include <string>
#include "computer_player.h"

#define space std::cout << "\n------------------------\n";
#define pause system("pause"); system("cls"); 

using namespace std; // ./scacchiera singi ginsgo

void test_1_checkmate();

int main()
{
    board b;
    b.print_board();
    b.move_piece(position(2, 5), position(1, 5));
    b.print_board();
    b.move_piece(position(1, 5), position(0, 5));
    b.print_board();

}

int ex_main_2(int argc, char* argv[])
{
    board b;
    b.print_board();

    b.move_piece(position(2, 4), position(3, 4));
    b.move_piece(position(2, 4), position(3, 5));
    b.move_piece(position(2, 4), position(1, 4));

    b.print_board();
    //cout << b.is_check(board::PLAYER_1) << endl;
    
    /*if (b.is_checkmate(board::PLAYER_1))
        cout << "checkmate";
    */

    b.print_board();
    
}


int ex_main_1()
{
    test_1_checkmate();
    return 0;

    /*if(argv[1][1] != 'c' || argv[1][0] != 'c' && argv[1][0] != 'p'){ // se l'argomento non è nè pc nè cc allora il programma termina
        clog << "[ERROR] Parametri da riga di comando non corretti !!" << endl;
        return -1;
    }

    bool type_of_match = (argv[1][0] == 'p'); //questa variabile è vera se la partita è del tipo giocatore vs computer. E' falsa nel caso contrario ovvero se è del tipo  computer vs computer
*/
    board b;
    computer_player cp1(&b, 0);
    computer_player cp2(&b, 1);


    b.print_board();
    system("pause");
    system("cls");

    for (int i = 0; i < 10; i++)
    {
        cout << "\n";

        if (i % 2 == 0)
        {
            std::cout << "turn player 1:\n";
            cp1.turn();
        }   
        else
        {
            std::cout << "turn player 2:\n";
            cp2.turn();
        }

        b.print_board();
        cout << "\n";
        system("pause");
        system("cls");
        
    }

    //b.print_board();


    
    /*b.move_piece(position(6, 3), position(4, 3));
    space
    b.print_board();
    space
    b.move_piece(position(1, 0), position(2, 0));
    */

    /*pawn p1(position(1, 2), 1);
    std::cout << p1.get_position();*/

    //b.move_piece(position(2,6), position(2,4));
    //b.print_board();

    /*b.move_piece(position(6,4), position(4,4));
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
    b.print_board();*/


    b.move_piece(position(6, 4), position(4, 2));
    space
    b.print_board();

    b.move_piece(position(1, 5), position(3, 5));
    space
    b.print_board();

    b.move_piece(position(3, 5), position(4, 5));
    space
    b.print_board();

    b.move_piece(position(4, 5), position(5, 5));
    space
    b.print_board();

    b.move_piece(position(7, 4), position(6, 4));
    space
    b.print_board();

    std::cout << "main ended correctly.\n";
    return 0;
}


void test_1_checkmate()
{
    board b;
    #define p(x, y) position(x, y)

    //std::cout << "bruh\n";
    b.move_piece(p(6, 4), p(4, 4));

    std::cout << "Checking check.\n";
    //std::cout << b.is_check(board::PLAYER_1) << std::endl;

    // muovo il re in A4
    b.move_piece(p(7, 4), p(6, 4));
    b.move_piece(p(6, 4), p(5, 4));
    b.move_piece(p(5, 4), p(5, 5));
    b.move_piece(p(5, 5), p(4, 5));

    // pawn dx giù
    b.move_piece(p(1, 7), p(3, 7));

    //
    b.move_piece(p(0, 7), p(2, 7));
    b.move_piece(p(2, 7), p(2, 5));

    b.is_check(board::PLAYER_1);

    b.print_board();
}