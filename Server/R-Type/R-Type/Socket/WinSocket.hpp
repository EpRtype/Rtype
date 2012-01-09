#ifndef		WIN_SOCKET_HPP
#define		WIN_SOCKET_HPP

#ifdef __linux__
#else

#include "ISocket.hpp"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

class   WinSocket : public ISocket
{
private:
  SOCKET    socket_;
public:
		WinSocket();
		~WinSocket();

  virtual bool CreateSocket(int domain, int type, int protocol);
  virtual bool BindSocket(int family, int port);
  virtual receive RecvData(int len, int flags);
  virtual bool SendData(std::string ip, int port, char *buf, int len, int flags);
  //virtual bool ListenSocket(int backlog);
};
#endif

#endif		/* WIN_SOCKET_HPP */
