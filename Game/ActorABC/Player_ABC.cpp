#include "Player_ABC.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel_ABC.h"

Player_ABC::Player_ABC(const Vector2 & position,GameLevel_ABC * level)
	:DrawableActor("★"),refLevel(level)
{
	this->position = position;	//위치 설정
	color = Color::White;		//색상 설정
}

void Player_ABC::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if(Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();	//Engine::Get().QuitGame();
	}
}