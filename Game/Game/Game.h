#pragma once

#include <Engine/Engine.h>

class Game: public Engine
{
public:
	Game();
	~Game();

	void ToggleMenu();
	void SetPlayerInfo();

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

	Level* beforeStartLevel = nullptr;
	Level* historyLevel = nullptr;

private:
	static Game* instance;
};