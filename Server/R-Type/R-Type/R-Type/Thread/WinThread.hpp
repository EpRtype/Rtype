#ifndef		WIN_THREAD_HPP
#define		WIN_THREAD_HPP

#include	"IThread.hpp"
#include	"WinMutex.hpp"

#ifdef __linux__
#else

#include	<windows.h>

class		WinThread : public IThread
{
public:
		WinThread();
		~WinThread();

	void		create(void *(*start_routine)(void *), void *_arg);
	void		destroy();
	void		join();
	void		start();
    void		suspend();
	void		resume();

private:
  IMutex	*mutex;
  HANDLE	thread;
};

#endif

#endif		/* WIN_THREAD_HPP */
