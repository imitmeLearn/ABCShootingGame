#include "Player_ABC.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel_ABC.h"

#include "ActorABC/ABCBullet.h"

Player_ABC::Player_ABC(const Vector2 & position,GameLevel_ABC * level)
	:DrawableActor("★"),refLevel(level)
	//:DrawableActor("P"),refLevel(level)
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

	if(Engine::Get().GetKeyDown(VK_SPACE))
	{
		std::cout<<" VK_SPACE\n";

		Vector2 bulletPosition(position.x + (width/2),position.y  /*-1*/);

		ABCBullet* abcBullet = new ABCBullet(bulletPosition);  		//Engine::Get().AddActor(new ABCBullet(bulletPosition));
		refLevel->SetActors(abcBullet);
	}
}