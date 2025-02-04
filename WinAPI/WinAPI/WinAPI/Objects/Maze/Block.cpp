#include "framework.h"
#include "Block.h"

Block::Block()
	:RectCollider(Vector(0,0), Vector(15,15))
{
	_brushes.push_back(CreateSolidBrush(BLACK));
	_brushes.push_back(CreateSolidBrush(GREEN));
	_brushes.push_back(CreateSolidBrush(RED));
	_brushes.push_back(CreateSolidBrush(BLACK));
	_brushes.push_back(CreateSolidBrush(RGB(101, 3, 62)));
	_brushes.push_back(CreateSolidBrush(RGB(53, 13, 162)));

}

Block::~Block()
{
	for (auto brush : _brushes)
		DeleteObject(brush);

}

void Block::Update()
{
	RectCollider::Update();

}

void Block::Render(HDC hdc)
{
	SelectObject(hdc,_brushes[static_cast<int>(_curType)]);
	RectCollider::Render(hdc);

}
