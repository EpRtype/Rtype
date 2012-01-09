#ifndef    RECEIVE_HPP
#define    RECEIVE_HPP

#include <winsock2.h>

struct		receive
{
  SOCKADDR_IN s_rcv;
  char        *data_;
};

#endif		/* RECEIVE_HPP */