#pragma once

#include <windows.h> // OutputDebugString 함수 사용
#include <cstdarg>   // va_list, va_start, va_end
#include <cstdio>    // vsnprintf
#include <cwchar> // vswprintf
#include <cmath>

#include "Level/Level.h"
#include <Math/Vector2.h>

class DrawableActor ; //전방선언
class Player_ABC;
class GameLevel_ABC: public Level
{
	RTTI_DECLARATIONS(GameLevel_ABC,Level)

public:
	GameLevel_ABC();
	~GameLevel_ABC();

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

	//플레이어 탄약과 적 충돌처리
	void ProcessCollisionPlayerBulletandEnemy();

	//플레이어와 적 충돌처리
	void ProcessCollisionPlayerAndEnemy();

	//플레이어가 기믹(스텝) 위에 있는지 확인하는 함수
	Actor* SteponActor(const Vector2& position);

	void SpawnEnemy(float deltaTime);

	char* GetName ()
	{
		if(name)
		{
			return name;
		}

		else
		{
			name = new char[5];
			strcpy_s(name,sizeof(name),"null");

			return name;
		}
	}
	char* GetComment ()
	{
		if(comment)
		{
			return comment;
		}

		else
		{
			comment = new char[5];
			strcpy_s(comment,sizeof(comment),"null");

			return comment;
		}
	}
	inline const char* GetPlayTime()
	{
		char tempBuffer[256] = {};
		int minutes = (int)(gamePlayTime / 60.0f);
		int seconds = (int)fmod(gamePlayTime,60.0f);
		sprintf_s(tempBuffer,256,"%d분 %d초",minutes,seconds);

		playTime = new char[strlen(tempBuffer) + 1];
		strcpy_s(playTime,strlen(tempBuffer) + 1,tempBuffer);

		return playTime;
	}

	char* GetEndTime()
	{
		SYSTEMTIME time;
		GetLocalTime(&time);

		char tempBuffer[256];
		sprintf_s(tempBuffer,256,"%d %d %d - %d %d %d",
			time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond
		);

		endTime = new char[strlen(tempBuffer) + 1];
		strcpy_s(endTime,strlen(tempBuffer) + 1,tempBuffer);
		endTime[strlen(tempBuffer)] = '\0';

		return endTime;
	}

	int GetTotalScore()
	{
		return totalScore;
	}

	int  GetHitCount()
	{
		return hitCount;
	}

	int  GetDodgeCount()
	{
		return dodgeCount;
	}

	void HitCount()
	{
		hitCount++;
		totalScore = hitCount * hitScore;
	}

	void DodgeCount()
	{
		dodgeCount++;
		totalScore = dodgeCount * dodgeScore;
	}

	//상단 UI
	void DrawPlayerInfo()
	{
		std::cout << " ====  Game_ABC SHOOTING  ====\n";
		std::cout << " 플레이어 이름 :   " << GetName()
			<< "  (  " << GetComment()<< "  )     "
			<< "   플레이 시간 ( " <<GetPlayTime()<< " ) "
			<< "   점수 :  " << GetTotalScore();
	}

	bool IsGameOver()
	{
		return	isGameOver;
	}

	bool IsSaveData()
	{
		return isSaveData;
	}
	void IsSaveData(bool isSave)
	{
		isSaveData = isSave;
	}

private:
	char* name = nullptr;			//이름
	char* comment = nullptr;			//코멘트
	char* playTime = nullptr ;		//플레이타임
	char* endTime = nullptr;		//플레이 종료 시간
	int totalScore = 0;
	int hitCount = 0;		//적 파괴 수
	int dodgeCount = 0;		//적 회피 수

	List <DrawableActor*> map;	//벽 땅 액터 배열
	List <DrawableActor*> shooters;	//벽 땅 액터 배열
	List <DrawableActor*> steppers;	//벽 땅 액터 배열
	//List <DrawableActor*> bullets;	//벽 땅 액터 배열
	//List <DrawableActor*> enemies;	//벽 땅 액터 배열

	Player_ABC* player_ABC = nullptr;	//플레이어 액터
	bool isGameOver = false;	//게임 클리어 변수

	int maxX = 0;
	int maxY = 0;
	Vector2 maxXY;

	int hitScore = 100;
	int dodgeScore = 100;
	int timeScore = 100;

	bool isSaveData = false;		//종료 시 게임저장 여부

	// 게임 시간 기록용 변수.
	float gamePlayTime = 0.0f;
};