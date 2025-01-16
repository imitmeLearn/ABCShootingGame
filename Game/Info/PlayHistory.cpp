#include "PlayHistory.h"
#include "PlayerInfo.h"
#include <iostream>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

// 메모리 해제 함수.
template<typename T>
void SafeDelete(T* pointer)
{
	if(pointer != nullptr)
	{
		delete pointer;
	}
}

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

void PlayHistory::PrintMenu()
{
	// 메뉴 목록 출력.
	std::cout << "==== ABC SHOOTING GAME ====\n";
	std::cout << "1. 플레이 하기 \n";
	std::cout << "2. 플레이 히스토리 보기 \n";
	std::cout << "9. 프로그램 종료\n";
	std::cout << "\n 숫자를 입력 하세요 :  ";
}

void PlayHistory::Save(const char* filename)
{
	char buffer[2048];		// 저장할 데이터 생성.
	memset(buffer,0,2048);
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
		// 파일에서 읽은 데이터를 임시 저장할 버퍼.
		char buffer[256];
		while(!feof(file))
		{
			std::cout << "\n 파일 로드 \n";

			// 한 줄씩 읽기.
			fgets(buffer,256,file);

			// 정보 변수.
			int type = 0;
			char name[256];
			char comment[256];
			char playTime[256];
			char endTime[256];
			int totalScore = 0;
			int hitCount = 0;
			int dodgeScore = 0;

			sscanf_s (
				buffer
				,"%d - 이름 : %s | 코멘트 : %s | 플레이타임: %s | 플레이 종료 시간: %s --------------------------- 총 점수 : %d ( 파괴 수: %d , 회피 수: %d )"
				,&type,name,256,comment,256,playTime,256,endTime,256,&totalScore,&hitCount,&dodgeScore
			);

			// 생성 후 추가.
			playerInfos[count++] = new PlayerInfo(name,comment,playTime,endTime,totalScore,hitCount,dodgeScore);
		}

		// 파일 닫기.
		fclose(file);
	}
}