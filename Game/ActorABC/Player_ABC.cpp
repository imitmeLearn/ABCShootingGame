#include "Player_ABC.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel_ABC.h"

#include "ActorABC/ABCBullet.h"
#include "ActorABC/Stepper.h"

Player_ABC::Player_ABC(const Vector2 & position,GameLevel_ABC * level)
//:DrawableActor("★"),refLevel(level)
	:DrawableActor("P"),refLevel(level)
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
		Actor* actor = refLevel->SteponActor(position);

		if(nullptr == actor)
		{
			return;
		}

		Stepper* curr =	dynamic_cast<Stepper*> (actor); //@세윤쌤 : 이렇게 막 형변환 해도 됨?

		switch(curr->GetType())
		{
		case StepperType::None:
		break;
		case StepperType::CurrPos:
		{
			Vector2 bulletPosition(position.x + (width/2),position.y  /*-1*/);

			//ABCBullet* abcBullet = new ABCBullet(bulletPosition,refLevel);  		//Engine::Get().AddActor(new ABCBullet(bulletPosition));
			//refLevel->SetActors_Bullets(abcBullet);
			refLevel->AddActor(new ABCBullet(bulletPosition,refLevel));
		}
		break;
		case StepperType::OtherPos:
		{
			actor = refLevel->GetShooterActor(curr->GetIndex());
			if(actor == nullptr)
			{
				refLevel->myDebugMsg("GetShooterActor-  인덱스에 해당하는 객체 없음\n"); //@지우기 - 확인후

				return;
			}
			Vector2 bulletPosition(actor->Position().x + (width/2),actor->Position().y  /*-1*/);

			ABCBullet* abcBullet = new ABCBullet(bulletPosition,refLevel);  		//Engine::Get().AddActor(new ABCBullet(bulletPosition));
			//refLevel->SetActors_Bullets(abcBullet);
			refLevel->AddActor(abcBullet);
		}
		break;
		case StepperType::AllRight:
		break;
		case StepperType::AllLeft:
		break;
		default:
		break;
		}
	}
}