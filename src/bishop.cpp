//Autore: EDDIE CARRARO

#include "bishop.h"
#include "board.h"
#include <algorithm>

using namespace std;

bool bishop::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{

//--------controllo il bounding--------
	/*if(dest.row > max_position || dest.row < min_position || dest.col > max_position || dest.col < min_position)	//ridondante? velocizza????????
	{
		return false;
	}*/

	vector<position> possible_positions = get_possible_positions();
	vector<position>::iterator it;
	it = find(possible_positions.begin(), possible_positions.end(), dest);
	if(it == possible_positions.end())
		return false;

	position go_on = pos;		//posizione che avanza fino a dest
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
	else if(dest.col < pos.col)          //controllo se la destinazione e' a "sinistra" rispetto alla current_pos
	{
		if(dest.row > pos.row)		//controllo se la destinazione e' "in alto" (a sinistra) rispetto alla current_pos
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

bool bishop::can_eat(const position& dest, const vector<piece*>& board_pieces)
{
	return this->can_move_to(dest, board_pieces);
}

vector<position> bishop::get_possible_positions()
{
	vector<position> possible_positions;

	//---------- diagonale verso avanti-sinistra ---------
	position go_on = position(pos.row + 1, pos.col + 1);
	while(go_on.row < max_position && go_on.row > min_position && go_on.col < max_position && go_on.col > min_position) //boundary rispettato?
	{
		possible_positions.push_back(go_on);

		go_on.row++;
		go_on.col++;		//controllo le posizioni successive (in cui bishop puo'andare)
	}

	//---------- diagonale verso indietro-sinistra ---------
	go_on = position(pos.row - 1, pos.col + 1);
	while(go_on.row < max_position && go_on.row > -1 && go_on.col < max_position && go_on.col > -1)	//boundary rispettato?
	{
		possible_positions.push_back(go_on);

		go_on.row--;
		go_on.col++;		//controllo le posizioni successive (in cui bishop puo'andare)
	}

	//---------- diagonale verso avanti-destra ---------
	go_on = position(pos.row + 1, pos.col - 1);
	while(go_on.row < piece::max_position && go_on.row > piece::min_position && go_on.col < piece::max_position && go_on.col > piece::min_position)		//boundary rispettato?
	{
		possible_positions.push_back(go_on);

		go_on.row++;
		go_on.col--;		//controllo le posizioni successive (in cui bishop puo'andare)
	}

	//---------- diagonale verso indietro-destra ---------
	go_on = position(pos.row - 1, pos.col - 1);
	while(go_on.row < max_position && go_on.row > min_position && go_on.col < max_position && go_on.col > min_position)	//boundary rispettato?
	{
		possible_positions.push_back(go_on);

		go_on.row--;
		go_on.col--;		//controllo le posizioni successive (in cui bishop puo'andare)
	}

	return possible_positions;
}