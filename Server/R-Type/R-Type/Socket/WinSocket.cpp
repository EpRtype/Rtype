#include "WinSocket.hpp"

#ifdef __linux__
#else

WinSocket::WinSocket()
{ }

WinSocket::~WinSocket()
{ }

bool     WinSocket::CreateSocket(int domain, int type, int protocol)
{
  WSADATA wsaData = {0};
  int iResult = 0;
  
  socket_ = INVALID_SOCKET;
  iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != 0)
 	return false;
  socket_ = WSASocket(domain, type, protocol, NULL, 0, WSA_FLAG_OVERLAPPED);
  if (socket_ == INVALID_SOCKET) 
	return false;
  return true;
}

bool     WinSocket::BindSocket(int family, int port)
{
  struct sockaddr_in sockaddress;
  int    len;
   sockaddress.sin_family = family;
   sockaddress.sin_port = htons(port);
   sockaddress.sin_addr.s_addr = htonl(INADDR_ANY);
   len = sizeof(sockaddress);
   if (bind(socket_, (struct sockaddr*)&sockaddress, len) < 0)
	 return false;
   return true;
}

receive     WinSocket::RecvData(int len, int flags)
{
  int    check;
  char   *buffer = new char[len];
  SOCKADDR_IN addr_;
  int    sizeaddr = sizeof(addr_);
  receive   rcv;

  check = recvfrom(socket_, buffer, len, flags, (struct sockaddr*) &addr_, &sizeaddr);
  buffer[check] = 0;
  rcv.data_ = buffer;
  rcv.s_rcv = addr_;
  return rcv;
}

bool     WinSocket::SendData(std::string ip, int port, char *buf, int len, int flags)
{
  int    check;
  SOCKADDR_IN addr_;

  addr_.sin_family = AF_INET;
  addr_.sin_addr.s_addr = inet_addr(ip.c_str());
  addr_.sin_port = htons(port);
  check = sendto(socket_, buf, len, flags, (struct sockaddr*) &addr_, sizeof(addr_));
  if (check == SOCKET_ERROR)
	return false;
  return true;
}
//bool     WinSocket::ListenSocket(int backlog)
//{
//  if (listen(socket_, backlog) < 0)
//	return false;
//  return true;
//}
#endif