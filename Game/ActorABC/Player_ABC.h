#pragma once

#include <Actor/DrawableActor.h>
class GameLevel_ABC;
class Player_ABC: public DrawableActor
{
	RTTI_DECLARATIONS(Player_ABC,DrawableActor)
public:
	Player_ABC(const Vector2& position,GameLevel_ABC* level);
	virtual void Update(float deltaTime) override;
private:
	GameLevel_ABC* refLevel = nullptr;

	bool isRow =true;
	int space = 0;
};