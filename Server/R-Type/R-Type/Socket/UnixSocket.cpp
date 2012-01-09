#include	"UnixSocket.hpp"

#ifdef		__linux__

UnixSocket::UnixSocket()
{ }

UnixSocket::~UnixSocket()
{ }

bool     UnixSocket::CreateSocket(int domain, int type, int protocol)
{
  if ((socket_ = socket(domain, type, protocol)) < 0)
	return false;
  return true;
}

bool     UnixSocket::BindSocket(int family, int port, std::string inet_address)
{
  struct sockaddr_in sockad;
  int    len;

   sockad.sin_family = family;
   sockad.sin_port = port;
   sockad.sin_addr.s_addr = inet_addr(inet_address.c_str());
   len = sizeof(sockaddress);
   if(bind(socket_, (struct sockaddr*)&sockad, len) < 0)
	 return false;
   return true;
}

bool     UnixSocket::ListenSocket(int backlog)
{
  if (listen(socket_, backlog) < 0)
	return false;
  return true;
}

#endif		/* __linux__ */