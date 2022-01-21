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
        // Chiamo move finche' questa non restituisce true
        if (move())
        {
            success = true;
        }
    }
}

bool computer_player::move()
{
    // Ottengo tutti i pezzi ancora nella board di questo giocatore in un vector
    vector<position> player_pieces_positions = b->get_player_in_board_pieces_positions(id);
    
    // Inizializzazione della generazione

    // La scelta casuale dell'indice all'interno del vector è uniformemente distribuita
    // Il seed è il numero di millisecondi passanti dal primo gennaio 1970
    default_random_engine ran(chrono::system_clock::now().time_since_epoch().count());
    int random_index = (int)uniform_int_distribution<>(0, player_pieces_positions.size() - 1)(ran);
    position from = player_pieces_positions.at(random_index);  // from contiene la posiz. del pezzo scelto causalmente
    piece* p = b->get_board_piece(from);    // Pezzo scelto casualmente  

    // Ottengo tutte le possibili posizioni del pezzo scelto causalmente
    vector<position> possible_positions = p->get_possible_positions();

    if (possible_positions.size() == 0)
    {   
        return false;
    }

    // Ottengo una posizione a caso fra quelle possibili
    random_index = (int)uniform_int_distribution<>(0, possible_positions.size() - 1)(ran);
    position to = possible_positions.at(random_index);
    // Si ottiene una possibile destinazione casuale di un pezzo scelto casualmente.
    
    /*
        Chiaramente tutti questi controli servono per diminuire
        il dominio di scelta del computer_player. Sono decisamente
        piu' mirate e dunque efficenti di un elemento che sceglie
        casualmente fra tutti i pezzi nella board (1/64 di possibilita'
        di ottenere un proprio pezzo nel caso peggiore di avere solo
        il re, senza contare la scelta casuale della poszione).
        Cio' rende la soluzione molto efficente.
    */

    // Ritorna true se e solo se il pezzo si è mosso
    return b->move_piece(from, to);
}