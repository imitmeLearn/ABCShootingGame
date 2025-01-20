#pragma once
#include <Actor/DrawableActor.h>

class ABCBullet: public DrawableActor
{
	RTTI_DECLARATIONS(ABCBullet,DrawableActor)
public:
	ABCBullet(const Vector2& position);
	ABCBullet(bool isRow,const Vector2& position);
	virtual void Update(float deltaTime) override;
	void SetReImage(const char* image);

private:

	float speed = 20.f;
	float yPosition = 0.f;
	float xPosition = 0.f;

	bool isRow= false;
};
