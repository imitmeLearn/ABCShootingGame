#pragma once

#include "Level/Level.h"

class DrawableActor ; //전방선언
class Player_ABC;
class GameLevel_ABC: public Level
{
	RTTI_DECLARATIONS(GameLevel_ABC,Level)

public:
	GameLevel_ABC();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	//플레이 하는 플레이어 이름과 코멘트 정보 넘기기
	void SetPlayer(const char* name,const char* comment) ;


private:
	char* name = nullptr;		// 플레이어 이름
	char* comment= nullptr;		// 플레이어 코멘트

	List <DrawableActor*> map;	//벽 땅 액터 배열

	Player_ABC* player_ABC = nullptr;	//플레이어 액터
};