#pragma once

#include <Actor/DrawableActor.h>
class Shooter: public DrawableActor
{
	RTTI_DECLARATIONS(Shooter,DrawableActor)
public:
	Shooter(const Vector2& position);
private:
};
