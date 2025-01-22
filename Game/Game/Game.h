#pragma once

#include <Engine/Engine.h>
#include "Info\PlayHistory.h"

class Game: public Engine
{
public:
	Game();
	~Game();

	bool isSameBackLevel(Level* nextGameLevel);

	void ToggleMenu();
	void StartGameSetPlayer_ABC();
	void StartGame_ABC_TESTER();
	void StartGame_ABC();
	void LoadFile();
	//void SaveFile();
	void SaveFile(Level* level);
	void StartGame_Sokoban();
	//void StartGame();
	void StartGame_mini();

	static Game& Get() {
		return *instance;
	}

	void SetShowMenu(bool isOn)
	{
		showMenu = isOn;
	}
private:
	bool showMenu = false;

	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

	Level* gameLevel_ABC = nullptr;
	Level* gameLevel_sokoban = nullptr;

	Level* historyLevel = nullptr;

	PlayHistory* playHistory = nullptr;
private:

	static Game* instance;
};