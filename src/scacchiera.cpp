//Author: 

#include <iostream>
#include "board.h"
#include <string>
#include "computer_player.h"

#define space std::cout << "\n------------------------\n";
#define pause system("pause"); system("cls"); 

using namespace std; // ./scacchiera singi ginsgo

int main(int argc, char* argv[])
{
    if(argv[1][1] != 'c' || argv[1][0] != 'c' && argv[1][0] != 'p'){ // se l'argomento non è nè pc nè cc allora il programma termina
        cout << "Parametri da riga di comando non corretti !!";
        return 0;
    }

    bool type_of_match = (argv[1][0] == 'p'); //questa variabile è vera se la partita è del tipo giocatore vs computer. E' falsa nel caso contrario ovvero se è del tipo  computer vs computer

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

    std::cout << "main ended correctly.\n";
    return 0;
} 