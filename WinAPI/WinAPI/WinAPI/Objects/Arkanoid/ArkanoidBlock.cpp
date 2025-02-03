#include "framework.h"
#include "ArkanoidBlock.h"

ArkanoidBlock::ArkanoidBlock()
	:RectCollider(Vector(0, 0), Vector(100, 15))
{
	_brushes.push_back(CreateSolidBrush(BLACK));
	_brushes.push_back(CreateSolidBrush(GREEN));
	_brushes.push_back(CreateSolidBrush(RED));
}

ArkanoidBlock::~ArkanoidBlock()
{
}

void ArkanoidBlock::Update()
{
	RectCollider::Update();

	if(_curType == Type::BAR)
		Move();
}

void ArkanoidBlock::Render(HDC hdc)
{
	SelectObject(hdc, _brushes[static_cast<int>(_curType)]);
	RectCollider::Render(hdc);



}

void ArkanoidBlock::Move()
{
	if (GetKeyState('A') & 0x8000)
	{
		SetCenter(GetCenter() + Vector(-1, 0) * _speed );
	}

	if (GetKeyState('D') & 0x8000)
	{
		SetCenter(GetCenter() + Vector(1, 0) * _speed);
	}
}
