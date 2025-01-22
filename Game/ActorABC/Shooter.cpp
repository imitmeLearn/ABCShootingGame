#include "Shooter.h"

Shooter::Shooter(const Vector2 & position,GameLevel_ABC* level)
	:DrawableActor("S")
{
	this->position = position;
	color = Color::Yellow;
	xPosition =(float)position.x;
	yPosition =(float)position.y;
	//++this->index ;

	refLevel = level;
}

void Shooter::Update(float deltaTime)
{
	if(refLevel->IsGameOver())
	{
		return;
	}

	Super::Update(deltaTime);

	//if(refLevel->GetHitCount() > 2)

	float factor = direction == Direction::Left? -1.f : 1.f;		//좌우이동
	xPosition += factor *speed* deltaTime ;		//x 축 이동
	//position.x = (int)xPosition;

	//float factor = direction == Direction::Left? -1.f : 1.f;		//좌우이동
	//xPosition += factor * speed * deltaTime ;		//x 축 이동
	////xPosition += factor * speed * deltaTime;		//x 축 이동
	//position.x = (int)xPosition;

	position.x = (int)xPosition % (refLevel->GetMaxXY().x);
	std::cout <<"shoot"<< position.x << "  "<<deltaTime <<"\n";
}