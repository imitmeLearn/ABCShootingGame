#pragma once
//#include <Engine\Engine.h>
#include <Level\GameLevel_ABC.h>
class PlayerInfo;
class PlayHistory
{
public:

	PlayHistory();
	~PlayHistory();
	// 플레이 히스토리 생성
	void CreatePlayHistory(const char* name,const char* comment,const char* playTime,const char* endTime,int totalScore,int hitCount,int dodgeCount);
	void CreatePlayHistory(const char* name,const char* comment);
	void CreatePlayHistory(const char* name,const char* comment,const char* playTime,const char* endTime);

	void CreatePlayHistory(Level * level);

	// 플레이 히스토리 출력
	void PrintHistory();

	//메뉴
	void PrintMenu();

	//히스토리 저장
	void Save(const char* filename);

	//히스토리 로드
	void Load(const char* filename);

private:
	PlayerInfo* playerInfos[1000] = {};			// 플레이어 저장을 위한 배열.

	int count = 0;
};