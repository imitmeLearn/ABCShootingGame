#include "ABCBullet.h"

//_Column
ABCBullet::ABCBullet(bool isRow,const Vector2 & position)
{
	this->isRow =isRow;

	if(isRow)
	{
		DrawableActor("―");
	}

	else
	{
		DrawableActor("|");
		this -> position = position;
		yPosition = (float)position.y;
	}
}

ABCBullet::ABCBullet(const Vector2 & position)
	:DrawableActor("|")
{
	this -> position = position;
	yPosition = (float)position.y;

	color = Color::White;
}

void ABCBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);
	std::cout<<"ABCBullet::Update(float deltaTime) \n";

	/*if(isRow)
	{
	}

	else
	{
		yPosition += speed * deltaTime;
		position.y = (int)yPosition;
	}*/

	if(position.y < 0)
	{
		Destroy();
		return;
	}

	if(position.x < 0)
	{
		Destroy();
		return;
	}
}