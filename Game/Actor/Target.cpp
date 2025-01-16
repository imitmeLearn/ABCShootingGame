#include "Target.h"

Target::Target(const Vector2 & position)
	:DrawableActor("T")
{
	this->position = position;	//위치 설정
	color = Color::Blue;		//색상 설정
}