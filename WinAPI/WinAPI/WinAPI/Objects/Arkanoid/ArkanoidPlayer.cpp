#include "framework.h"
#include "ArkanoidPlayer.h"

#include "Objects/Arkanoid/ArkanoidBall.h"

ArkanoidPlayer::ArkanoidPlayer()
	:RectCollider(Vector(0, 0), Vector(100, 15))
{
	_brush = CreateSolidBrush(GREEN);

	for (int i = 0; i < 1;i++)
	{
		shared_ptr<CircleCollider> life = make_shared<CircleCollider>(Vector(50 + 50 * i, 650), 10.0f);
		_lifes.push_back(life);
	}

}

ArkanoidPlayer::~ArkanoidPlayer()
{
	DeleteObject(_brush);
}


void ArkanoidPlayer::Init()
{
	_ball = make_shared<ArkanoidBall>(dynamic_pointer_cast<ArkanoidPlayer>(shared_from_this()));
	_ball->SetActive();
}

void ArkanoidPlayer::Update()
{
	if (_gameOver)
		return;

	RectCollider::Update();

	_ball->Update();
	IsDead();
}

void ArkanoidPlayer::Render(HDC hdc)
{
	SelectObject(hdc, _brush);
	RectCollider::Render(hdc);
	_ball->Render(hdc);
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
		if (!_ball->IsFired())
		{
			_ball->SetDir(Vector(0, -1));
			_ball->Fire();
		}
	}
}

bool ArkanoidPlayer::IsDead()
{
	if (_ball->GetCenter().y > WIN_HEIGHT)
	{
		if (_lifes.empty() == false)
		{
			_lifes.pop_back();
			_ball->SetDir(Vector(0, -1));
		}
		else
		{
			PlaySound(TEXT("Objects//Arkanoid//ArkanoidSound//Arkanoid SFX (11).wav"), NULL, SND_FILENAME | SND_SYNC);
			_gameOver = true;
			return true;
		}

		PlaySound(TEXT("Objects//Arkanoid//ArkanoidSound//Arkanoid SFX (10).wav"), NULL, SND_FILENAME | SND_SYNC);
		_ball->ReadyFire();
		return true;
	}
	return false;
}
