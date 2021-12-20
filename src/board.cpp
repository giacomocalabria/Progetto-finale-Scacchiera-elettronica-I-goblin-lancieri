#include "board.h"

board::board()
{
    to_empty();
}

void board::move_piece(const position& from, const position& to)
{
    if (board_matrix[from.x][from.y] == nullptr)   // non c'è una pedina nella casella from
    {
        return; // da def, forse eccezione o altro
    }

    piece* p = board_matrix[from.x][from.y];
    if (p->can_move_to(to))
    {
        p->move(position(to));
    }
    
}

void board::to_empty()
{
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j--)
        {
            board_matrix[i][j] = nullptr;
        }
    }
}