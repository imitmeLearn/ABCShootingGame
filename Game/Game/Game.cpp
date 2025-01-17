#include "Game.h"

#include "Level/MenuLevel.h"
#include "Level/BeforeStartLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;

	menuLevel = new MenuLevel();
	beforeStartLevel = new BeforeStartLevel();
}

Game::~Game()
{
	if(showMenu)
	{
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	} else
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	delete menuLevel;
	menuLevel = nullptr;
}

void Game::SetPlayerInfo()
{
	system("cls");
	//Clear();
	//
	std::cout << "	if(showMenu) 1" << showMenu;
	showMenu = !showMenu;
	if(showMenu)
	{
		std::cout << "	if(showMenu) 2";

		backLevel = mainLevel;
		mainLevel = beforeStartLevel;
	}

	else
	{
		mainLevel = backLevel;
	}
}

void Game::ToggleMenu()
{
	system("cls");
	//Clear();
	showMenu = !showMenu;
	if(showMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}

	else
	{
		mainLevel = backLevel;
	}
}