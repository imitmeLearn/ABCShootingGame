#pragma once
#include <Actor/DrawableActor.h>
#include <Level/GameLevel_ABC.h>

class ABCBullet: public DrawableActor
{
	RTTI_DECLARATIONS(ABCBullet,DrawableActor)
public:
	ABCBullet(const Vector2& position,GameLevel_ABC* level);
	ABCBullet(bool isRow,const Vector2& position);
	virtual void Update(float deltaTime) override;
	void SetReImage(const char* image);

private:

	float speed = 20.f;
	float yPosition = 0.f;
	float xPosition = 0.f;

	bool isRow= false;

	GameLevel_ABC* refLevel = nullptr;
};
