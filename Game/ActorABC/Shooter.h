#pragma once

#include <Actor/DrawableActor.h>
#include <Level/GameLevel_ABC.h>

class Shooter: public DrawableActor
{
	RTTI_DECLARATIONS(Shooter,DrawableActor)
public:
	//~Shooter()//DrawableActor 에서 지우니까
	//{
	//	delete image;
	//}
	Shooter(const Vector2& position,GameLevel_ABC* level);

	virtual void Update(float deltaTime) override;

	void SetReImage(const char* image)
	{
		if(this->image)
		{
			delete[] this->image;
		}

		auto length = strlen(image) + 1;
		this->image = new char[length];
		strcpy_s(this->image,length,image);

		//너비 설정
		width = (int)strlen(image);

		index= (int)(char)image[0];
	}

	int GetIndex()
	{
		return index;
	}

private:
	int index = -1;

	GameLevel_ABC* refLevel = nullptr;
	Direction direction = Direction::Right;		//방향변수

	int	xPosition = 0;
	int	yPosition = 0;
	//float speed = 0.00000001f;
	float speed = 20.f;
};