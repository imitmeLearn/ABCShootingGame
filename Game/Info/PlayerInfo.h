﻿#pragma once
#include <cstdio>

class PlayerInfo
{
public:
	PlayerInfo(const char* name,const char* comment,const char* playTime,const char* endTime,int totalScore,int hitScore,int dodgeScore);
	virtual ~PlayerInfo();

	// 문자열 직렬화(Serialization) 함수.
	virtual const char* Serialize();

	void PrintInfos()
	{
		printf
		(
			"\n name : %s   comment : %s   playTime: %s   endTime: %s  --- totalScore : %d ( hitCount: %d   dodgeCount: %d ) \n\n"
			,name,comment,playTime,endTime,totalScore,hitCount,dodgeCount
		);
	}

	bool IsNull()
	{
		if(name == nullptr)
		{
			return true;
		}

		return false;
	}

protected:
	char* name ;			//이름
	char* comment;			//코멘트
	char* playTime;		//플레이타임
	char* endTime;		//플레이 종료 시간
	int totalScore;		//적 파괴 수
	int hitCount;		//적 파괴 수
	int dodgeCount;		//적 회피 수

private:
	int timeBonus = 10;		//파괴 당 점수
	int hitBonus = 10;		//파괴 당 점수
	int dodgeBonus = 10;	//회피 당 점수
};