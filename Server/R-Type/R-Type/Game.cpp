#include "Game.hpp"

Game::Game(void): id(-1), player1(0), player2(0), player3(0), player4(0)
{ }

Game::~Game(void)
{ }

void	Game::setId(int _id)
{
	id = _id;
}

void	Game::setPlayer(Player *_player, int id)
{
	if (id == 0)
		player1 = _player;
	else if (id == 1)
		player2 = _player;
	else if (id == 2)
		player3 = _player;
	else if (id == 3)
		player4 = _player;
}

int		Game::getId(void) const
{
	return id;
}

Player	*Game::getPlayer(int id) const
{
	if (id == 0)
		return player1;
	else if (id == 1)
		return player2;
	else if (id == 2)
		return player3;
	else if (id == 3)
		return player4;
	return 0;
}
