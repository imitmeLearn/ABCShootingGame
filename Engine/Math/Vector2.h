#pragma once
#include "Core.h"

class ENGINE_API Vector2
{
public:

	Vector2(int x=0,int y=0);
	~Vector2() = default;

	// 연산자 오버로딩
	bool operator ==(const Vector2& other);
	bool operator !=(const Vector2& other);
	Vector2 operator +(const Vector2& other);
	Vector2 operator -(const Vector2& other);

	//좌표관리 정수로!
	int x =0;
	int y =0;
private:
};
