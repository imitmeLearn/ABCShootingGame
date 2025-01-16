#pragma once

#include <Engine/Engine.h>

class Game: public Engine
{
public:
	Game();
	~Game();

	void ToggleMenu();

	static Game& Get() {
		return *instance;
	}

private:
	bool showMenu = false;

	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;
	Level* historyLevel = nullptr;

private:
	static Game* instance;
};