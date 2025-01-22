#include "Game.h"

#include "Level/MenuLevel.h"
#include "Level/GameLevel.h"
#include "Level/GameLevel_ABC.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;

	menuLevel = new MenuLevel();
	LoadLevel(menuLevel);
	gameLevel_sokoban = new GameLevel();
	gameLevel_ABC = new GameLevel_ABC();

	playHistory = new PlayHistory();
}

Game::~Game()
{
	if(showMenu)
	{
		backLevel = nullptr;
		mainLevel = nullptr;
	} else
	{
		mainLevel = nullptr;
	}

	delete menuLevel;
	menuLevel = nullptr;

	if(gameLevel_sokoban)
	{
		delete gameLevel_sokoban;
		gameLevel_sokoban = nullptr;
	}

	if(gameLevel_ABC)
	{
		delete gameLevel_ABC;
		gameLevel_ABC = nullptr;
	}

	if(playHistory)
	{
		delete playHistory;
		playHistory = nullptr;
	}
}

//백 레벨이랑,진입할 레벨이 같으면, 같은거 / 다르면, 다른거
bool Game::isSameBackLevel(Level * nextGameLevel)
{
	if(backLevel == nextGameLevel)
	{
		return true;
	}
	return false;
}

void Game::StartGame_Sokoban()
{
	system("cls");
	showMenu = !showMenu;
	//소코반 재입장 아니라면,
	if(showMenu ||  !isSameBackLevel(gameLevel_sokoban))
	{
		Game::Get().SetShowMenu(false);

		backLevel = mainLevel;
		mainLevel = gameLevel_sokoban;
	}
	//소코반 재입장이면,
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

void Game::SaveFile(){ //@세윤쌤 질문
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

void Game::StartGameSetPlayer_ABC()
{
	system("cls");
	//Clear();
	char	name[100];
	char comment[512];;

	std::cout << " 이름을 입력하세요 :   ";
	std::cin >> name;

	std::cout << " 시작 전 남기고픈 말은?  ";
	std::cin >> comment;

	auto level = dynamic_cast<GameLevel_ABC*>(gameLevel_ABC);
	if(level)
	{
		if(level->IsGameOver())
		{
			delete level;
			level = nullptr;

			level = new GameLevel_ABC();
		}

		level->SetPlayer(name,comment);
	}

	StartGame_ABC();
}
void Game::StartGame_ABC_TESTER()
{
	auto level = dynamic_cast<GameLevel_ABC*>(gameLevel_ABC);

	if(level)
	{
		if(level->IsGameOver())
		{
			delete level;
			level = nullptr;

			level = new GameLevel_ABC();

			level->SetPlayer("RE-TESTER","comment : winwin again");
		}

		else
		{
			level->SetPlayer("TESTER","comment : winwin");
		}
	}

	StartGame_ABC();
}

void Game::StartGame_ABC()
{
	system("cls");
	//Clear();

	showMenu = !showMenu;
	if(showMenu ||!isSameBackLevel(gameLevel_ABC))
	{
		backLevel = mainLevel;
		mainLevel = gameLevel_ABC;

		Game::Get().SetShowMenu(false);
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

//void Game::StartGame()
//{
//	system("cls");
//	std::cout << "StartGame";
//}