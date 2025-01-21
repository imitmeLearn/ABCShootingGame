#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Actor/Player.h"

#include "Engine/Timer.h"

GameLevel::GameLevel()
{
	Engine::Get().SetCursorType(CursorType::NoCursor);//커서 감추기

	// 맵 파일 불러와 레벨 로드.
		//파일읽기
	FILE* file = nullptr;
	fopen_s(&file,"..\\Assets\\Maps\\Map.txt","rb");	//백슬래시는 2개**
	fopen_s(&file,"../Assets/Maps/Stage1.txt","rb");		//원슬래시는 1개**
	fopen_s(&file,"../Assets/Maps/Stage2.txt","rb");		//원슬래시는 1개**
	fopen_s(&file,"../Assets/Maps/Stage3.txt","rb");		//원슬래시는 1개**
	fopen_s(&file,"../Assets/Maps/Map.txt","rb");		//원슬래시는 1개**

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
			Wall* wall = new Wall(Vector2(xPosition,yPosition));
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		else if(mapChar == '.')
		{
			Ground* ground =  new Ground(Vector2(xPosition,yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);
		}

		else if(mapChar == 'b')	//움직이기에, Ground 먼저 그려줌
		{
			Ground* ground =  new Ground(Vector2(xPosition,yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Box* box =  new Box(Vector2(xPosition,yPosition));
			actors.PushBack(box);
			boxes.PushBack(box);
		}

		else if(mapChar == 't')
		{
			Target* target =  new Target(Vector2(xPosition,yPosition));
			actors.PushBack(target);
			map.PushBack(target);
			targets.PushBack(target);
		}

		else if(mapChar == 'p')	//움직이기에, Ground 먼저 그려줌
		{
			Ground* ground =  new Ground(Vector2(xPosition,yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);	//랜더 제어 목적으로!

			player =  new Player(Vector2(xPosition,yPosition),this);
			actors.PushBack(player);
		}

		++xPosition;
		//	std::cout << mapChar;
	}

	delete[] buffer;	//버퍼 삭제

	fclose(file);		//파일 닫기
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
	if(isGameClear)
	{
		static Timer timer(0.1f);	//타이머
		timer.Update(deltaTime);
		if(!timer.IsTimeOut())
		{
			return;
		}

		Engine::Get().SetCursorPosition(0,Engine::Get().ScreenSize().y);	//커서이동
		Log("GameClear");
		Sleep(1000);				//쓰레드 정지
		Engine::Get().QuitGame();	//게임 종료 처리
	}
}

void GameLevel::Draw()
{
	for(auto* actor:map)		//맵 그리기
	{
		if(actor-> Position() == player->Position())	//플레이어 위치 확인
		{
			continue;
		}

		bool shouldDraw = true;
		for(auto* box : boxes)
		{
			if(actor->Position() == box->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		if(shouldDraw)
		{
			actor -> Draw();	//맵 액터 그리기
		}
	}

	for(auto* target:targets)	//타겟그리기
	{
		if(target-> Position() == player->Position())	//플레이어 위치 확인
		{
			continue;
		}

		bool shouldDraw = true;
		for(auto* box : boxes)
		{
			if(target->Position() == box->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		if(shouldDraw)
		{
			target -> Draw();
		}
	}

	for(auto* box:boxes)			//박스그리기
	{
		box -> Draw();
	}

	player->Draw();			//플레이어 그리기
}

bool GameLevel::CanPlayerMove(const Vector2& position)
{
	if(isGameClear)
	{
		return false;
	}

	Box* searchedBox = nullptr;			//박스검색
	for(auto* box : boxes)
	{
		if(box->Position() == position)
		{
			searchedBox =box;
			break;
		}
	}

	if(searchedBox)		//박스가 있을 때 처리
	{
		//Vector2 direction =	position - player->Position();		//이동 방향.
		int directionX =	position.x - player->Position().x;		//이동 방향. x
		int directionY =	position.y - player->Position().y;		//이동 방향. y

		Vector2 newPosition = searchedBox->Position()+Vector2(directionX,directionY);	//박스가 이동할 새 위치 :박스위치+이동방향

		for(auto* box:boxes)							//박스 검색(박스)
		{
			if(box==searchedBox)
			{
				continue;
			}

			if(box->Position() == newPosition)			//이동할 위치에 다른 박스가 있다면, 이동불가
			{
				return false;
			}
		}

		for(auto* actor:map)
		{
			if(actor->Position() == newPosition)	//이동하려는 위치에 있는 액터 검색
			{
				if(actor -> As<Wall>())		//이동하려는 위치에 벽이 있으면, 이동 불가
				{
					return false;
				}

				if(actor -> As<Ground>() || actor->As<Target>())		//이동 가능 ㅣ 땅 , 타켓
				{
					searchedBox->SetPosition(newPosition);				// 박스 이동 처리.
					isGameClear = CheckGameClear();			//게임 클리어 여부 확인
					return true;
				}
			}
		}
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

	//벽  -> 이동불가
	if(searchedActor->As<Wall>())
	{
		return false;
	}

	//땅, 타겟  -> 이동가능
	if(searchedActor->As<Ground>()   || searchedActor->As<Target>())
	{
		return true;
	}

	return false;
}

bool GameLevel::CheckGameClear()
{
	int currentScore = 0;								//점수 확인을 위한 변수 : 박스 타겟 같은 위치 있는 거 찾을 거야.
	int targetScore = targets.Size();

	for(auto* box:boxes)								//박스 위치에 배치된 박스 개수 세기
	{
		for(auto* target : targets)
		{
			if(box ->Position() == target->Position())	//점수확인
			{
				++currentScore;
				continue;
			}
		}
	}

	return currentScore == targetScore;					//획득한 점수가 목표 점수와 같은지 비교
}