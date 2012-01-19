#include	"WinThread.hpp"

#ifdef __linux__
#else

WinThread::WinThread()
{ }

WinThread::~WinThread()
{ }

void	WinThread::create(void *(*start_routine)(void *), void *_arg)
{
  thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start_routine, (LPVOID)this, 0, NULL);
}

void	WinThread::destroy(void)
{
  TerminateThread(thread, -1);
}

void	WinThread::join(void)
{
  WaitForSingleObject(thread, INFINITE);
}

#endif /* WIN_32 */
