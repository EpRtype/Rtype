#ifndef		ISOCKET_HPP
#define		ISOCKET_HPP

#include "../Receive.hpp"
#include	<iostream>

class   ISocket
{
public:
  virtual bool CreateSocket(int domain, int type, int protocol) = 0;
  virtual bool BindSocket(int family, int port) = 0;
  virtual receive RecvData(int len, int flags) = 0;
  virtual bool SendData(std::string ip, int port, char *buf, int len, int flags) = 0;

  //virtual bool ListenSocket(int backlog) = 0;
};

#endif  /* ISOCKET_HPP */