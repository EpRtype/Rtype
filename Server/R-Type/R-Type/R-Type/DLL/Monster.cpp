#include "Monster.h"

Monster::Monster(int16_t X, int16_t Y)
{
	_X = X;
	_Y = Y;
}

Monster::~Monster()
{}

uint8_t Monster::getX()
{
	return _X;
}

void Monster::setX(int16_t X)
{
	_X = X;
}

uint8_t Monster::getY()
{
	return _Y;
}

void Monster::setY(int16_t Y)
{
	_Y = Y;
}