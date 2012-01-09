#include	"Server.hpp"

Server::Server(void)
{ 
#ifdef	__linux__
	socket = new UnixSocket();
#else
	socket = new WinSocket();
#endif
}

Server::~Server(void)
{ }

void	Server::init(void)
{
	if (!(socket->CreateSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
		throw -1;
	if (!(socket->BindSocket(AF_INET, 4242)))
		throw -1;
}

void	Server::running(void)
{
	RTProtocol::Header		*h;
	Command					c(this);

	while (1)
	{
		receive rHeader = socket->RecvData(sizeof(RTProtocol::Header), MSG_PEEK);
		h = reinterpret_cast<RTProtocol::Header *>(rHeader.data_);
		receive rBody = socket->RecvData(h->Size, 0);
		c.FindCommand(h, rBody);
	}
}

void	Server::addNewPlayer(const SOCKADDR_IN rcv)
{
	players.push_back(new Player(rcv));
}

Player	*Server::getPlayer(const SOCKADDR_IN rcv)
{
	for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
	{
		Player *p = *it;
		if (p->getSockaddr().sin_addr.S_un.S_addr == rcv.sin_addr.S_un.S_addr && p->getSockaddr().sin_port == rcv.sin_port)
			return p;
	}
	return 0;
}

void	Server::deletePlayer(const Player *p)
{
	for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
	{
		if (p == *it)
		{
			players.erase(it);
			break;
		}
	}
}

void	Server::addNewGame(void)
{
	games.push_back(new Game());
}

void	Server::deleteGame(const Game *g)
{

}