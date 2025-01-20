#include "GameLevel_ABC.h"

#include "Game/Game.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"

#include "Actorabc/Player_ABC.h"
#include "Actorabc/Shooter.h"
#include "Actorabc/Stepper.h"

GameLevel_ABC::GameLevel_ABC()
{
	Engine::Get().SetCursorType(CursorType::NoCursor);//커서 감추기

	// 맵 파일 불러와 레벨 로드.

	FILE* file = nullptr;
	fopen_s(&file,"../Assets/Maps/MapABC.txt","rb");		//원슬래시는 1개**

	if(file == nullptr)
	{
		std :: cout << "맵 파일 열기 실패. \n";

		__debugbreak();
		return;
	}

	fseek(file,0,SEEK_END);			//파일 읽기, 끝위치로 이동
	size_t readSize = ftell(file);	//이동한 위치의 FP 가져오기

	rewind(file);	//FP 원위치하는! 같은거// SET/ / fseek(file,0,SEEK_SET)//파일 읽기, 끝위치로 이동

	char* buffer = new char[readSize +1];	//파일 읽어서 버퍼에 담기
	size_t bytesRead =	fread(buffer,1,readSize,file);
	if(readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름 \n";
		__debugbreak();
		return ;
	}

	buffer[readSize] = '\0';
	//std::cout << buffer << "\n";	//테스트출력

	int index=0;//파일 읽을 때 사용할 인덱스
	int xPosition = 0;
	int yPosition = 0;

	while(index < (int)bytesRead)	//해석 파씽
	{
		char mapChar = buffer[index++];	//한 문자씩 읽기

		if(mapChar == '\n')
		{
			++yPosition;
			xPosition =0;
			continue;
		}

		if(mapChar == '1')
		{
			//	actors.PushBack(new Wall(Vector2(xPosition,yPosition)));
			Wall * wall = new Wall(Vector2(xPosition,yPosition));
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		else if(mapChar == '.')
		{
			Ground* ground =  new Ground(Vector2(xPosition,yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);
		}

		//else if(mapChar == 'b')	//움직이기에, Ground 먼저 그려줌
		//{
		//	Ground* ground =  new Ground(Vector2(xPosition,yPosition));
		//	actors.PushBack(ground);
		//	map.PushBack(ground);

		//	Box* box =  new Box(Vector2(xPosition,yPosition));
		//	actors.PushBack(box);
		//	boxes.PushBack(box);
		//}

		//else if(mapChar == 't')
		//{
		//	Target* target =  new Target(Vector2(xPosition,yPosition));
		//	actors.PushBack(target);
		//	map.PushBack(target);
		//	targets.PushBack(target);
		//}

		else if(mapChar == 'S')
		{
			Ground* ground =  new Ground(Vector2(xPosition,yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);	//랜더 제어 목적으로!

			Shooter* shooter =  new Shooter(Vector2(xPosition,yPosition));
			actors.PushBack(shooter);
			map.PushBack(shooter);	//랜더 제어 목적으로! //깜밖임 제어??
			shooters.PushBack(shooter);
		}

		else if(mapChar == 's')
		{
			Ground* ground =  new Ground(Vector2(xPosition,yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);	//랜더 제어 목적으로!

			Stepper* stepper =  new Stepper(Vector2(xPosition,yPosition));
			actors.PushBack(stepper);
			map.PushBack(stepper);	//랜더 제어 목적으로! //깜밖임 제어??
			steppers.PushBack(stepper);
		}

		else if(mapChar == 'P')	//움직이기에, Ground 먼저 그려줌
		{
			Ground* ground =  new Ground(Vector2(xPosition,yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);	//랜더 제어 목적으로!

			player_ABC =  new Player_ABC(Vector2(xPosition,yPosition),this);
			actors.PushBack(player_ABC);
		}

		++xPosition;
		//	std::cout << mapChar;
	}

	delete[] buffer;	//버퍼 삭제

	fclose(file);		//파일 닫기

	//슈터
	int inta = 'A';
	for(DrawableActor* shooter:shooters)
	{
		char* shooterText = new char[2]; // 동적 메모리 할당
		shooterText[0] = (char)inta; // 첫 번째 문자
		shooterText[1] = '\0';       // null 문자 추가

		dynamic_cast<Shooter*>(shooter)->SetReImage(shooterText);

		delete[] shooterText; // 메모리 해제

		inta++;
	}

	int start_A = 'a';
	for(DrawableActor* stepper:steppers)
	{
		char* shooterText = new char[2]; // 동적 메모리 할당
		shooterText[0] = (char)start_A; // 첫 번째 문자
		shooterText[1] = '\0';       // null 문자 추가

		dynamic_cast<Stepper*>(stepper)->SetReImage(shooterText);

		delete[] shooterText; // 메모리 해제

		start_A++;
	}

	SetMaxXY();
}

void GameLevel_ABC::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void GameLevel_ABC::Draw()
{
	//std::cout << name << comment <<"\n";

	for(auto* actor:map)		//맵 그리기
	{
		if(actor-> Position() == player_ABC->Position())	//플레이어 위치 확인
		{
			continue;
		}

		bool shouldDraw = true;
		/*	for(auto* box : boxes)
			{
				if(actor->Position() == box->Position())
				{
					shouldDraw = false;
					break;
				}
			}*/

		if(shouldDraw)
		{
			actor -> Draw();	//맵 액터 그리기
		}
	}

	//슈터그리기
	for(auto* shooter:shooters)
	{
		if(shooter-> Position() == player_ABC->Position())	//플레이어 위치 확인
		{
			continue;
		}

		bool shouldDraw = true;
		/*	for(auto* box : boxes)
			{
				if(shooter->Position() == box->Position())
				{
					shouldDraw = false;
					break;
				}
			}*/

		if(shouldDraw)
		{
			shooter -> Draw();
		}
	}

	//푸터그리기
	for(auto* stepper:steppers)
	{
		if(stepper-> Position() == player_ABC->Position())	//플레이어 위치 확인
		{
			continue;
		}

		bool shouldDraw = true;
		/*	for(auto* box : boxes)
			{
				if(stepper->Position() == box->Position())
				{
					shouldDraw = false;
					break;
				}
			}*/

		if(shouldDraw)
		{
			stepper -> Draw();
		}
	}

	//총알 그리기
	for(auto* bullet:bullets)
	{
		if(bullet-> Position() == player_ABC->Position())	//플레이어 위치 확인
		{
			continue;
		}

		bool shouldDraw = true;
		/*	for(auto* box : boxes)
			{
				if(bullet->Position() == box->Position())
				{
					shouldDraw = false;
					break;
				}
			}*/

		if(shouldDraw)
		{
			if(bullet->IsActive())
			{
				bullet -> Draw();
			}
		}
	}

	player_ABC->Draw();			//플레이어 그리기
}

void GameLevel_ABC::SetPlayer(const char* name,const char* comment)
{
	if(this->name != nullptr)
	{
		delete[] this->name;
	}
	if(this->comment != nullptr)
	{
		delete[] this->comment;
	}

	if(name != nullptr)
	{
		size_t length = strlen(name) + 1;
		this->name = new char[length];
		strcpy_s(this->name,length,name);
	}
	if(comment != nullptr)
	{
		size_t length = strlen(comment) + 1;
		this->comment = new char[length];
		strcpy_s(this->comment,length,comment);
	}

	std::cout<<"SetPlayer" << name << comment <<"\n";
}

bool GameLevel_ABC::CanPlayerMove(const Vector2& position)
{
	if(isGameClear)
	{
		return false;
	}

	DrawableActor* searchedActor = nullptr;	// 이동하려는 위치에 벽 있는지 확인

	for(auto* actor : map)
	{
		if(actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	//이동불가 -> 벽
	if(searchedActor->As<Wall>())
	{
		return false;
	}

	// 이동가능 -> 땅, 타겟
	if(searchedActor->As<Ground>())
		//if(searchedActor->As<Ground>()   || searchedActor->As<Target>())
	{
		return true;
	}

	return false;
}

void GameLevel_ABC::SetActors_Bullets(Actor *&& actor)
{
	actors.PushBack(actor);
	bullets.PushBack((DrawableActor*)actor);
}

Vector2 GameLevel_ABC::GetMaxXY()
{
	return maxXY;
}

Vector2 GameLevel_ABC::SetMaxXY()
{
	float maxX = 0.f;
	float maxY = 0.f;
	for(auto* actor:map)		//맵 그리기
	{
		if(maxX < actor->Position().x){
			maxX = actor->Position().x;
		}

		if(maxY < actor->Position().y){
			maxY = actor->Position().y;
		}
	}

	return  maxXY= Vector2(maxX,maxY);
}

Actor* GameLevel_ABC::CanPlayerShoot(const Vector2 & position)
{
	if(isGameClear)
	{
		return nullptr;
	}

	DrawableActor* searchedActor = nullptr;	// 현위치에 기믹이 있는지
	for(auto* actor : steppers)
	{
		if(actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}
	if(searchedActor == nullptr)
	{
		return nullptr;
	}

	if(searchedActor->As<Stepper>())
	{
		return dynamic_cast<Actor*> (searchedActor); //@세윤쌤 : 이렇게 막 형변환 해도 됨?
	}

	return nullptr;
}