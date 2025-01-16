#pragma once
#include <Level/Level.h>
#include <Math/Vector2.h>

class DrawableActor ; //전방선언
class Player;
class Box;
class Target;
class GameLevel: public Level
{
	RTTI_DECLARATIONS(GameLevel,Level)
public:
	GameLevel();

	virtual void Update(float deltaTime) override;

	//레벨 그리기 함수
	virtual void Draw() override;

	//플레이어 이동 가능하지 확인하는 함수
	bool CanPlayerMove(const Vector2& position);

private:
	//박스를 옮긴 뒤 게임을 클리어 했는지 확인하는 함수.
	bool CheckGameClear();

private:
	List <DrawableActor*> map;	//벽 땅 액터 배열
	List <Box*> boxes;			//박스 액터
	List <Target*> targets;		//타겟 액터
	Player* player = nullptr;	//플레이어 액터
	bool isGameClear = false;	//게임 클리어 변수
};