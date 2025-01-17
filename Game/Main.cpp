#include <iostream>
#include <Engine\Engine.h>
#include <Level\GameLevel.h>
#include <Level\MenuLevel.h>
//#include <Level\BeforeStartLevel.h>
#include "Game/Game.h"

#include "Info\PlayHistory.h"

// 열거형.
enum class MenuType
{
	Create = 1
	,History
	,TESTER7 = 7
	,TESTER8 = 8
	,Exit = 9
};

void ClearScreen() {
	system("cls");
}

int main()
{
	CheckMemoryLeak();

	PlayHistory* playHistory = new PlayHistory();
	playHistory->Load("Save.txt");		// 저장된 데이터 로드.

	int choice = 0;		// 메뉴 선택 입력 받기.
	MenuType menuType;		// 선택 메뉴 열거형 선언.
	char tempBuffer[100];		// 오류 확인을 위한 임시 값.
	char name[100];		// 플레이어 이름
	char comment[100];		// 플레이어 코멘트

	//기존
//Game game;
//game.LoadLevel(new GameLevel());
//game.Run();

	Game game;
	game.LoadLevel(new MenuLevel());
	game.Run();

	//while(true)
	//{
	//playHistory->PrintMenu();			// 사용자가 선택할 수 있는 메뉴 출력.

	//	std::cin >> tempBuffer;			// 임시 버퍼에 사용자 입력 저장.

	//	// 정수로 변환이 가능한 지 확인.
	//	if(choice = atoi(tempBuffer))
	//	{
	//		// 입력 값 확인.
	//		if(choice >= 1 && choice <= 10)
	//		{
	//			menuType = static_cast<MenuType>(choice);
	//			switch(menuType)
	//			{
	//			case MenuType::Create:
	//			std::cout << "\n 이름을 입력하세요 : ";
	//			std::cin >> name;

	//			std::cout << " 시작 전 남기고픈 말은?  ";
	//			std::cin >> comment;

	//			game.LoadLevel(new GameLevel());
	//			Game::Get().ToggleMenu();
	//			//game.LoadLevel(new GameLevel(),playHistory,name,comment);

	//			//game.LoadLevel(new GameLevel());
	//			//game.Run();
	//			//	playHistory->CreatePlayHistory(name,comment);	//@todo : 저장 테스트
	//			break;

	//			case MenuType::History:

	//			break;

	//			case MenuType::TESTER7:
	//			playHistory->CreatePlayHistory("테스터","잘한다~");	//저장 테스트

	//			break;
	//			case MenuType::TESTER8:
	//			playHistory->CreatePlayHistory("TEST","GOOD~");	//저장 테스트

	//			break;

	//			case MenuType::Exit:
	//			std::cout << " 게임종료  ";

	//			playHistory->Save("Save.txt");		// 프로그램 종료 시 파일 저장.

	//			delete playHistory;		// 메모리 해제.
	//			return 0;

	//			break;
	//			default:
	//			break;
	//			}
	//		}

	//		else
	//		{
	//			std::cout << "잘못 입력하셨습니다.\n";
	//		}
	//	}

	//	else
	//	{
	//		std::cout << "잘못 입력하셨습니다.\n";
	//	}
	//}
}