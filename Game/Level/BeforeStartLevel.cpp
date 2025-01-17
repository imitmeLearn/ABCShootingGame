#include "BeforeStartLevel.h"
#include "Game/Game.h"

BeforeStartLevel::BeforeStartLevel()
{
	std::cout << "BeforeStartLevel 생성 \n";
}

BeforeStartLevel::~BeforeStartLevel()
{}

void BeforeStartLevel::Update(float deltaTime)
{
	//@check : player 꺼가 먼저 실행됨.
	if(Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}
}

void BeforeStartLevel::Draw()
{
	Super::Draw();
	std::cout << "BeforeStartLevel DRAW \n";
}