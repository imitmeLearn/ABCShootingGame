#include "ABCBullet.h"

//_Column

ABCBullet::ABCBullet(const Vector2 & position)
	:DrawableActor("|")
{
	this -> position = position;
	yPosition = (float)position.y;
	xPosition = (float)position.x;

	color = Color::White;
}

void ABCBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if(isRow)
	{
		SetReImage("―");

		xPosition += speed * deltaTime;
		position.x = (int)xPosition;
	}

	else
	{
		SetReImage("|");

		yPosition += speed * deltaTime;
		position.y = (int)yPosition;
	}

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

void ABCBullet::SetReImage(const char * image)
{
	auto length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image,length,image);

	//너비 설정
	width = (int)strlen(image);
}