#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Container/List.h"

//전방선언
class Actor;
class ENGINE_API Level: public RTTI
{
	RTTI_DECLARATIONS(Level,RTTI)	//메크고, 문자로 인식, 오타x //RTTI 정의
public:
	Level();
	virtual ~Level();

	void AddActor(Actor* newActor);			//엑터추가

	//삭제 요청이 된 액터를 정리하는 함수
	//void DestroyActor();	//ProcessAddedandDestroyedActor 로 대체
	void ProcessAddedandDestroyedActor();

	virtual void Update(float deltaTime);	//루프
	virtual void Draw();					//루프
protected:

	List<Actor*> actors;		//게임 공간에 배치되는 물체(액터)배열 (자료구조로 묶어야 하지만, 약식으로)
	Actor* addRequestedActor = nullptr;	//프레임 추가 엑터 수1개 가 된것임??
};
