#include "Enemy.h"

Enemy::Enemy(const char* image,int yPosition,GameLevel_ABC* refLevel)
	:DrawableActor(image)
{
	int random = Random(1,10);
	if(random%2 ==0)
	{
		direction = Direction::Left;
		xPosition = (float)(refLevel->GetMaxXY().x - width);
	} else
	{
		direction = Direction::Right;
		xPosition = 0.f;
	}

	this -> position = Vector2((int)xPosition,yPosition);
}
void Enemy::Update(float deltaTime)
{}