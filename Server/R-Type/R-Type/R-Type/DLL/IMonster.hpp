#include <cstdint>

#ifndef _IMONSTER_HPP_
#define _IMONSTER_HPP_

#include	<vector>

class	IMonster
{
public:
	virtual int16_t getX(void) = 0;
	virtual int16_t getY(void) = 0;
	virtual	std::vector<int16_t>	getXFires(void) = 0;
	virtual	std::vector<int16_t>	getYFires(void) = 0;
	virtual uint8_t getType(void) = 0;
	virtual void	update(void) = 0;
	virtual uint8_t	getWidth(void) = 0;
	virtual uint8_t getHeight(void) = 0;
	virtual uint8_t	getLife(void) = 0;
	virtual void	setLife(uint8_t) = 0;
	virtual	uint32_t	getId(void) = 0;
	virtual void		setId(uint32_t _id) = 0;
	virtual void		ActFire() = 0;
	virtual void		UpdateFire() = 0;
};

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif
/*
extern "C"
{
   DECLDIR void* getInstanceDLL(int X, int Y);
}
*/
#endif	/* IMONSTER_HPP */
