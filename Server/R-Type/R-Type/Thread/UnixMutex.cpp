#include	"UnixMutex.hpp"

#ifdef		__linux__

UnixMutex::UnixMutex()
{ }

UnixMutex::~UnixMutex()
{ }

void	UnixMutex::init()
{
  mutex = PTHREAD_MUTEX_INITIALIZER;
}

void	UnixMutex::lock()
{
  pthread_mutex_lock(&mutex);
}

void	UnixMutex::trylock()
{
  pthread_mutex_trylock(&mutex);
}

void	UnixMutex::unlock()
{
  pthread_mutex_unlock(&mutex);
}

void	UnixMutex::destroy()
{
  pthread_mutex_destroy(&mutex);
}

#endif		/* __linux__ */
