#include "Game.h"

#include "Level/MenuLevel.h"
#include "Level/BeforeStartLevel.h"
#include "Level/GameLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;

	menuLevel = new MenuLevel();
	beforeStartLevel = new BeforeStartLevel();
	gameLevel_sokoban = new GameLevel();
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

void Game::StartGame_Sokoban()
{
	system("cls");
	showMenu = !showMenu;
	if(showMenu)
	{
		backLevel = mainLevel;
		mainLevel = gameLevel_sokoban;
	}

	else
	{
		mainLevel = backLevel;
	}
}
void Game::StartGame_mini()
{
	system("cls");
	std::cout << "StartGame_mini";
}

void Game::SaveFile(){
	playHistory->Load("Save.txt");		// 저장된 데이터 로드.
	char cStrfTime[64];

	__time64_t now2 = _time64(nullptr);
	tm tm_2;
	gmtime_s(&tm_2,&now2);

	strftime(cStrfTime,64,"%Y년 %m월 %d일 %H시 %M분 %S초\n",&tm_2);
	std::cout << "SaveFile - 시간: "<<cStrfTime;

	playHistory->CreatePlayHistory("테스터","잘한다~");	//저장 테스트
	playHistory->CreatePlayHistory("TEST","GOOD~","없음",cStrfTime);	//저장 테스트

	playHistory->Save("Save.txt");		// 프로그램 종료 시 파일 저장.
}

void Game::SetPlayerInfo()
{
	system("cls");
	//Clear();
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

void Game::StartGame()
{
	system("cls");
	std::cout << "StartGame";
}