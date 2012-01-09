#include	"WinMutex.hpp"

#ifdef		__linux__
#else

WinMutex::WinMutex()
{ }

WinMutex::~WinMutex()
{ }

void	WinMutex::init()
{
  InitializeCriticalSection(&criticalSection);
}

void	WinMutex::lock()
{
  EnterCriticalSection(&criticalSection);
}

void	WinMutex::trylock()
{
  TryEnterCriticalSection(&criticalSection);
}

void	WinMutex::unlock()
{
  LeaveCriticalSection(&criticalSection);
}

void	WinMutex::destroy()
{
  DeleteCriticalSection(&criticalSection);
}

#endif /* WIN32 */