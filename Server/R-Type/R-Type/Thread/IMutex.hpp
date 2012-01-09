#ifndef		IMUTEX_HPP
#define		IMUTEX_HPP

class		IMutex
{
public:
  virtual void	init() = 0;
  virtual void	lock() = 0;
  virtual void	trylock() = 0;
  virtual void	unlock() = 0;
  virtual void	destroy() = 0;
};

#endif		/* IMUTEX_HPP */
