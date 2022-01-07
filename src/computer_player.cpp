// Author: NICOLA MARITAN

#include "computer_player.h"
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>

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
    // Ottengo tutti i pezzi di questo giocatore in un vector
    vector<position> player_pieces_positions = b->get_player_pieces_positions(id);

    /*std::cout << "\n-------------------\n"; 
    for (auto p : player_pieces_positions)
    {
        std::cout << p << "\n";
    }*/
    
    // Inizializzazione della generazione

    // La scelta casuale dell'indice all'interno del vector è uniformemente distribuita
    uniform_int_distribution<int> pp_positions_distribution(0, player_pieces_positions.size() - 1);
    int random_index = pp_positions_distribution(generator);
    position from = player_pieces_positions[random_index];  // from contiene la posiz. del pezzo scelto causalmente
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
    uniform_int_distribution<int> poss_positions_distribution(0, possible_positions.size() - 1);
    random_index = poss_positions_distribution(generator);
    position to = possible_positions[random_index];
    // Si ottiene una possibile destinazione casuale di un pezzo scelto casualmente.
    
    #if DEBUG
    std::cout << "to: " << to;
    std::cout << "\n-------------------\n";
    system("pause");
    #endif

    return b->move_piece(from, to);
}