#pragma once

#include <Actor/DrawableActor.h>
class Shooter: public DrawableActor
{
	RTTI_DECLARATIONS(Shooter,DrawableActor)
public:
	Shooter(const Vector2& position);

	void SetReImage(const char* image)
	{
		auto length = strlen(image) + 1;
		this->image = new char[length];
		strcpy_s(this->image,length,image);

		//너비 설정
		width = (int)strlen(image);

		index= (int)(char)image[0];
	}

	int GetIndex()
	{
		return index;
	}

private:
	int index = -1;
};
