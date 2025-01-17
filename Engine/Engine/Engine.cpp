#include "PreCompiledHeader.h"

#include "Engine.h"
#include <Windows.h>	//이거 사용하려면, 속성>링커>입력>종속성 맨 압에 winmm.lib; 추가
#include <iostream>

#include "Level/Level.h"
#include "Actor/Actor.h"
#include <time.h>

Engine* Engine::instance = nullptr;	// 스태틱 변수 초기화 //instance 범위 엔진 안에 instance

Engine::Engine()
	:quit(false),mainLevel(nullptr),screenSize(40,25)
{
	srand((unsigned int)time (nullptr));		//랜덤 시드 설정

	instance = this;	//생성할 때, 싱글톤 같이 구현하는것 좋아한다.

	SetTargetFrameRate(60.f);		//기본 타겟 프레임 속도 설정

	//화면 지울 때 사용할 버퍼 초기화
	emptyStringBuffer = new char[(screenSize.x+1)*screenSize.y+1];			//1. 버퍼 크기 할당-가로세로 1칸씩 더 필요 : 개행문자\n -다음줄가니까,널문자\0 - 문자열이니까
	memset(emptyStringBuffer,' ',(screenSize.x+1)*screenSize.y + 1);		//1.1 버퍼 덮어쓰기
	for(int y = 0; y < screenSize.y; y++)									//2. 값 할당
	{
		//for(int x = 0; x < screenSize.x; x++)						//1.1 버퍼 덮어쓰기 로 대체
		//{
		//	emptyStringBuffer[(y*(screenSize.x+1)) +x] = ' ';  //인덱스 계산 잘하기
		//}
		emptyStringBuffer[(y*(screenSize.x+1)) +screenSize.x] = '\n';	//개행문자  	//각 줄 끝에 개행 문자 추가.
	}
	emptyStringBuffer[(screenSize.x+1)*(screenSize.y)] = '\0';			//널문자

	#if _DEBUG					//디버깅
	char buffer[2048];
	strcpy_s(buffer,2048,emptyStringBuffer);
	#endif
}

Engine::~Engine()
{
	//메인 레벨 메모리 해제
	if(mainLevel != nullptr)
	{
		delete mainLevel;
	}

	delete[] emptyStringBuffer;		//클리어 버퍼 삭제
}

void Engine::Run()
{
	////시작 타임 스탬프 저장
	//unsigned long currentTime = timeGetTime(); // 정밀도 단위:밀리세컨트 (1/1000초)/ 프레임 부정확함.
	//unsigned long previousTime = 0;

	//CPU 시계사용-> 메인보드 시계가 있다. //재활용
	//시스템 시계 (timeGetTime와 다르게)고해상도 카운터임. //메인보드에있는시계 - 정밀도단위:천만
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	//시작 시간 및 이전 시간을 위한 변수 //여러번 씀
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	//__int64 currentTime = time.QuadPart; // __int64   int64_t  같은거
	int64_t currentTime = time.QuadPart;
	int64_t previousTime = currentTime;		//첫 프레임 엔진 루프에서, 건너뛸 수 있도록,

	//	float targetFrameRate = 60.f;	//프레임제한
	//float targetOneFrameTime = 1.0f / targetFrameRate; 	//프레임 시간 계산

	while(true)	//Game=Loop.
	{
		if(quit)
		{
			break;
		}
		//현재 프레인 시간 저장
		//currentTime = timeGetTime();
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		//프레임 시간 계산
		//float deltaTime = static_cast<float>(currentTime - previousTime) / 1000.0f;
		float deltaTime
			= static_cast<float>(currentTime - previousTime) / static_cast<float>(frequency.QuadPart);

		//float targetOneFrameTime = 1.0f / targetFrameRate; 	//프레임 시간 계산 //동적으로

		if(deltaTime >= targetOneFrameTime)
		{
			ProcessInput();
			if(shouldUpdate)				//업데이트 가능한 상태에서만, 프레임 업데이트 처리
			{
				Update(deltaTime);
				Draw();
			}

			SavePreviouseKeyStates();		//키 상태 저장

			previousTime = currentTime;		//이전 프레임 시간 저장
			if(mainLevel)					//엑터 정리 : 삭제요청된 엑터 정리
			{
				mainLevel -> ProcessAddedandDestroyedActor();//프레임처리하고, 삭제요청된거 한번에 모아서 처리될거다.
			}
			shouldUpdate = true;			//프레임 활성화
		}
		//sleep(1);
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	//기존 레벨이 있다면, 삭제 후 교체

	mainLevel = newLevel;		//메인 레벨 설정
}

void Engine::AddActor(Actor* newActor)
{
	if(mainLevel == nullptr)					//예외처리
	{
		return;
	}

	shouldUpdate = false;
	mainLevel-> AddActor(newActor);				//레벨에 엑터추가
}

void Engine::DestroyActor(Actor* targetActor)
{
	if(mainLevel == nullptr)	//예외처리
	{
		return;
	}

	shouldUpdate = false;
	targetActor ->Destroy();
}

void Engine::SetCursorType(CursorType cursorType)
{
	CONSOLE_CURSOR_INFO info = {};									//1. 속성 구조체 설정

	switch(cursorType)												//타입별로 구조체 값 설정
	{
	case CursorType::NoCursor:
	info.dwSize = 1;
	info.bVisible = FALSE;
	break;

	case CursorType::SolidCursor:
	info.dwSize = 100;
	info.bVisible = TRUE;
	break;

	case CursorType::NormalCursor:
	info.dwSize = 20;
	info.bVisible = TRUE;
	break;

	default:
	break;
	}

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);	//2. 설정 //자주 안쓰기에, 따로 뺴지 않고 씀
}

void Engine::SetCursorPosition(const Vector2& position)
{
	SetCursorPosition(position.x,position.y);
}

void Engine::SetCursorPosition(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {static_cast<short>(x),static_cast<short>(y)};
	SetConsoleCursorPosition(handle,coord);
}

void Engine::SetTargetFrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1.0f / targetFrameRate;
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown; // 눌려, 안눌렸는데,
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown; // 안눌려, 눌렸었는데
}

void Engine::QuitGame()
{
	quit = true;
}

Engine& Engine::Get()
{
	return *instance; //싱글톤 객체 반환
}

void Engine::ProcessInput()
{
	for(int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].isKeyDown = (GetAsyncKeyState(ix) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	//if (GetKeyDown(VK_ESCAPE))		//esc 키로 게임 종료 //이건 강제종료
	//{
	//	QuitGame();
	//}

	if(mainLevel != nullptr)		//레벨 업데이트
	{
		mainLevel->Update(deltaTime);
	}

	//	std::cout << "currentTime : " << timeGetTime() << "   deltaTime : " << deltaTime << ",  FPS : " << (1.0f / deltaTime) << "\n";
}

void Engine::Clear()
{
	SetCursorPosition(0,0);								//화면 (0,0)으로 이동

	// 화면지우기 - 기존 문자열 용도에서,  emptyStringBuffer 용도로 교체
	std::cout << emptyStringBuffer;

	//int height = 25;						//화면지우기 -기존 문자열 용도
	//for(int ix = 0; ix < height; ix++)
	//{
	//	Log("                               \n");			//화면지우기	//문자 수 화면 지울 때 중요
	//}

	SetCursorPosition(0,0);									// 화면의 (0,0)으로 이동.
}

void Engine::Draw()
{
	//Clear();
	if(mainLevel != nullptr)	//레빌그리기
	{
		mainLevel->Draw();
	}
}

void Engine::SavePreviouseKeyStates()
{
	for(int ix = 0; ix < 255; ix++)
	{
		keyState[ix].wasKeyDown = keyState[ix].isKeyDown;
	}
}