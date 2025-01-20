#pragma once

#include "Level/Level.h"
#include <Math/Vector2.h>

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

	//플레이어 이동 가능하지 확인하는 함수
	bool CanPlayerMove(const Vector2& position);

	//액터 추가 0 그리는 용도?
	void SetActors_Bullets(Actor *&& actor);

	//화면 큰 경계 찾기
	Vector2 GetMaxXY();
	Vector2 SetMaxXY();

	//플레이어가 기믹(스텝) 위에 있는지 확인하는 함수
	Actor* CanPlayerShoot(const Vector2& position);

private:
	char* name = nullptr;		// 플레이어 이름
	char* comment= nullptr;		// 플레이어 코멘트

	List <DrawableActor*> map;	//벽 땅 액터 배열
	List <DrawableActor*> shooters;	//벽 땅 액터 배열
	List <DrawableActor*> steppers;	//벽 땅 액터 배열
	List <DrawableActor*> bullets;	//벽 땅 액터 배열

	Player_ABC* player_ABC = nullptr;	//플레이어 액터
	bool isGameClear = false;	//게임 클리어 변수

	int maxX = 0;
	int maxY = 0;
	Vector2 maxXY;
};