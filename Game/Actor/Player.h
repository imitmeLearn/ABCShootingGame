#pragma once

#include <Actor/DrawableActor.h>
class GameLevel;	//게임레벨 전방 선언
class Player: public DrawableActor
{
	RTTI_DECLARATIONS(Player,DrawableActor)
public:
	Player(const Vector2& position,GameLevel* level);
	virtual void Update(float deltaTime) override;
private:
	GameLevel* refLevel = nullptr;	//게임 레벨 참조 변수
};