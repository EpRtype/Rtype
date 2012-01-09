#include "Command.hpp"


Command::Command(Server *s): s(s)
{ }

Command::~Command(void)
{ }

void	Command::FindCommand(const RTProtocol::Header *h, const receive& rBody)
{
	std::cout << "FindCommand" << std::endl;
	if (h->Command == RTProtocol::CONNECTION)
		RecvConnection(rBody);
	else if (h->Command == RTProtocol::RUN_MODE)
		RecvRunMode(rBody);
	else if (h->Command == RTProtocol::GAME_ACTION)
		RecvGameAction(rBody);
}

void	Command::RecvConnection(const receive& rBody)
{
	std::cout << "RecvConnection" << std::endl;

	RTProtocol::Connection		*h = reinterpret_cast<RTProtocol::Connection *>(rBody.data_ + sizeof(RTProtocol::Header));
	if (h->StateConnection == RTProtocol::LOG_IN)
		RecvConnectionLogIn(rBody.s_rcv);
	else if (h->StateConnection == RTProtocol::LOG_OUT)
		RecvConnectionLogOut(rBody.s_rcv);
}

void	Command::RecvConnectionLogIn(const SOCKADDR_IN rcv)
{
	std::cout << "RecvConnectionLogIn" << std::endl;

	s->addNewPlayer(rcv);
}

void	Command::RecvConnectionLogOut(const SOCKADDR_IN rcv)
{
	std::cout << "RecvConnectionLogOut" << std::endl;

	if (s->getPlayer(rcv)->getIdGame() != -1)
	{
		// Send to all players in the player game's disconection of the player
	}
	s->deletePlayer(s->getPlayer(rcv));
}

void	Command::RecvRunMode(const receive& rBody)
{
	std::cout << "RecvRunMode" << std::endl;

	RTProtocol::RunMode		*h = reinterpret_cast<RTProtocol::RunMode *>(rBody.data_ + sizeof(RTProtocol::Header));
	if (h->Mode == RTProtocol::CREATE)
		RecvRunModeCreate();
	else if (h->Mode == RTProtocol::JOIN)
		RecvRunModeJoin();
}

void	Command::RecvRunModeCreate()
{
	std::cout << "RecvRunModeCreate" << std::endl;
}

void	Command::RecvRunModeJoin()
{
	std::cout << "RecvRunModeJoin" << std::endl;
}

void	Command::RecvGameAction(const receive& rBody)
{
	std::cout << "RecvGameAction" << std::endl;
}
