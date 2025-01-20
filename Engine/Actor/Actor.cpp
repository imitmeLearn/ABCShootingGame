#include "PreCompiledHeader.h"
#include "Actor.h"

Actor::Actor()
	:isActive(true),isExpired(false)
{}

Actor::~Actor()
{}

void Actor::Update(float deltaTime)
{
	//RTTI::
}

void Actor::Draw()
{}

void Actor::SetPosition(const Vector2 & newPosition)
{
	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}