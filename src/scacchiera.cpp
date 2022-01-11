//Author: NICOLA MARITAN

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "board.h"
#include "computer_player.h"
#include "human_player.h"
#include "player_id.h"

using namespace std;

const string nome_file{"log.txt"};

int main(int argc, char *argv[])
{
    if(argv[1][1] != 'c' || argv[1][0] != 'c' && argv[1][0] != 'p'){ // se l'argomento non è nè pc nè cc allora il programma termina
        cerr << "[ERROR] Parametri da riga di comando non corretti !!" << endl;
        return -1;
    }

    bool type_of_match = (argv[1][0] == 'p'); //questa variabile è vera se la partita è del tipo giocatore vs computer. E' falsa nel caso contrario ovvero se è del tipo  computer vs computer

    /*
        Board principale su cui avviene il gioco.
    */
    board main_board;
    main_board.print_board();

    /*
        Vector contenente human_player e computer_players. Il primo
        avrà capacitò max 1 e l'altro 2 per le regole del gioco.
        Sono conservati nel vector per poi acquisire il loro riferimento
        dal vector di player* players, per poter utilizzare le loro
        funzioni virtuali.
    */
    vector<human_player> human_player_game;
    vector<computer_player> computer_player_game;
    vector<player*> players(player_id::player_count);

    // Reserve delle capacità dei vector per le regole del gioco.
    human_player_game.reserve(1);
    computer_player_game.reserve(2);
    players.reserve(2);

    // Se il tipo di match è giocatore vs computer
    if (type_of_match)
    {
        std::cout << "Partita giocatore vs computer.\n";

        // Scelgo casualmente un id giocatore 
        // DA SISTEMARE RNG
        std::random_device rd;
        std::uniform_int_distribution<int> dstr(0, 1);
        int int_player_id = dstr(rd);
        player_id human_id = int_player_id == 0 ? player_1 : player_2;
        player_id computer_id = human_id == player_1 ? player_2 : player_1;
        

        //cout << "human_id: " << human_id << "\ncomputer_id: " << computer_id << endl;

        computer_player_game.push_back(computer_player(&main_board, computer_id));
        human_player_game.push_back(human_player(&main_board, human_id));

        // vector players contiene un rif ad un human_player e duno a un computer_player
        players[computer_player_game[0].get_player_number()] = &computer_player_game[0];
        players[human_player_game[0].get_player_number()] = &human_player_game[0];

    }
    else    // Tipo di match computer vs computer
    {
        computer_player_game.push_back(computer_player(&main_board, player_1));
        computer_player_game.push_back(computer_player(&main_board, player_2));

        players[0] = &computer_player_game[0];
        players[1] = &computer_player_game[1];
    }

    #if NO_TURNS
    main_board.print_board();
    main_board.move_piece(position("C2"), position("C3"));
    main_board.move_piece(position("D2"), position("D3"));
    main_board.print_board();
    main_board.move_piece(position("C1"), position("D2"));
    main_board.print_board();
    main_board.move_piece(position(7, 1), position(6, 3));
    main_board.print_board();
    #endif

    
    #if !NO_TURNS
    int turn_counter{0};
    vector<string> log;
    while (true)
    {
        // Annuncio del turno
        cout << endl <<  "Turno " << turn_counter << endl;
        int player_turn{turn_counter % 2};
        if (player_turn == 0)
            cout << "Tocca al bianco." << endl;
        else
            cout << "Tocca al nero." << endl;

        main_board.print_board();

        // -------------------------- Controllo se il giocatore ha ancora il re --------------------------
        if (main_board.has_king_been_captured(players[player_turn]->get_player_number()))
        {
            string winner = (player_turn == player_1) ? "bianco" : "nero";
            cout << "Il giocatore " << winner << " ha vinto eliminando il re." << endl;
            log = main_board.get_log();
            log.push_back("FF " + winner);
            break;
        }
        /*
            Apparentemente sembra oppurtuno verificare che un giocatore abbia ancora pezzi,
            ma chiaramente se non possiede pezzi allora non possiede nemmeno il re,
            dunque poiché tale verifica è appena avvenuta non c'è bisogno.
        */

        // -------------------------- Controllo se il giocatore è sotto scacco --------------------------
        if (main_board.is_checkmate(players[player_turn]->get_player_number()))
        {
            string winner = (player_turn == player_1) ? "bianco" : "nero";
            cout << "Il giocatore " << winner << " ha vinto. Scacco matto." << endl;
            log = main_board.get_log();
            log.push_back("FF " + winner);
            break;
        }

        // Se non è sotto scacco allora il giocatore può eseguire la sua mossa.
        players[player_turn]->turn();

        if (turn_counter == 500 || main_board.is_draw(players[player_turn]->get_player_number()))
        {
            cout << "Patta placeholder." << endl;
            log = main_board.get_log();
            log.push_back("PP PP");
            break;
        }

        turn_counter++;
    }
    #endif

    cout << "Partita finita, scrittura file 'log.txt'" << endl;
    ofstream out_file(nome_file);
    if(out_file.is_open()){
        for(auto command : log){
            out_file << command << endl;
        }
    } else {
        cerr << "[ERROR] Impossibile aprire/leggere il file: '" << nome_file << "'" << endl;
        return -1;
    }
    out_file.close();
    cout << "Fine scrittura file 'log.txt'" << endl;

    cout << "Programma terminato correttamente." << endl;
    return 0;
}