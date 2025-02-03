#include "framework.h"
#include "ArkanoidBall.h"

ArkanoidBall::ArkanoidBall(Vector pos)
	:CircleCollider(pos, 10)
{
	_brush = CreateSolidBrush(BLACK);
}

ArkanoidBall::~ArkanoidBall()
{
}

void ArkanoidBall::Update()
{
	CircleCollider::Update();

}

void ArkanoidBall::Render(HDC hdc)
{
	SelectObject(hdc, _brush);
	CircleCollider::Render(hdc);

}
