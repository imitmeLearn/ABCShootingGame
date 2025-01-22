#pragma once
#include <Actor/DrawableActor.h>
#include <Level/GameLevel_ABC.h>

class Enemy: public DrawableActor
{
	RTTI_DECLARATIONS(Enemy,DrawableActor)

		enum class Direction
	{
		None = -1,
		Left,
		Right
	};

public:
	//Enemy(const Vector2& position);
	//Enemy(const char* image,int yPosition);
	Enemy(const char* image,int yPosition,GameLevel_ABC* level);//@세윤 적이 레벨을 아는게 맞는지?
	virtual void Update(float deltaTime) override;
private:
	Direction direction;

	float xPosition = 0.f;
	float yPosition = 0.f;
	float speed = 3.f;

	GameLevel_ABC* refLevel = nullptr;
};