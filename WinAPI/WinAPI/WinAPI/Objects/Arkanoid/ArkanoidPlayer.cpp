#include "framework.h"
#include "ArkanoidPlayer.h"

ArkanoidPlayer::ArkanoidPlayer()
	:RectCollider(Vector(0, 0), Vector(100, 15))
{
	_brush = CreateSolidBrush(GREEN);
}

ArkanoidPlayer::~ArkanoidPlayer()
{
	DeleteObject(_brush);
}

void ArkanoidPlayer::Update()
{
	RectCollider::Update();

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
