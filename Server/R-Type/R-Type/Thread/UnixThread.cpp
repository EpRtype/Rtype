#include	"UnixThread.hpp"

#ifdef		__linux__

UnixThread::UnixThread()
{
  mutex = new UnixMutex();
}

UnixThread::~UnixThread()
{ }

void	UnixThread::create(void *(*start_routine)(void *), void *_arg)
{
  pthread_create(&thread, NULL, start_routine, _arg);
}

void	UnixThread::destroy(void)
{
  pthread_cancel(thread);
}

void	UnixThread::join(void)
{
  pthread_join(thread, NULL);
}
/*
void	UnixThread::start(void)
{

}

void	UnixThread::suspend(void)
{

}

void	UnixThread::resume(void)
{

}
*/

#endif		/* __linux__ */