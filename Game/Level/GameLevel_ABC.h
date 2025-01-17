#pragma once

#include "Level/Level.h"

class GameLevel_ABC: public Level
{
public:
	GameLevel_ABC();
	~GameLevel_ABC();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	void SetPlayer(const char* name,const char* comment) ;

private:
	char* name = nullptr;		// 플레이어 이름
	char* comment= nullptr;		// 플레이어 코멘트
};