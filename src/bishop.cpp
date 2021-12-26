//Autore: EDDIE CARRARO

#include "bishop.h"
#include "board.h"
#include <algorithm>

using namespace std;

bool bishop::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{

//--------controllo il bounding--------
	if(dest.row > 8 || dest.row < 0 || dest.col > 8 || dest.col < 0)	//ridondante? velocizza????????
	{
		return false;
	}
	vector<position> possible_positions = get_possible_positions();
	vector<position>::iterator it;
	it = find(possible_positions.begin(), possible_positions.end(), dest);
	if(it == possible_positions.end())
		return false;

	position go_on = position(pos.row, pos.col);		//posizione che avanza fino a dest
	piece* go_piece = board_pieces[make_index_8(go_on)];			//pedina di ogni posizione considerata fino a dest

	if(dest.col > pos.col)			//controllo se la destinazione e' a "destra" rispetto alla current_pos
	{
		if(dest.row > pos.row)		//controllo se la destinazione e' "in alto" (a destra) rispetto alla current_pos
		{
			while(go_on.row != dest.row && go_on.col != dest.col)
			{
				go_on = position(go_on.row + 1, go_on.col + 1);
				go_piece = board_pieces[make_index_8(go_on)];

				if(go_piece != nullptr && (*go_piece).get_player() == this->get_player())
				{
					return false;
				}
			}
		}
		else if(dest.row < pos.row)
		{
			while(go_on.row != dest.row && go_on.col != dest.col)
			{
				go_on = position(go_on.row - 1, go_on.col + 1);
				go_piece = board_pieces[make_index_8(go_on)];

				if(go_piece != nullptr && (*go_piece).get_player() == this->get_player())
				{
					return false;
				}
			}
		}
		else
			return false;

		return true;
	}
	else if(dest.col < pos.col)
	{
		if(dest.row > pos.row)		//controllo se la destinazione e' "in alto" (a destra) rispetto alla current_pos
		{
			while(go_on.row != dest.row && go_on.col != dest.col)
			{
				go_on = position(go_on.row + 1, go_on.col - 1);
				go_piece = board_pieces[make_index_8(go_on)];

				if(go_piece != nullptr && (*go_piece).get_player() == this->get_player())
				{
					return false;
				}
			}
		}
		else if(dest.row < pos.row)
		{
			while(go_on.row != dest.row && go_on.col != dest.col)
			{
				go_on = position(go_on.row - 1, go_on.col - 1);
				go_piece = board_pieces[make_index_8(go_on)];

				if(go_piece != nullptr && (*go_piece).get_player() == this->get_player())
				{
					return false;
				}
			}
		}
		else
			return false;
	}
	else
		return false;

	return true;
}

char bishop::symbol()
{
	return player == board::PLAYER_1 ? 'a' : 'A';
}

vector<position> bishop::get_possible_positions()
{
	vector<position> possible_positions;

	position go_on = position(pos.row + 1, pos.col + 1);
	while(go_on.row < 8 && go_on.row > 0 && go_on.col < 8 && go_on.col > 0) //boundary rispettato?
	{
		possible_positions.push_back(go_on);

		go_on.row++;
		go_on.col++;		//controllo le posizioni successive (in cui bishop puo'andare)
	}

	go_on = position(pos.row - 1, pos.col + 1);
	while(go_on.row < 8 && go_on.row > 0 && go_on.col < 8 && go_on.col > 0)	//boundary rispettato?
	{
		possible_positions.push_back(go_on);

		go_on.row--;
		go_on.col++;		//controllo le posizioni successive (in cui bishop puo'andare)
	}

	go_on = position(pos.row + 1, pos.col - 1);
	while(go_on.row < 8 && go_on.row > 0 && go_on.col < 8 && go_on.col > 0)	//boundary rispettato?
	{
		possible_positions.push_back(go_on);

		go_on.row++;
		go_on.col--;		//controllo le posizioni successive (in cui bishop puo'andare)
	}

	go_on = position(pos.row - 1, pos.col - 1);
	while(go_on.row < 8 && go_on.row > 0 && go_on.col < 8 && go_on.col > 0)	//boundary rispettato?
	{
		possible_positions.push_back(go_on);

		go_on.row--;
		go_on.col--;		//controllo le posizioni successive (in cui bishop puo'andare)
	}

	return possible_positions;
}