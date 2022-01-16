//Autore: EDDIE CARRARO

#include "bishop.h"

#include <algorithm>

#include "board.h"

using namespace std;

bool bishop::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
	//cout << "Call a can_move_to di bishop; from : " << pos << ", dest: " << dest << endl;
	//--------controllo il bounding--------
	if(!is_valid_position_8(dest))	//ridondante? velocizza????????
	{
		return false;
	}
	vector<position> possible_positions = get_possible_positions();
	vector<position>::iterator it;
	it = find(possible_positions.begin(), possible_positions.end(), dest);
	if(it == possible_positions.end())
		return false;

	position go_on = position(pos.row, pos.col);  // ---------- posizione che avanza fino a dest
	piece* go_piece = board_pieces.at(make_index_8(go_on));	// --- pedina di ogni posizione considerata fino a dest

	//controllo se la destinazione e' a "destra" rispetto alla current_pos
	if(dest.col > pos.col)
	{
		go_on = go_on + position(0, 1);

	//-------controllo se la destinazione e' "in basso" (a destra) rispetto alla current_pos-------
		if(dest.row > pos.row)
		{
			go_on = go_on + position(1, 0);

			while(go_on.row != dest.row && go_on.col != dest.col)
			{
				go_piece = board_pieces.at(make_index_8(go_on));

				if(go_piece)
				{
					return false;
				}
				go_on = go_on + position(1, 1);
			}
		}
	//-------controllo se la destinazione e' "in alto" (a destra) rispetto alla current_pos-------
		else if(dest.row < pos.row)
		{
			go_on = go_on - position(1, 0);

			while(go_on.row != dest.row && go_on.col != dest.col)
			{
				go_piece = board_pieces.at(make_index_8(go_on));

				if(go_piece)
				{
					return false;
				}
				go_on = go_on + position(-1, 1);
			}
		}
		else
			return false;
	}
	//controllo se la destinazione e' a "sinistra" rispetto alla current_pos
	else if(dest.col < pos.col)
	{
		go_on = go_on - position(0, 1);

	//-------controllo se la destinazione e' "in basso" (a sinistra) rispetto alla current_pos-------
		if(dest.row > pos.row)
		{
			go_on = go_on + position(1, 0);

			while(go_on.row != dest.row && go_on.col != dest.col)
			{
				go_piece = board_pieces.at(make_index_8(go_on));

				if(go_piece)
				{
					return false;
				}
				go_on = go_on + position(1, -1);
			}
		}
	//-------controllo se la destinazione e' "in alto" (a sinistra) rispetto alla current_pos-------
		else if(dest.row < pos.row)
		{
			go_on = go_on - position(1, 0);

			while(go_on.row != dest.row && go_on.col != dest.col)
			{
				go_piece = board_pieces.at(make_index_8(go_on));

				if(go_piece)
				{
					return false;
				}
				go_on = go_on + position(-1, -1);
			}
		}
		else
			return false;
	}
	else
		return false;

	//controllo se in dest c' e' una pedina avversaria o nulla (se trovo una pedina dello stesso player, ritorno false)
	go_piece = board_pieces.at(make_index_8(dest));	//inserisco in go_piece il pezzo presente in dest (eventualmente null)
	if(go_piece && go_piece->get_player() == player)
		return false;

	return true;
}

char bishop::symbol()
{
	return player == player_id::player_1 ? 'a' : 'A';
}

bool bishop::can_capture(const position& dest, const vector<piece*>& board_pieces)
{
	return this->can_move_to(dest, board_pieces);
}

vector<position> bishop::get_possible_positions()
{
	//cout << "Call a get_possible_positions di bishop." << endl;
	vector<position> possible_positions;

	position go_on = position(pos.row + 1, pos.col + 1);
	while(is_valid_position_8(go_on))
	{
		possible_positions.push_back(go_on);

		go_on.row++;
		go_on.col++;		//controllo le posizioni "in basso a destra" (in cui bishop puo'andare)
	}

	go_on = position(pos.row - 1, pos.col + 1);
	while(is_valid_position_8(go_on))
	{
		possible_positions.push_back(go_on);

		go_on.row--;
		go_on.col++;		//controllo le posizioni "in alto a destra" (in cui bishop puo'andare)
	}

	go_on = position(pos.row + 1, pos.col - 1);
	while(is_valid_position_8(go_on))
	{
		possible_positions.push_back(go_on);

		go_on.row++;
		go_on.col--;		//controllo le posizioni "in basso a sinistra" (in cui bishop puo'andare)
	}

	go_on = position(pos.row - 1, pos.col - 1);
	while(is_valid_position_8(go_on))
	{
		possible_positions.push_back(go_on);

		go_on.row--;
		go_on.col--;		//controllo le posizioni "in alto a sinistra" (in cui bishop puo'andare)
	}

	//cout << "Fine call a get_possible_positions di bishop.\n\n";
	return possible_positions;
}