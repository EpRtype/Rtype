#ifndef		UNIX_MUTEX_HPP
#define		UNIX_MUTEX_HPP

#ifdef		__linux__

#include	"IMutex.hpp"
#include	<pthread.h>

class		UnixMutex : public IMutex
{
public:
		UnixMutex();
	   ~UnixMutex();

  void		init();
  void		lock();
  void		trylock();
  void		unlock();
  void		destroy();

private:
  pthread_mutex_t	mutex;
};

#endif		/* __linux__ */

#endif		/* UNIX_MUTEX_HPP */
