#pragma once
#include <Actor/DrawableActor.h>
#include <Level/GameLevel_ABC.h>

class ABCBullet: public DrawableActor
{
	RTTI_DECLARATIONS(ABCBullet,DrawableActor)
public:
	ABCBullet(const Vector2& position,GameLevel_ABC* level);

	~ABCBullet() = default;

	virtual void Update(float deltaTime) override;
	void SetReImage(const char* image);

	void SetIsRow(bool isRow)
	{
		this->isRow=	isRow ;
	}

	void SetIsRow(int dir)
	{
		this->	dir = dir;
	}

private:

	float speed = 20.f;
	float yPosition = 0.f;
	float xPosition = 0.f;

	bool isRow= false;
	int dir= 3;

	GameLevel_ABC* refLevel = nullptr;
};
