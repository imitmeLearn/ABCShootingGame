#include "PreCompiledHeader.h"

#include "Level.h"
//#include "../Actor/Actor.h"
#include "Actor/Actor.h"

Level::Level(){}

Level::~Level()
{
	for(Actor* actor:actors)//메모리 해제.//
	{
		delete actor;
	}
}

void Level::AddActor(Actor* newActor)
{
	//actors.PushBack(newActor);
	addRequestedActor = newActor;
}

void Level::ProcessAddedandDestroyedActor()
{
	for(int ix = 0; ix < actors.Size(); )		//엑터 순회 후
	{
		if(actors[ix]->isExpired)
		{
			delete	actors[ix];
			actors[ix] = nullptr;
			actors.Erase(ix);
			continue;
		}

		++ix;				//똑같은 인덱스가, 밀리니까. 당겨지니까, 인덱스 고정해서, 다시 처리- 비교처리
	}
	if(addRequestedActor)
	{
		actors.PushBack(addRequestedActor);
		addRequestedActor = nullptr;
	}
}

void Level::Update(float deltaTime)
{
	for(Actor* actor : actors) 	//레벨에 포함된 액터를 순회하면서, 함수호출
	{
		if(!actor->isActive || actor -> isExpired)		//엑터비활성화 상태이거나, 삭제 요청된 경우 건너뛰기
		{
			continue;
		}
		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	for(Actor* actor : actors) 	//레벨에 포함된 액터를 순회하면서, 함수호출
	{
		if(!actor->isActive || actor -> isExpired)		//엑터비활성화 상태이거나, 삭제 요청된 경우 건너뛰기
		{
			continue;
		}
		actor->Draw();
	}
}