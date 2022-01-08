//Author: 

#include <fstream>
#include <iostream>
#include <string>

#include "board.h"
#include "computer_player.h"
#include "human_player.h"

using namespace std;

string nome_file {"log.txt"};

int main(int argc, char *argv[])
{
    if(argv[1][1] != 'c' || argv[1][0] != 'c' && argv[1][0] != 'p'){ // se l'argomento non è nè pc nè cc allora il programma termina
        cerr << "[ERROR] Parametri da riga di comando non corretti !!" << endl;
        return -1;
    }

    bool type_of_match = (argv[1][0] == 'p'); //questa variabile è vera se la partita è del tipo giocatore vs computer. E' falsa nel caso contrario ovvero se è del tipo  computer vs computer

    board b;

    //PARTITA

    vector<string> log = b.get_log();
    cout << "Partita finita, scrittura file log.txt" << endl;
    ofstream out_file(nome_file);
    for(auto command : log){
        out_file << command;
    }
    cout << "Fine scrittura file log.txt" << endl;
    return 0;
}