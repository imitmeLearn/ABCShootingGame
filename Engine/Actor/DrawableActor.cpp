#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include <Engine\Engine.h>

//전달받은 문자열 복사
DrawableActor::DrawableActor(const char* image)
	:Actor()
	//해도 안해도 되지만, 명시적 생성을 위해 호촐
	//,image(image)
{
	auto length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image,length,image);

	//너비 설정
	width = (int)strlen(image);
}

DrawableActor::~DrawableActor()
{
	delete[] image;
}

void DrawableActor::Draw()
{
	Super::Draw();
	SetColor(color); //색상설정

	//todo 그리기 : 단계2단계 있음.
	Engine::Get().SetCursorPosition(position);			//1단계 : 콘솔 좌표 옮기기'
	Log(image);									//2단계 : 그리기(콘솔 출력)

	SetColor(Color::White); 	//색상복구
}

void DrawableActor::SetPosition(const Vector2 & newPosition)
{
	Super::SetPosition(newPosition);			//위치 새로 옮기기
}

bool DrawableActor::Intersect(const DrawableActor & other)
{
	//AABB

	int min = position.x;				//내 액터 x좌표 최소
	int max = position.x + width;		//내 액터 x좌표 최대

	//다른 액터 x좌표 최소/최대
	int otherMin = other.position.x;					//다른 액터 x좌표 최소
	int otherMax = other.position.x + other.width;		//다른 액터 x좌표 최대

	if(otherMin > max)	//다른 액터의 왼쪽 끝 위치가 내 오른쪽 끝 위치를 벗어나면 출동 안함.
	{
		return false;
	}
	if(otherMax < min)	//다른 액터의 오른쪽 끝 위치가 내 왼쪽 끝 위치보다 작으면 충돌 안함.
	{
		return false;
	}

	return position.y == other.position.y;  //위의 두 경우 아니라면, X 좌표 서로 겹침,  y 위치 비교
}