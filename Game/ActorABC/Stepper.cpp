#include "Stepper.h"

Stepper::Stepper(const Vector2 & position)
	:DrawableActor("s")
{
	this->position = position;	//위치 설정
	color = Color::Yellow;		//색상 설정

	//++this->index ;
}