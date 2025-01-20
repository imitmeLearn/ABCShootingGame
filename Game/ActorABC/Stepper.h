#pragma once

#include <Actor/DrawableActor.h>
class Stepper: public DrawableActor
{
	RTTI_DECLARATIONS(Stepper,DrawableActor)
public:
	Stepper(const Vector2& position);

	void SetReImage(const char* image)
	{
		//std::cout<<" 그리기 확인 : "<<&image;

		auto length = strlen(image) + 1;
		this->image = new char[length];
		strcpy_s(this->image,length,image);

		//너비 설정
		width = (int)strlen(image);

		index= (int)image;
	}

private:
	int index = -1;
};
