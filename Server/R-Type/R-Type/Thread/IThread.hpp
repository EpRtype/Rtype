#ifndef		ITHREAD_HPP
#define		ITHREAD_HPP

class		IThread
{
public:
  virtual void	create(void *(*start_routine)(void *), void *arg) = 0;
  virtual void	destroy() = 0;
  virtual void	join() = 0;
  //  virtual void	start() = 0;
  //  virtual void	suspend() = 0;
  //  virtual void	resume() = 0;
};

#endif		/* ITHREAD_HPP */
