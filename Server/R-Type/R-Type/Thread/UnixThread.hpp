#ifndef		_UTHREAD_HPP_
#define		_UTHREAD_HPP_

#ifdef		__linux__

#include	"IThread.hpp"
#include	"UnixMutex.hpp"
#include	<pthread.h>

class		UnixThread : public IThread
{
public:
		UnixThread();
	   ~UnixThread();

  void		create(void *(*start_routine)(void *), void *_arg);
  void		destroy();
  void		join();
  //  void		start();
  //  void		suspend();
  //  void		resume();

private:
  IMutex	*mutex;
  pthread_t	thread;
};

#endif		/* __linux__ */

#endif		/* UTHREAD_HPP */
