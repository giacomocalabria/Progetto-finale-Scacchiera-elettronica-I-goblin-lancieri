#include "piece.h"

bool is_pawn(piece* p){return (p->symbol() == 'p' || p->symbol() == 'P');}
bool is_king(piece* p){return (p->symbol() == 'r' || p->symbol() == 'R');}
bool is_queen(piece* p){return (p->symbol() == 'd' || p->symbol() == 'D');}
bool is_rook(piece* p){return (p->symbol() == 't' || p->symbol() == 'T');}
bool is_knight(piece* p){return (p->symbol() == 'c' || p->symbol() == 'C');}
bool is_bishop(piece* p){return (p->symbol() == 'a' || p->symbol() == 'A');}