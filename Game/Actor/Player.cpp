#include "Player.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"

Player::Player(const Vector2 & position,GameLevel* level)
	:DrawableActor("P"),refLevel(level)
{
	this->position = position;	//위치 설정
	color = Color::White;		//색상 설정
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if(Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();	//Engine::Get().QuitGame();
	}
	if(Engine::Get().GetKeyDown(VK_LEFT))
	{
		if(refLevel -> CanPlayerMove(Vector2(position.x - 1,position.y)))		//이동가능한지 확인
		{
			position.x -= 1;
		}
	}

	if(Engine::Get().GetKeyDown(VK_RIGHT))
	{
		if(refLevel -> CanPlayerMove(Vector2(position.x + 1,position.y)))		//이동가능한지 확인
		{
			position.x += 1;
		}
	}

	if(Engine::Get().GetKeyDown(VK_UP))
	{
		if(refLevel -> CanPlayerMove(Vector2(position.x,position.y - 1)))		//이동가능한지 확인
		{
			position.y -= 1;
		}
	}

	if(Engine::Get().GetKeyDown(VK_DOWN))
	{
		if(refLevel -> CanPlayerMove(Vector2(position.x,position.y + 1)))		//이동가능한지 확인
		{
			position.y += 1;
		}
	}
}