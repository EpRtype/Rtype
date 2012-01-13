#include "Command.hpp"
int Command::inc = 0;
Command	*Command::_singleton = NULL;

Command	*Command::getInstance(void)
{
	if (_singleton == NULL)
		_singleton = new Command();
	return _singleton;
}

void	Command::kill(void)
{
	if (_singleton != NULL)
	{
		delete	_singleton;
		_singleton = NULL;
	}
}

Command::Command(void)
{ }

Command::~Command(void)
{ }

void	Command::Test(void *param)
{
	_command *recv = reinterpret_cast<_command *>(param);
	RTProtocol::Connection *connect = reinterpret_cast<RTProtocol::Connection *>(recv->r.data_ + sizeof(RTProtocol::Header));
	Command *c = Command::getInstance();
	c->FindCommand(recv->h, recv->r);
}

void	Command::FindCommand(const RTProtocol::Header *h, const receive &rBody)
{
//  std::cout << "FindCommand" << std::endl;

  if (h->Command == RTProtocol::CONNECTION)
    RecvConnection(rBody);
  else if (h->Command == RTProtocol::RUN_MODE)
    RecvRunMode(rBody);
  else if (h->Command == RTProtocol::GAME_ACTION)
    RecvGameAction(rBody);
}

void	Command::RecvConnection(const receive &rBody)
{
//  std::cout << "RecvConnection" << std::endl;

  RTProtocol::Connection		*h = reinterpret_cast<RTProtocol::Connection *>(rBody.data_ + sizeof(RTProtocol::Header));
  if (h->StateConnection == RTProtocol::LOG_IN)
    RecvConnectionLogIn(rBody.s_rcv);
  else if (h->StateConnection == RTProtocol::LOG_OUT)
    RecvConnectionLogOut(rBody.s_rcv);
}

void	Command::RecvConnectionLogIn(const struct sockaddr_in& rcv)
{
	std::cout << "RecvConnectionLogIn: " << inc++ << std::endl;

	Server *s = Server::getInstance();
	s->addNewPlayer(rcv);
}

void	Command::RecvConnectionLogOut(const struct sockaddr_in& rcv)
{
  std::cout << "RecvConnectionLogOut: " << inc++ << std::endl;

	Server *s = Server::getInstance();
	if (s->getPlayer(rcv) != 0)
	{
		if (s->getPlayer(rcv)->getIdGame() != -1)
		{
			for (int i = 0; i < 4; ++i)
				if (s->getGame(s->getPlayer(rcv))->getPlayer(i) != 0)
					SendConnection(s->getPlayer(rcv), RTProtocol::LOG_OUT);
			s->getGame(s->getPlayer(rcv))->setPlayer(0, s->getPlayer(rcv)->getId());
		}
		SendConnection(s->getPlayer(rcv), RTProtocol::LOG_OUT);
		s->deletePlayer(s->getPlayer(rcv));
	}
}

void	Command::RecvRunMode(const receive& rBody)
{
//  std::cout << "RecvRunMode" << std::endl;
  
  RTProtocol::RunMode		*h = reinterpret_cast<RTProtocol::RunMode *>(rBody.data_ + sizeof(RTProtocol::Header));
  if (h->Mode == RTProtocol::CREATE)
	  RecvRunModeCreate(rBody.s_rcv);
  else if (h->Mode == RTProtocol::JOIN)
	  RecvRunModeJoin(rBody.s_rcv);
}

void	Command::RecvRunModeCreate(const struct sockaddr_in& rcv)
{
//	std::cout << "RecvRunModeCreate" << std::endl;

	Server *s = Server::getInstance();

	s->addNewGame();
	s->getGame()->setPlayer(s->getPlayer(rcv), RTProtocol::PLAYER_1);
	SendIdentifier(s->getPlayer(rcv), RTProtocol::PLAYER_1);
	SendGameState(s->getPlayer(rcv), RTProtocol::START);
}

void	Command::RecvRunModeJoin(const struct sockaddr_in& rcv)
{
//  std::cout << "RecvRunModeJoin" << std::endl;

	Server *s = Server::getInstance();

  if (s->getAvailableSlot() != 0)
  {
	  s->getPlayer(rcv)->setId(s->getAvailableSlot()->getEmptySlot());
	  s->getPlayer(rcv)->setIdGame(s->getAvailableSlot()->getId());
	  s->getAvailableSlot()->setPlayer(s->getPlayer(rcv), s->getAvailableSlot()->getEmptySlot());
	  SendIdentifier(s->getPlayer(rcv), s->getPlayer(rcv)->getId().Id);
	  for (int i = 0; i < 4; ++i)
		  if (s->getGame(s->getPlayer(rcv))->getPlayer(i) != 0 && s->getGame(s->getPlayer(rcv))->getPlayer(i)->getId().Id != s->getPlayer(rcv)->getId().Id)
			  SendIdentifier(s->getGame(s->getPlayer(rcv))->getPlayer(i), s->getPlayer(rcv)->getId().Id);
	  SendGameState(s->getPlayer(rcv), RTProtocol::END);
  }
  else
  {
	  RecvRunModeCreate(rcv);
  }
}

void	Command::RecvGameAction(const receive& rBody)
{
  std::cout << "RecvGameAction" << std::endl;
}

void	Command::SendConnection(const Player *p, const uint8_t state)
{
	std::cout << "SendConnection" << std::endl;

	char	*send;
	RTProtocol::Connection c;
	Server *s = Server::getInstance();

	c.StateConnection = state;
	send = getNewHeader(RTProtocol::CONNECTION, sizeof(RTProtocol::Header) + sizeof(RTProtocol::Connection));
	std::memcpy(send + sizeof(RTProtocol::Header), &c, sizeof(RTProtocol::Connection));
	s->getSocket()->SendData(p->getSockaddr().sin_addr, p->getSockaddr().sin_port, send, sizeof(RTProtocol::Header) + sizeof(RTProtocol::Connection), 0);
}

void	Command::SendIdentifier(const Player *p, const uint8_t id)
{
	std::cout << "SendIdentifier" << std::endl;

	char	*send;
	RTProtocol::Identifier i;
	Server *s = Server::getInstance();

	i.Id = id;
	send = getNewHeader(RTProtocol::IDENTIFIER, sizeof(RTProtocol::Header) + sizeof(RTProtocol::Identifier));
	std::memcpy(send + sizeof(RTProtocol::Header), &i, sizeof(RTProtocol::Identifier));
	s->getSocket()->SendData(p->getSockaddr().sin_addr, p->getSockaddr().sin_port, send, sizeof(RTProtocol::Header) + sizeof(RTProtocol::Identifier), 0);
}

void	Command::SendGameState(const Player *p, const uint8_t state)
{
	std::cout << "SendGameState" << std::endl;

	char	*send;
	RTProtocol::GameState g;
	Server *s = Server::getInstance();

	g.State = state;
	send = getNewHeader(RTProtocol::GAME_STATE, sizeof(RTProtocol::Header) + sizeof(RTProtocol::GameState));
	std::memcpy(send + sizeof(RTProtocol::Header), &g, sizeof(RTProtocol::GameState));
	s->getSocket()->SendData(p->getSockaddr().sin_addr, p->getSockaddr().sin_port, send, sizeof(RTProtocol::Header) + sizeof(RTProtocol::GameState), 0);
}

char	*Command::getNewHeader(uint8_t command, int32_t size)
{
	std::cout << "getNewHeader" << std::endl;

	RTProtocol::Header	h;

	h.Command = command;
	h.Size = size;

	char *header = new char[size];
	std::memcpy(header, &h, sizeof(RTProtocol::Header));

	return (header);
}
