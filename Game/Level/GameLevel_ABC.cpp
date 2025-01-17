#include "GameLevel_ABC.h"

#include "Game/Game.h"

GameLevel_ABC::GameLevel_ABC()
{}

GameLevel_ABC::~GameLevel_ABC()
{}

void GameLevel_ABC::Update(float deltaTime)
{
	//@check : player 꺼가 먼저 실행됨.
	if(Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}
}

void GameLevel_ABC::Draw()
{
	std::cout << name << comment <<"\n";
}

void GameLevel_ABC::SetPlayer(const char* name,const char* comment)
{
	if(this->name != nullptr)
	{
		delete[] this->name;
	}
	if(this->comment != nullptr)
	{
		delete[] this->comment;
	}

	if(name != nullptr)
	{
		size_t length = strlen(name) + 1;
		this->name = new char[length];
		strcpy_s(this->name,length,name);
	}
	if(comment != nullptr)
	{
		size_t length = strlen(comment) + 1;
		this->comment = new char[length];
		strcpy_s(this->comment,length,comment);
	}

	std::cout<<"SetPlayer" << name << comment <<"\n";
}