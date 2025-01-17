#pragma once
#include "Level/Level.h"

class BeforeStartLevel: public Level
{
	RTTI_DECLARATIONS(BeforeStartLevel,Level)
public:
	BeforeStartLevel();
	~BeforeStartLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
};
