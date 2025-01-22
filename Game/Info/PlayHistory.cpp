#include "PlayHistory.h"
#include "PlayerInfo.h"
#include <iostream>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

//// 메모리 해제 함수.   //이미 엔진에 있따.
//template<typename T>
//void SafeDelete(T* pointer)
//{
//	if(pointer != nullptr)
//	{
//		delete pointer;
//	}
//}

PlayHistory::PlayHistory()
	:count(0)
{}

PlayHistory::~PlayHistory()
{
	for(int ix = 0; ix < count; ++ix)		// 메모리 해제.
	{
		SafeDelete(playerInfos[ix]);
	}
}

void PlayHistory::CreatePlayHistory(const char* name,const char* comment,const char* playTime,const char* endTime,int totalScore,int hitCount,int dodgeCount)
{
	playerInfos[count] = new PlayerInfo(name,comment,playTime,endTime,totalScore,hitCount,dodgeCount);
	++count;
}

void PlayHistory::CreatePlayHistory(const char * name,const char * comment)
{
	std::cout << "CreatePlayHistory " <<name << "  " << comment<<" \n";

	playerInfos[count] = new PlayerInfo(name,comment,"00:00:00","2025.00.00",99999,99999,99999);
	++count;
}
void PlayHistory::CreatePlayHistory(const char * name,const char * comment,const char * playTime,const char * endTime)
{
	std::cout << "CreatePlayHistory " <<name << "  " << comment<<" \n";

	playerInfos[count] = new PlayerInfo(name,comment,playTime,endTime,99999,99999,99999);
	++count;
}
void PlayHistory::CreatePlayHistory(Level* level)
{
	auto*	gameLevel = dynamic_cast<GameLevel_ABC*>(level);

	if(!gameLevel)
	{
		return;
	}

	playerInfos[count] = new PlayerInfo(gameLevel->GetName(),gameLevel->GetComment(),gameLevel->GetPlayTime()
		,gameLevel->GetEndTime(),gameLevel->GetTotalScore(),gameLevel->GetHitCount(),gameLevel->GetDodgeCount());

	++count;
}
void PlayHistory::PrintMenu()
{
	// 메뉴 목록 출력.
	std::cout << "\n\n==== ABC SHOOTING GAME ====\n";
	std::cout << "1. 플레이 하기 \n";
	std::cout << "2. 플레이 히스토리 보기 \n";
	std::cout << "9. 프로그램 종료\n";
	std::cout << "\n 숫자를 입력 하세요 :  ";
}

void PlayHistory::Save(const char* filename)
{
	int size = 2048 * 10;
	char buffer[2048 * 10];		// 저장할 데이터 생성.
	memset(buffer,0,size);
	for(int ix = 0; ix < count; ++ix)
	{
		// 각 계좌별로 문자열 데이터로 직렬화.
		const char* data = playerInfos[ix]->Serialize();
		strcat_s(buffer,data);
		delete data;
	}

	// 파일 저장.
	FILE* file = nullptr;
	fopen_s(&file,filename,"wb");
	if(file)
	{
		std::cout << "\n 파일 저장 \n ";

		fwrite(buffer,strlen(buffer) + 1,1,file);
		fclose(file);
	}
}

void PlayHistory::Load(const char * filename)
{
	FILE* file = nullptr;
	fopen_s(&file,filename,"rb");
	if(file)
	{
		fseek(file,0,SEEK_END);
		size_t length = ftell(file);
		if(length == 0)
		{
			fclose(file);
			return;
		}

		rewind(file);

		// 파일에서 읽은 데이터를 임시 저장할 버퍼.
		char buffer[2048];
		while(!feof(file))
		{
			std::cout << "\n 파일 로드 \n";

			// 한 줄씩 읽기.
			fgets(buffer,2048,file);

			// 정보 변수.
			int type = 1111;
			char name[256];
			char comment[256];
			char playTime[256];
			char endTime[256];
			int totalScore = 0;
			int hitCount = 0;
			int dodgeScore = 0;

			sscanf_s (
				buffer
				,"%d - name : %s comment : %s playTime: %s endTime: %s  --- totalScore : %d ( hitCount: %d   dodgeCount: %d ) \n"
				//,"%d - name : %s | comment : %s | playTime: %s | EndTime: %s --------------------------- totalScore : %d ( Hit Count: %d , Dodge Count: %d )"
				,&type,name,256,comment,256,playTime,256,endTime,256,&totalScore,&hitCount,&dodgeScore
			);

			// 생성 후 추가.
			playerInfos[count++] = new PlayerInfo(name,comment,playTime,endTime,totalScore,hitCount,dodgeScore);
		}

		// 파일 닫기.
		fclose(file);
	}
}