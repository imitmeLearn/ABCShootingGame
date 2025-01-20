#pragma once

#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"

//레벨의 기본 물체
class ENGINE_API Actor: public RTTI
{
	RTTI_DECLARATIONS(Actor,RTTI)

		friend class Level;						//private 접근이 가능하도록,  //레벨 클래스를 friend 로 선언.

public:
	Actor();
	virtual ~Actor();

	virtual void Update(float deltaTime);		//루프
	virtual void Draw();						//루프

	virtual void SetPosition(const Vector2& newPosition);
	Vector2 Position() const;

	inline bool IsActive() const {
		return isActive&& !isExpired;
	}
	inline void SetActive(bool active){
		isActive = active;
	}
	inline void Destroy() {
		isExpired = true;
	}

protected:
	Vector2 position;	//엑터 위치

	//ID 엑터검색용 숫자기반 ID : 유일값 해시값
	bool isActive;	//활성화 상태인지를 나타내는 변수
	bool isExpired;	//엑터의 제거 요청이 됐는지 여부를 나타내는 변수
};