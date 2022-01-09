// Author: NICOLA MARITAN

#include "computer_player.h"

#include <algorithm>
#include <ctime>
#include <random>
#include <vector>

using namespace std;

void computer_player::turn()
{
    bool success = false;
    while (!success)
    {
        if (move())
        {
            success = true;
        }
    }
}

bool computer_player::move()
{
    //cout << "Computer_player move.\n";
    // Ottengo tutti i pezzi ancora nella board di questo giocatore in un vector
    vector<position> player_pieces_positions = b->get_player_in_board_pieces_positions(id);

    /*std::cout << "\n-------------------\n"; 
    for (auto p : player_pieces_positions)
    {
        std::cout << p << "\n";
    }*/
    
    // Inizializzazione della generazione

    // La scelta casuale dell'indice all'interno del vector è uniformemente distribuita
    default_random_engine ran(chrono::system_clock::now().time_since_epoch().count());
    int random_index = (int)uniform_int_distribution<>(0, player_pieces_positions.size() - 1)(ran);
    position from = player_pieces_positions.at(random_index);  // from contiene la posiz. del pezzo scelto causalmente
    piece* p = b->get_board_piece(from);    // Pezzo scelto casualmente  

#if DEBUG
    std::cout << "random index: " << random_index << "\nfrom: " << from << "\n";
#endif

    // Ottengo tutte le possibili posizioni del pezzo scelto causalmente
    vector<position> possible_positions = p->get_possible_positions();
    if (possible_positions.size() == 0)
    {
        #if DEBUG
        cout << "possible positions size e' 0.\n";
        #endif
        return false;
    }

    random_index = (int)uniform_int_distribution<>(0, possible_positions.size() - 1)(ran);
    position to = possible_positions.at(random_index);
    // Si ottiene una possibile destinazione casuale di un pezzo scelto casualmente.
    
    // IMPORTANTISSIMO PER IL DEBUG, NON ELIMINARE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //cout << "Trying to move: " << p->symbol() << " from " << from << " to " << to << endl;

    #if DEBUG
    std::cout << "to: " << to;
    std::cout << "\n-------------------\n";
    system("pause");
    #endif

    return b->move_piece(from, to);
}