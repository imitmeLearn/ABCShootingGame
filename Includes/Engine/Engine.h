#pragma once

//#include "PrecompiledHeader.h"
#include "Core.h"
#include "Math/Vector2.h"

struct KeyState						//입력 처리를 위한 구조체
{
	bool isKeyDown = false;			//현재 프레임에 키가 눌렸는지 확인
	bool wasKeyDown = false;		//이전 키 눌렸는지 확인
};

enum class CursorType				// 커서의 종류를 설정할 때 사용할 열거형.
{
	NoCursor,
	SolidCursor,
	NormalCursor
};
class Level; //전방선언
class Actor; //전방선언
class ENGINE_API Engine
{
public:
	Engine();
	virtual ~Engine();				//엔진 실행 함수
	void Run();

	void LoadLevel(Level* newLevel);	//레벨 추가 함수
	//void LoadLevel(Level* newLevel);	//레벨 추가 함수
	void AddActor(Actor* newActor);		//엑터 추가 삭제 함수
	void DestroyActor(Actor* targetActor);		//엑터 추가 삭제 함수

	void SetCursorType(CursorType cursorType);
	void SetCursorPosition(const Vector2& position);	//화면 좌표 관련 함수
	void SetCursorPosition(int x,int y);				//화면 좌표 관련 함수

	inline Vector2 ScreenSize() const					// 화면크기 변환함수
	{
		return screenSize;
	}

	void SetTargetFrameRate(float targetFrameRate);		//타겟 프레임 속도 설정 함수

	bool GetKey(int key);			// 엔진 입력 관련 함수
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	void QuitGame();				//엔진 종료 함수

	static	Engine& Get();	//접근용, 엔진 포인터로 반환, const 레퍼런스! 대신 static

protected:
	void ProcessInput();			//입력 처리
	void Update(float deltaTime);	//tick();
	void Clear();					//화면 지우기.
	void Draw();					//Render();
	void SavePreviouseKeyStates();	//이전 프레임 키 상태 저장

protected:
	float targetFrameRate = 60.0f;		//타겟 프레임 변수
	float targetOneFrameTime = 0.f;		//한 프레임 시간 값*(단위  초)
	bool quit;						//종료할 때 설정할 변수
	KeyState keyState[255];			//키 상태 저장 배열
	static Engine* instance;		//싱글통 구현을 위한

	Level* mainLevel;
	bool shouldUpdate = true;		//프레임을 업데이트 해야 하는지 여부를 나타내는 변수
	Vector2 screenSize;				//화면 크기
	char* emptyStringBuffer = nullptr;  //화면 지울 때 사용할 버퍼.(Buffer / Blob:블롭_바이너리 덩어리)
};