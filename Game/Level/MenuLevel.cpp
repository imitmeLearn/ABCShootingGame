﻿#include "MenuLevel.h"
#include "Game/Game.h"

MenuLevel::MenuLevel()
{
	Engine::Get().SetCursorType(CursorType::NoCursor);//커서 감추기

	menuItems.PushBack(new MenuItem("Start Game",[]() { Game::Get().StartGameSetPlayer_ABC(); }));
	menuItems.PushBack(new MenuItem("Start Game-TESTER",[]() { Game::Get().StartGame_ABC_TESTER(); }));
	menuItems.PushBack(new MenuItem("Start Game - sokoban",[]() { Game::Get().StartGame_Sokoban(); }));
	//menuItems.PushBack(new MenuItem("Start Game_mini",[]() { Game::Get().StartGame_mini(); }));
	menuItems.PushBack(new MenuItem("--HISTORY-- 누르면 지금은 오류남",[]() { Game::Get().LoadFile(); }));
	menuItems.PushBack(new MenuItem("Resume Game",[]() { Game::Get().ToggleMenu(); }));
	menuItems.PushBack(new MenuItem("Quit Game",[]() { Game::Get().QuitGame(); }));
	//menuItems.PushBack(new MenuItem("Save History",[]() { Game::Get().SaveFile(); }));

	length = menuItems.Size();
}

MenuLevel::~MenuLevel()
{
	for(auto* item : menuItems)
	{
		delete item;
	}
}

void MenuLevel::Update(float deltaTime)
{
	//if(Game::Get().GetKeyDown(VK_ESCAPE))
	//{
	//	Game::Get().ToggleMenu();
	//}

	if(Game::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if(Game::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if(Game::Get().GetKeyDown(VK_RETURN))
	{
		menuItems[currentIndex]->onSelected();
	}
}

void MenuLevel::Draw()
{
	Super::Draw();

	Engine::Get().SetCursorPosition(0,0);

	SetColor(unselectedColor);
	Log("========ABCShooting Game========\n\n");

	for(int ix = 0; ix < length; ++ix)
	{
		SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		Log("%s\n",menuItems[ix]->menuText);
	}
}