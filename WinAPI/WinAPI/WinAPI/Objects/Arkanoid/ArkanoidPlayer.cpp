#include "framework.h"
#include "ArkanoidPlayer.h"

#include "Objects/Arkanoid/ArkanoidBall.h"

ArkanoidPlayer::ArkanoidPlayer()
	:RectCollider(Vector(0, 0), Vector(100, 15))
{
	_brush = CreateSolidBrush(GREEN);

	for (int i = 0; i < 3;i++)
	{
		shared_ptr<ArkanoidBall> life = make_shared<ArkanoidBall>(Vector(50 + 50 * i, 650));
		_lifes.push_back(life);
	}

}

ArkanoidPlayer::~ArkanoidPlayer()
{
	DeleteObject(_brush);
}

void ArkanoidPlayer::Update()
{
	RectCollider::Update();

	for (int i = 0; i < _lifes.size();i++)
	{
		_lifes[i]->Update();
	}

	Move();
}

void ArkanoidPlayer::Render(HDC hdc)
{
	SelectObject(hdc, _brush);
	RectCollider::Render(hdc);
}

void ArkanoidPlayer::Move()
{
	if (GetKeyState('A') & 0x8000)
	{
		SetCenter(GetCenter() + Vector(-1, 0) * _speed);
	}

	if (GetKeyState('D') & 0x8000)
	{
		SetCenter(GetCenter() + Vector(1, 0) * _speed);
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
			isFired = false;
		}
		else
		{
			_gameOver = true;

		}
		PlaySound(TEXT("Objects//Arkanoid//ArkanoidSound//Arkanoid SFX (10).wav"), NULL, SND_FILENAME | SND_SYNC);

		return true;
	}
	return false;
}
