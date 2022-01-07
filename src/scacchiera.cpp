//Author: 

#include <iostream>
#include <string>

#include "board.h"
#include "computer_player.h"
#include "human_player.h"

using namespace std;

int main(int argc, char *argv[])
{
<<<<<<< HEAD
    if(argv[1][1] != 'c' || argv[1][0] != 'c' && argv[1][0] != 'p'){ // se l'argomento non è nè pc nè cc allora il programma termina
        cerr << "[ERROR] Parametri da riga di comando non corretti !!" << endl;
=======
    test_1_checkmate();
    return 0;

int main()
{
    board b;
    b.print_board();
    space;

    b.move_piece(position(1, 1), position(3, 1));
    b.print_board();
    space;

    b.move_piece(position(3, 1), position(4, 1));
    b.print_board();
    space;

    b.move_piece(position(6, 2), position(5, 2));
    b.print_board();
    space;

    b.move_piece(position(5, 2), position(4, 2));
    b.print_board();
    space;

    b.move_piece(position(4, 1), position(5, 2));
    b.print_board();
    space;

    return 0;
}


int ex_main()
{
    /*if(argv[1][1] != 'c' || argv[1][0] != 'c' && argv[1][0] != 'p'){ // se l'argomento non è nè pc nè cc allora il programma termina
        clog << "[ERROR] Parametri da riga di comando non corretti !!" << endl;
>>>>>>> parent of 86ea422 (Revert "Merge branch 'Eddie_6'")
        return -1;
    }

    bool type_of_match = (argv[1][0] == 'p'); //questa variabile è vera se la partita è del tipo giocatore vs computer. E' falsa nel caso contrario ovvero se è del tipo  computer vs computer
<<<<<<< HEAD
=======
*/
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
>>>>>>> parent of 86ea422 (Revert "Merge branch 'Eddie_6'")

    return 0;
}