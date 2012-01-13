#ifndef		_COMMAND_HPP_
#define		_COMMAND_HPP_

#include "Server.hpp"

struct	_command
{
	RTProtocol::Header *h;
	receive	r;
};

class	Server;

class	Command
{
public:
static int inc;
	void	FindCommand(const RTProtocol::Header *h, const receive& rBody);

	static void	Test(void *param);
	static Command	*getInstance(void);
	static void			kill(void);

private:
	void	RecvConnection(const receive& rBody);
	void	RecvConnectionLogIn(const struct sockaddr_in& rcv);
	void	RecvConnectionLogOut(const struct sockaddr_in& rcv);
	void	RecvRunMode(const receive& rBody);
	void	RecvRunModeCreate(const struct sockaddr_in& rcv);
	void	RecvRunModeJoin(const struct sockaddr_in& rcv);
	void	RecvGameAction(const receive& rBody);

	void	SendConnection(const Player *p, const uint8_t state);
	void	SendIdentifier(const Player *p, const uint8_t id);
	void	SendGameState(const Player *p, const uint8_t state);
	void	SendGameAction();

	void	SendGame();
	void	SendGameNew();
	void	SendGameUpdate();
	void	SendPlayer();
	void	SendPlayerNew();
	void	SendPlayerUpdate();

	char	*getNewHeader(uint8_t command, int32_t size);

	Server	*s;
	static Command	*_singleton;

	Command(void);
	~Command(void);

};

#endif		/* _COMMAND_HPP_ */