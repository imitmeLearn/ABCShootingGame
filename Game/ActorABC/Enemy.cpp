#include "Enemy.h"
#include "ActorABC/EnemyBullet.h"
#include "Engine/Engine.h"
#include "Actorabc/Player_ABC.h"

Enemy::Enemy(const char* image,int yPosition,GameLevel_ABC* level)
	:DrawableActor(image)
{
	int random = Random(1,10);
	if(random%2 ==0)
	{
		direction = Direction::Left;
		xPosition = (float)(level->GetMaxXY().x - width);
	} else
	{
		direction = Direction::Right;
		xPosition = 0.f ;
	}

	this -> position = Vector2((int)xPosition,yPosition);

	refLevel = level;
}
void Enemy::Update(float deltaTime)
{
	if(refLevel->IsGameOver())
	{
		return;
	}

	Super::Update(deltaTime);

	float factor = direction == Direction::Left? -1.f : 1.f;		//좌우이동
	xPosition += factor * speed * deltaTime;		//x 축 이동
	position.x = (int)xPosition;

	if(xPosition < 0.f || position.x > refLevel->GetMaxXY().x - width)			// 화면 밖 벗어나면 삭제.
	{
		Destroy();
	}

	static float elapsedTime = 0.f;	//탄약 발사
	static float fireInterval = RandomPercent(1.f,2.f);

	elapsedTime += deltaTime;		//타이머 업데이트

	if(elapsedTime < fireInterval)	//타이머처리
	{
		return;
	}

	elapsedTime = 0.f;	//타이머 초기화
	fireInterval = RandomPercent(1.f,2.f);

	refLevel->AddActor(new EnemyBullet(Vector2(position.x+ (width /2),position.y),refLevel));	//Engine::Get().AddActor(new EnemyBullet(Vector2(position.x+width /2,position.y),refLevel));
}