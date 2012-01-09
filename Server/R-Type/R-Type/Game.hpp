#ifndef		GAME_HPP
#define		GAME_HPP

#include	"Player.hpp"

class Game
{
public:
	Game(void);
	~Game(void);

	void	setId(int _id);
	void	setPlayer(Player *_player, int id);
	int		getId(void) const;
	Player	*getPlayer(int id) const;
private:
	int		id;
	Player	*player1;
	Player	*player2;
	Player	*player3;
	Player	*player4;
};

#endif		/* GAME_HPP */