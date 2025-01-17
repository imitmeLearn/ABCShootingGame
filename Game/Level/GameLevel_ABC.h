#pragma once

#include "Level/Level.h"

class DrawableActor ; //전방선언
class GameLevel_ABC: public Level
{
	RTTI_DECLARATIONS(GameLevel_ABC,Level)

public:
	GameLevel_ABC();
	~GameLevel_ABC();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	void SetPlayer(const char* name,const char* comment) ;

private:
	char* name = nullptr;		// 플레이어 이름
	char* comment= nullptr;		// 플레이어 코멘트

	List <DrawableActor*> map;	//벽 땅 액터 배열
};