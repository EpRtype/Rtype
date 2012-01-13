#include	"Server.hpp"

Server	*Server::_singleton = NULL;

Server	*Server::getInstance()
{
	if (_singleton == NULL)
		_singleton = new Server();
	return _singleton;
}

void	Server::kill()
{
	if (_singleton != NULL)
	{
		delete	_singleton;
		_singleton = NULL;
	}
}

Server::Server(void)
{
#ifdef __linux__
	serverMutex = new UnixMutex();
#else
	serverMutex = new WinMutex();
#endif
	serverMutex->init();

	serverMutex->lock();
	threadPool = ThreadPool_::getInstance();
	ThreadPool_::_singletonMutex->init();
	serverMutex->unlock();
#ifdef	__linux__
	socket = new UnixSocket();
#else
	socket = new WinSocket();
#endif
}

Server::~Server(void)
{
	for (std::vector<Player *>::const_iterator it = players.begin(); it != players.end(); ++it)
		delete *it;
	for (std::vector<Game *>::const_iterator it = games.begin(); it != games.end(); ++it)
		delete *it;
	delete socket;
	serverMutex->lock();
	ThreadPool_::kill();
	serverMutex->unlock();
	delete serverMutex;
}

void	Server::init(void)
{
	threadPool->ThreadPoolInit(5);
	if (!(socket->CreateSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
		throw std::exception();
	if (!(socket->BindSocket(AF_INET, 4242)))
		throw std::exception();
}

void	Server::running(void)
{
	RTProtocol::Header		*h;
	Command		*c = Command::getInstance();

	while (1)
	{
		receive rHeader = socket->RecvData(sizeof(RTProtocol::Header), MSG_PEEK);
		h = reinterpret_cast<RTProtocol::Header *>(rHeader.data_);
		receive rBody = socket->RecvData(h->Size, 0);
		_command	*recv = new _command();
		recv->h = h;
		recv->r = rBody;
		threadPool->QueuePush(Command::Test, recv);
	}
}

void	Server::addNewPlayer(const struct sockaddr_in rcv)
{
	if (getPlayer(rcv) == 0)
		players.push_back(new Player(rcv));
}

Player	*Server::getPlayer(const struct sockaddr_in rcv) const
{
  for (std::vector<Player *>::const_iterator it = players.begin(); it != players.end(); ++it)
    {
      Player *p = *it;
      uint32_t u = p->getSockaddr().sin_addr.s_addr;
      if (p->getSockaddr().sin_addr.s_addr == rcv.sin_addr.s_addr && p->getSockaddr().sin_port == rcv.sin_port)
		return p;
    }
  return 0;
}

void	Server::deletePlayer(const Player *p)
{
	for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
		if (p == *it)
		{
			players.erase(it);
			break;
		}
}

void	Server::addNewGame(void)
{
	games.push_back(new Game());
}

Game	*Server::getGame(void) const
{
	return games.back();
}

Game	*Server::getGame(const Player *p) const
{
	for (std::vector<Game *>::const_iterator it = games.begin(); it != games.end(); ++it)
		if ((*it)->getId() == p->getIdGame())
			return ((*it));
	return 0;
}

void	Server::deleteGame(const Game *g)
{
	for (std::vector<Game *>::iterator it = games.begin(); it != games.end(); ++it)
		if (g == *it)
		{
			games.erase(it);
			break;
		}
}

Game	*Server::getAvailableSlot(void) const
{
	for (std::vector<Game *>::const_iterator it = games.begin(); it != games.end(); ++it)
		if ((*it)->getEmptySlot() != -1)
			return (*it);
	return 0;
}

ISocket	*Server::getSocket(void) const
{
	return socket;
}