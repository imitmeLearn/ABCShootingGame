#include "GameLevel_ABC.h"

#include "Game/Game.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"

#include "Actorabc/Player_ABC.h"
#include "Actorabc/Shooter.h"
#include "Actorabc/Stepper.h"
#include "ActorABC/Enemy.h"
#include "ActorABC/ABCBullet.h"

#ifdef UNICODE
#define OutputDebugString  OutputDebugStringW
#else
#define OutputDebugString  OutputDebugStringA
#endif // !UNICODE

static const char* enemyType[]
{
	";(^);",
	"zZTZz",
	"oO&Oo",
	"<=-=>",
	")~O~(",
	"[[0]]"
};

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
			//Ground* ground =  new Ground(Vector2(xPosition,yPosition));
			//actors.PushBack(ground);
			//map.PushBack(ground);	//랜더 제어 목적으로!

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
		if(start_A == 'a')
		{
			dynamic_cast<Stepper*>(stepper)->SetReImage(shooterText,StepperType::CurrPos);
		}

		else{
			dynamic_cast<Stepper*>(stepper)->SetReImage(shooterText,StepperType::OtherPos);
		}

		delete[] shooterText; // 메모리 해제

		start_A++;
	}

	SetMaxXY();
}

GameLevel_ABC::~GameLevel_ABC()
{
	if(this->name != nullptr)
	{
		delete[] this->name;
		this->name = nullptr;
	}

	if(this->comment != nullptr)
	{
		delete[] this->comment;
		this->comment = nullptr;
	}

	//enemy
}

void GameLevel_ABC::myDebugMsg(const char * format,...)
{
	#ifdef _DEBUG
	char str[128];
	va_list args;
	va_start(args,format);
	vsnprintf(str,sizeof(str),format,args);
	//OutputDebugString(str);
	OutputDebugStringA(str);
	//OutputDebugStringW(str);
	va_end(args);
	#endif
}

void GameLevel_ABC::Update(float deltaTime)
{
	Super::Update(deltaTime);

	SpawnEnemy(deltaTime);

	ProcessCollisionPlayerBulletandEnemy();
	//ProcessCollisionPlayerAndEnemyBullet();
}

void GameLevel_ABC::Draw()
{
	//std::cout << name << comment <<"\n";

	// 적 리스트 초기화.
	List<Enemy*> enemies;
	List<ABCBullet*> bullets;
	for(auto* actor : actors)
	{
		Enemy* enemy = actor->As<Enemy>();
		if(enemy)
		{
			enemies.PushBack(enemy);
			//continue;
		}

		ABCBullet* bullet = actor->As<ABCBullet>();
		if(bullet)
		{
			bullets.PushBack(bullet);
		}
	}

	for(auto* actor : map)		//맵 그리기
	{
		if(actor-> Position() == player_ABC->Position())	//플레이어 위치 확인
		{
			continue;
		}

		bool shouldDraw = true;
		if(enemies.Size() > 0)
		{
			for(auto* enemy : enemies)
			{
				if((actor->Position().x -  enemy->Position().x) < enemy->Width()
					&& (actor->Position().x -  enemy->Position().x) >= 0
					&& actor->Position().y ==  enemy->Position().y
					)
				{
					shouldDraw = false;
					break; //continue;  //break; ?? continue적이 또 있을 수 있나?
				}

				/*if(actor->Position() == enemy->Position())
				{
					shouldDraw = false;
					break;
				}*/
			}
		}

		if(shouldDraw)
		{
			actor -> Draw();	//맵 액터 그리기
		}
	}

	//푸터그리기
	for(auto* stepper : steppers)
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
	if(bullets.Size() > 0)
	{
		for(auto* bullet : bullets)
		{
			if(bullet-> Position() == player_ABC->Position())	//플레이어 위치 확인
			{
				continue;
			}

			bool shouldDraw = true;
			/*for(auto* shooter : shooters)
			{
				if(bullet->Position() == shooter->Position())
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
	}

	//슈터그리기
	for(auto* shooter : shooters)
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
	//적 그리기
	for(auto* enemy:enemies)
	{
		//if(bullet-> Position() == player_ABC->Position())	//플레이어 위치 확인
		//{
		//	continue;
		//}

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
			if(enemy->IsActive())
			{
				enemy -> Draw();
			}
		}
	}

	player_ABC->Draw();			//플레이어 그리기
}

void GameLevel_ABC::SetPlayer(const char* name,const char* comment)
{
	size_t length = strlen(name) + 1;
	this->name = new char[length];
	strcpy_s(this->name,length,name);

	length = strlen(comment) + 1;
	this->comment = new char[length];
	strcpy_s(this->comment,length,comment);

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

void GameLevel_ABC::SetActors_Bullets(DrawableActor* actor)
{
	actors.PushBack(actor);
	//bullets.PushBack(actor);
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
		if(maxX < (float)actor->Position().x)
		{
			maxX = (float)actor->Position().x;
		}

		if(maxY < (float)actor->Position().y)
		{
			maxY = (float)actor->Position().y;
		}
	}

	return  maxXY= Vector2((int)maxX,(int)maxY);
}

Actor* GameLevel_ABC::SteponActor(const Vector2 & position)
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
		return searchedActor; //@세윤쌤 : 이렇게 막 형변환 해도 됨? ->OK. 업캐스팅이라서 문제 없습니다.
	}

	return nullptr;
}

void GameLevel_ABC::SpawnEnemy(float deltaTime)
{
	static float	elapsedTime = 0.f;
	static float	spawnTime = RandomPercent(1.f,3.f);

	elapsedTime += deltaTime;
	if(elapsedTime < spawnTime)
	{
		return;
	}

	elapsedTime = 0.0f;
	spawnTime = RandomPercent(1.f,3.f);

	static int length = sizeof(enemyType)/sizeof(enemyType[0]);
	int index = Random(0,length -1);
	Enemy* enemy = new Enemy(enemyType[index],Random(5,15),this); //@세윤썜 : 여기도 new 했는데, 해제하나요? 블록안에서 만든것들은 언제 해제 하나요?? 여기서 메모리 누수 오류!
	AddActor(enemy);
	//actors.PushBack(emeny);
	//enemies.PushBack(emeny);
}

Actor* GameLevel_ABC::GetShooterActor(int index)
{
	for(auto* shooter:shooters)
	{
		Shooter* curr =	dynamic_cast<Shooter*> (shooter);

		if(curr->GetIndex() == index-32)
		{
			//myDebugMsg("Index value: %d\n",index); //@지우기 - 확인후

			return shooter;
		}
	}

	return nullptr;
}

void GameLevel_ABC::ProcessCollisionPlayerBulletandEnemy()
{
	List<ABCBullet*> bullets;	//탄약 및 적 캐릭터 배열 선언.
	List<Enemy*> enemies;		//탄약 및 적 캐릭터 배열 선언.

	for(Actor* actor:actors)	//레벨에 배치된 액터를 순회하면서, 리스트 채우기.
	{
		ABCBullet* bullet = actor -> As<ABCBullet>();		//탄약 으로 형변환 후 확인해서, 리스트 채우기
		if(bullet)
		{
			bullets.PushBack(bullet);
			continue;
		}

		Enemy* enemy = actor->As<Enemy>();		//적 으로 형변환 후 확인해서, 리스트 채우기
		if(enemy)
		{
			enemies.PushBack(enemy);
		}
	}

	if(bullets.Size()==0 || enemies.Size() == 0) //예외처리 : 비교대상 없으면, 충돌 연산 할 필요 없어.
	{
		return;
	}

	for(ABCBullet* bullet:bullets)		//두 배열을 순회하면서, 충돌처리
	{
		for(Enemy* enemy : enemies)
		{
			if(!enemy ->IsActive())					// 적이 비활성화 상태라면 건너뛰기.
			{
				continue;
			}

			if(enemy -> Intersect (*bullet))	  // 충돌 처리.
			{
				enemy -> Destroy();			// 충돌했으면 적 제거.
				bullet->Destroy();			// 탄약도 제거.
				totalScore += hitScore;		//점수 추가
				hitCount++;					//hit 수 증가

				myDebugMsg("totalScore  %d, hitCount %d",totalScore,hitCount);
			}
		}
	}
}