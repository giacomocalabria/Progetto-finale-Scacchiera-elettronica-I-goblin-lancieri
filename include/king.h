#ifndef KING_H
#define KING_H

#include "piece.h"

class king : public piece
{
    public:
        king(const position& _pos, int _player) : piece(_pos, _player){}
        inline char symbol() override;
        bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) override;
        bool can_capture(const position& dest, const std::vector<piece*>& board_pieces) override;
        bool can_promote() override;
        std::vector<position> get_possible_positions() override;
         
    public:
        bool is_check(const std::vector<piece*>& board_pieces);
};

#endif //KING_H