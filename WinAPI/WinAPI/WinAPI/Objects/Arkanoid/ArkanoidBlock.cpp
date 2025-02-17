#include "framework.h"
#include "ArkanoidBlock.h"
#include "ArkanoidItem.h"

ArkanoidBlock::ArkanoidBlock()
	:RectCollider(Vector(0, 0), Vector(100, 15))
{
	_brushes.push_back(CreateSolidBrush(BLACK));
	_brushes.push_back(CreateSolidBrush(GREEN));
	_brushes.push_back(CreateSolidBrush(RED));
	_brushes.push_back(CreateSolidBrush(BLUE));
}

ArkanoidBlock::~ArkanoidBlock()
{
}

void ArkanoidBlock::Update()
{
	RectCollider::Update();

}

void ArkanoidBlock::Render(HDC hdc)
{
	SelectObject(hdc, _brushes[static_cast<int>(_curType)]);
	RectCollider::Render(hdc);
}

void ArkanoidBlock::SetItem(shared_ptr<ArkanoidItem> item)
{
	_item = item;
	if (_item.expired())
		return;

	_item.lock()->Pos() = GetCenter();

}

bool ArkanoidBlock::IsCollision(shared_ptr<CircleCollider> other)
{
	Vector dir = other->GetCenter() - GetCenter();
	Vector rightV = Vector(1, 0);
	Vector upV = Vector(0, -1);

	Vector halfSize = GetHalfSize();

	//예외처리
	if (dir.Length() > halfSize.Length() + other->GetRadius())
		return false;


	//x축 내적
	float lengthX = abs(rightV.Dot(dir));
	if (lengthX > halfSize.x + other->GetRadius())
		return false;

	//y축 내적
	float lengthY = abs(upV.Dot(dir));
	if (lengthY > halfSize.y + other->GetRadius())
		return false;




	return true;
}





