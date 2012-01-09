#ifndef		WIN_MUTEX_HPP
#define		WIN_MUTEX_HPP

#ifdef __linux__
#else

#include	"IMutex.hpp"
#include	<windows.h>

class		WinMutex : public IMutex
{
public:
		WinMutex();
	   ~WinMutex();

  void		init();
  void		lock();
  void		trylock();
  void		unlock();
  void		destroy();

private:
  CRITICAL_SECTION	criticalSection;
};

#endif

#endif		/* WIN_MUTEX_HPP */

