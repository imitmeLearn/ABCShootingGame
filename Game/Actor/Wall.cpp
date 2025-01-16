#include "Wall.h"

Wall::Wall(const Vector2 & position)
	:DrawableActor("1")
{
	this->position = position;	//위치 설정
	color = Color::Green;		//색상 설정
}