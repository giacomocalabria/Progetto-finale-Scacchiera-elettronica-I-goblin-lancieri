// Author: GIACOMO CALABRIA

#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <string>

/*
    ----------------------------------------------------
    position e' alla base di tutto cio' che riguarda
    il concetto astratto di posizione, nella board
    concreta e come variabile membro all'interno di
    un pezzo. Dunque e' stata pensata per essere molto
    flessibile e dotata di molti operatori.
    ----------------------------------------------------
*/

struct position
{
    /*
        La struct position è concepita come general purpouse: non fa alcun
        controllo se la posizione sia accettabile per la board. I controlli
        necessari sono effettuati all'interno di board, nelle classi derivate
        di piece, ecc. La funzione is_valid_position è chiave in questo contesto,
        essendo utilizzata ovunque in modo efficace, elegante e semplice.
        Dunque posizioni tipo (-3, 5) sono VALIDE, semplicemente non lo sono
        nel contesto scacchistico, e dunque sono gestite in un modo differente.
    */
    position() : row{0}, col{0}{}
    position(int _row, int _col) : row{_row}, col{_col}{}
    position(const position& pos) : row{pos.row}, col{pos.col}{}
    position(const std::string& pos);
    
    int get_row(){return row;}
    int get_col(){return col;}
    void set_row(int _row){row = _row;}
    void set_col(int _col){col = _col;}

    int row, col;
};

class bad_position_8{};

// Overload degli operatori
position operator+(position p1, position p2);
position operator-(position p1, position p2);
position operator*(int scalar, position p);
std::ostream& operator<<(std::ostream& os, position p);
bool operator==(position p1, position p2);

// Helper functions
int make_index_8(position p);
int make_index_8(int row, int col);
position position_from_8(int idx);
std::string get_string_move_8(const position& p1, const position& p2);
bool is_valid_position_8(const position& pos);
std::string get_string_8(const position& pos);

// Costanti globali
constexpr int max_position {8};
constexpr int min_position {0};
// Utilizzati soprattutto nei calcoli in position.cpp
constexpr char max_row {'8'};   // '8' Massima riga nella rappresentazione della board
constexpr char min_row {'0'};   // '0'
constexpr char min_col {'A'};   // 'A' Minima colonna nella rappresentazione

#endif // POSITION_H