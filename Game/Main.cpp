#include <iostream>
#include <Engine\Engine.h>
#include <Level\MenuLevel.h>
#include "Game/Game.h"

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

	//기존
//Game game;
//game.LoadLevel(new GameLevel());
//game.Run();

	Game game;
	game.LoadLevel(new MenuLevel());
	game.Run();

	std::cout << "\n??????";
}