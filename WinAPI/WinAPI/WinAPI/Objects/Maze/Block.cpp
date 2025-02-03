#include "framework.h"
#include "Block.h"

Block::Block()
	:RectCollider(Vector(0,0), Vector(15,15))
{
	_brushes.push_back(CreateSolidBrush(BLACK));
	_brushes.push_back(CreateSolidBrush(GREEN));
	_brushes.push_back(CreateSolidBrush(RED));
}

Block::~Block()
{
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
