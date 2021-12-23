#include "bishop.h"
#include "board.h"
#include <algorithm>

using namespace std;

void bishop::move(const position& to)
{

}

bool bishop::can_move_to(const position& dest, piece* const mat[][8])
{
//--------controllo il bounding--------
	if(dest.row < 8 || dest.row > 0 || dest.col < 8 || dest.col > 0)
	{
		return false;
	}
	vector<position> possible_positions = get_possible_positions();
	vector<position>::iterator it;
	it = find(possible_positions.begin(), possible_positions.end(), dest);
	if(it == possible_positions.end())
		return false;

	int sign = player == board::PLAYER_1 ? -1 : 1;  // orientazione (mi serve???)

	it = possible_positions.begin();	//faccio ripartire l'iteratore
	if(dest.col > pos.col)			//controllo se la destinazione e' a "destra" rispetto alla current_pos
	{
		while(it != possible_positions.end())
		{
			if((*it).col > dest.col && (*it).col <= dest.col)	//- - - - .controllo se ci sono pedine nelle caselle interessate
			{
				//position is_piece = position((*it).row, (*it).col);

				if(mat[(*it).row][(*it).col])
				{
					return false;
				}
			}
			it++;
		}
	}
	return true;
}

char bishop::symbol()
{
	return player == board::PLAYER_1 ? 'a' : 'A';
}

vector<position> bishop::get_possible_positions()
{
	vector<position> possible_positions;
	int sign = player == board::PLAYER_1 ? -1 : 1;  // orientazione

	position go_on = position(pos.row + 1, pos.col + sign);
	while(go_on.row < 8 && go_on.row > 0 && go_on.col < 8 && go_on.col > 0) //boundary rispettato?
	{
		possible_positions.push_back(go_on);

		go_on.row += 1;
		go_on.col += sign;		//controllo le posizioni successive (in cui bishop puo'andare)
	}

	go_on = position(pos.row - 1, pos.col + sign);
	while(go_on.row < 8 && go_on.row > 0 && go_on.col < 8 && go_on.col > 0)	//boundary rispettato?
	{
		possible_positions.push_back(go_on);

		go_on.row -= 1;
		go_on.col += sign;		//controllo le posizioni successive (in cui bishop puo'andare)
	}

	return possible_positions;
}