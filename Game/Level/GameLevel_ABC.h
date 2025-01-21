#pragma once

#include <windows.h> // OutputDebugString 함수 사용
#include <cstdarg>   // va_list, va_start, va_end
#include <cstdio>    // vsnprintf
#include <cwchar> // vswprintf

#include "Level/Level.h"
#include <Math/Vector2.h>

class DrawableActor ; //전방선언
class Player_ABC;
class GameLevel_ABC: public Level
{
	RTTI_DECLARATIONS(GameLevel_ABC,Level)

public:
	GameLevel_ABC();

	// 출력창에 디버그 보여주기 : https://eteo.tistory.com/673
	void myDebugMsg(const char* format,...);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	//플레이 하는 플레이어 이름과 코멘트 정보 넘기기
	void SetPlayer(const char* name,const char* comment) ;

	//플레이어 이동 가능하지 확인하는 함수
	bool CanPlayerMove(const Vector2& position);

	//액터 추가 0 그리는 용도?
	void SetActors_Bullets(DrawableActor* actor);

	//화면 큰 경계 찾기
	Vector2 GetMaxXY();
	Vector2 SetMaxXY();

	//인덱트에 해당하는 슈터 액터
	Actor* GetShooterActor(int index);

	//플레이어가 기믹(스텝) 위에 있는지 확인하는 함수
	Actor* SteponActor(const Vector2& position);

	void SpawnEnemy(float deltaTime);

private:
	char* name = nullptr;		// 플레이어 이름
	char* comment= nullptr;		// 플레이어 코멘트

	List <DrawableActor*> map;	//벽 땅 액터 배열
	List <DrawableActor*> shooters;	//벽 땅 액터 배열
	List <DrawableActor*> steppers;	//벽 땅 액터 배열
	//List <DrawableActor*> bullets;	//벽 땅 액터 배열
	//List <DrawableActor*> enemies;	//벽 땅 액터 배열

	Player_ABC* player_ABC = nullptr;	//플레이어 액터
	bool isGameClear = false;	//게임 클리어 변수

	int maxX = 0;
	int maxY = 0;
	Vector2 maxXY;
};