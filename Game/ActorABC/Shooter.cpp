#include "Shooter.h"

Shooter::Shooter(const Vector2 & position)
	:DrawableActor("S")
{
	this->position = position;
	color = Color::Yellow;

	//++this->index ;
}