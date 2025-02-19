#include "framework.h"
#include "ArkanoidPlayer.h"

#include "ArkanoidBall.h"
#include "ArkanoidItem.h"

ArkanoidPlayer::ArkanoidPlayer()
	:RectCollider(Vector(0, 0), Vector(100, 15))
{
	_brush = CreateSolidBrush(GREEN);

	for (int i = 0; i < 3;i++)
	{
		shared_ptr<CircleCollider> life = make_shared<CircleCollider>(Vector(50 + 50 * i, 650), 10.0f);
		_lifes.push_back(life);
	}



	_skills[0] = std::bind(&ArkanoidPlayer::TwoBall_Skill, this);
	_skills[1] = std::bind(&ArkanoidPlayer::More_Life, this);
	_skills[2] = std::bind(&ArkanoidPlayer::Game_Clear, this);


}


ArkanoidPlayer::~ArkanoidPlayer()
{
	DeleteObject(_brush);
}


void ArkanoidPlayer::Init()
{
	for (int i = 0; i < 4; i++)
	{
		auto ball = make_shared<ArkanoidBall>(dynamic_pointer_cast<ArkanoidPlayer>(shared_from_this()));

		_balls.push_back(ball);
	}

	_balls[0]->SetActive();
}

void ArkanoidPlayer::Update()
{
	if (_gameOver)
		return;

	RectCollider::Update();

	for (auto ball : _balls)
	{
		ball->Update();
	}
	IsDead();
}

void ArkanoidPlayer::Render(HDC hdc)
{
	if (_gameOver)
		return;

	SelectObject(hdc, _brush);
	RectCollider::Render(hdc);
	for (auto ball : _balls)
	{
		ball->Render(hdc);
	}
}



void ArkanoidPlayer::Move()
{
	if (_gameOver)
		return;

	if (GetKeyState('A') & 0x8000)
	{
		SetCenter(GetCenter() + Vector(-1, 0) * _speed);
	}

	if (GetKeyState('D') & 0x8000)
	{
		SetCenter(GetCenter() + Vector(1, 0) * _speed);
	}

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		//if (!_ball->IsFired())
		//{
		//	_ball->SetDir(Vector(0, -1));
		//	_ball->Fire();
		//}

		auto ballIter = std::find_if(_balls.begin(), _balls.end(), [](shared_ptr<ArkanoidBall> a)-> bool
			{
				if (a->IsFired())
					return false;
				return true;
			});

		if (ballIter != _balls.end())
		{
			(*ballIter)->SetDir(Vector(0, -1));
			(*ballIter)->Fire();

		}

	}
}

bool ArkanoidPlayer::IsDead()
{
	if (_balls[0]->GetCenter().y > WIN_HEIGHT)
	{
		if (_lifes.empty() == false)
		{
			_lifes.pop_back();
			for (auto ball : _balls)
			{
				ball->SetDir(Vector(0, -1));
				ball->ReadyFire();
			}
		}
		else
		{
			_gameOver = true;
			PlaySound(TEXT("Objects//Arkanoid//ArkanoidSound//Arkanoid SFX (11).wav"), NULL, SND_FILENAME | SND_ASYNC);
			return true;
		}

		PlaySound(TEXT("Objects//Arkanoid//ArkanoidSound//Arkanoid SFX (10).wav"), NULL, SND_FILENAME | SND_SYNC);
		return true;
	}
	return false;
}

void ArkanoidPlayer::EatItem(shared_ptr<ArkanoidItem> item)
{
	if (IsCollision(item->GetCollider()))
	{
		item->ActiveSkill();
	}
}

void ArkanoidPlayer::TwoBall_Skill()
{
	auto iter = std::find_if(_balls.begin(), _balls.end(), [](shared_ptr<ArkanoidBall> ball)->bool
		{
			if (ball->IsActive() == false)
				return true;
			return false;
		});

	if (iter != _balls.end())
	{
		(*iter)->ReadyFire();
		(*iter)->SetActive();
	}
}

void ArkanoidPlayer::More_Life()
{
	int a = 1;

}

void ArkanoidPlayer::Game_Clear()
{
	int a = 1;
}
