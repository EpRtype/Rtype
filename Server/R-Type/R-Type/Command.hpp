#ifndef		COMMAND_HPP
#define		COMMAND_HPP

#include "Server.hpp"

class	Server;

class	Command
{
public:
	Command(Server *s);
	~Command(void);

	void	FindCommand(const RTProtocol::Header *h, const receive& rBody);

private:
	void	RecvConnection(const receive& rBody);
	void	RecvConnectionLogIn(const SOCKADDR_IN rcv);
	void	RecvConnectionLogOut(const SOCKADDR_IN rcv);
	void	RecvRunMode(const receive& rBody);
	void	RecvRunModeCreate();
	void	RecvRunModeJoin();
	void	RecvGameAction(const receive& rBody);

	Server	*s;
};

#endif		/* COMMAND_HPP */