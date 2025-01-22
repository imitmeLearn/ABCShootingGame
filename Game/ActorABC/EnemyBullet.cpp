#include "EnemyBullet.h"
#include <Level/GameLevel_ABC.h>

EnemyBullet::EnemyBullet(const Vector2 & position,GameLevel_ABC* level)
	:DrawableActor("o")
{
	this-> position = position;		//위치설정
	yPosition = (float)position.y;

	refLevel = level;
}

void EnemyBullet::Update(float deltaTime)
{
	if(refLevel->IsGameOver())
	{
		return;
	}

	Super::Update(deltaTime);

	yPosition += speed * deltaTime;   // 이동 로직.
	position.y = (int)yPosition;

	if(yPosition >= refLevel->GetMaxXY().y)	//화면 벗어나면 제거
	{
		Destroy();
	}
}