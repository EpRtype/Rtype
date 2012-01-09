#ifndef		PLAYER_HPP
#define		PLAYER_HPP

#include	"Receive.hpp"
#include	"Protocol.hpp"

class Player
{
public:
	Player(const SOCKADDR_IN _rcv);
	~Player(void);

	void	setId(RTProtocol::Identifier _id);
	void	setIdGame(int _idGame);
	const SOCKADDR_IN	getSockaddr(void) const;
	RTProtocol::Identifier	getId(void) const;
	int		getIdGame(void) const;
private:
	const SOCKADDR_IN		rcv;
	RTProtocol::Identifier	id;
	int			idGame;
};

#endif		/* PLAYER_HPP */
