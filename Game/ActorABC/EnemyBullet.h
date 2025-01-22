#pragma once
#include <Actor/DrawableActor.h>
#include <Level/GameLevel_ABC.h>

class EnemyBullet: public DrawableActor		// 적 탄약 클래스.
{
	RTTI_DECLARATIONS(EnemyBullet,DrawableActor)

public:
	EnemyBullet(const Vector2& position,GameLevel_ABC* level);
	virtual void Update(float deltaTime) override;

private:

	float speed = 15.0f;		// 이동 관련 변수(속성).
	float yPosition = 0.0f;		// 이동 관련 변수(속성).

	GameLevel_ABC* refLevel = nullptr;
};