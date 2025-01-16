#include "PlayerInfo.h"
#include <string.h>
#include <iostream>

PlayerInfo::PlayerInfo(const char* name,const char* comment,const char* playTime,const char* endTime,int totalScore,int hitScore,int dodgeScore)
	:name(nullptr),comment(nullptr),playTime(nullptr),endTime(nullptr),totalScore(totalScore),hitCount(hitScore),dodgeCount(dodgeScore)
{
	if(name != nullptr)
	{
		size_t length = strlen(name) + 1;
		this->name = new char[length];
		strcpy_s(this->name,length,name);
	}
	if(comment != nullptr)
	{
		size_t length = strlen(comment) + 1;
		this->comment = new char[length];
		strcpy_s(this->comment,length,comment);
	}
	if(playTime != nullptr)
	{
		size_t length = strlen(playTime) + 1;
		this->playTime = new char[length];
		strcpy_s(this->playTime,length,playTime);
	}
	if(endTime != nullptr)
	{
		size_t length = strlen(endTime) + 1;
		this->endTime = new char[length];
		strcpy_s(this->endTime,length,endTime);
	}
}

PlayerInfo::~PlayerInfo()
{
	delete[] name;
	delete[] playTime;
	delete[] comment;
}

const char * PlayerInfo::Serialize()
{
	char* buffer = new char[256];
	snprintf(buffer,256,"이름 : %s | 코멘트 : %s | 플레이타임: %s | 플레이 종료 시간: %s --------------------------- 총 점수 : %d ( 파괴 수: %d , 회피 수: %d )\n"
		,name,comment,playTime,endTime,totalScore,hitCount,dodgeCount);
	return buffer;
}