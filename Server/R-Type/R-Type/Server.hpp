#ifndef		SERVER_HPP
#define		SERVER_HPP

#ifdef	__linux__
#include	"Socket/UnixSocket.hpp"
#else
#include	"Socket\WinSocket.hpp"
#endif

#include	"Game.hpp"
#include	"Player.hpp"
#include	"Protocol.hpp"
#include	"Command.hpp"

#include	<vector>

class	Command;

class	Server
{
public:
	Server(void);
	~Server(void);

	void	init(void);
	void	running(void);

	void	addNewPlayer(const SOCKADDR_IN rcv);
	Player	*getPlayer(const SOCKADDR_IN rcv);
	void	deletePlayer(const Player *p);
	void	addNewGame(void);
	void	deleteGame(const Game *g);

private:
	ISocket		*socket;
	std::vector<Player *>	players;
	std::vector<Game *>		games;
};

#endif		/* SERVER_HPP */
