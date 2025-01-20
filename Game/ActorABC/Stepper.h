#pragma once

#include <Actor/DrawableActor.h>
class Stepper: public DrawableActor
{
	RTTI_DECLARATIONS(Stepper,DrawableActor)
public:
	Stepper(const Vector2& position);
private:
};
