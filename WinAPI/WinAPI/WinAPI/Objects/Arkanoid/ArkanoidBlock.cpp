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

}

void ArkanoidBlock::Render(HDC hdc)
{
	SelectObject(hdc, _brushes[static_cast<int>(_curType)]);
	RectCollider::Render(hdc);
}

bool ArkanoidBlock::IsCollision(shared_ptr<CircleCollider> other)
{
	Vector dir = other->GetCenter() - GetCenter();
	Vector rightV = Vector(1, 0);
	Vector upV = Vector(0, -1);

	Vector halfSize = GetHalfSize();

	//����ó��
	if (dir.Length() > halfSize.Length() + other->GetRadius())
		return false;


	//x�� ����
	float lengthX = abs(rightV.Dot(dir));
	if (lengthX > halfSize.x + other->GetRadius())
		return false;

	//y�� ����
	float lengthY = abs(upV.Dot(dir));
	if (lengthY > halfSize.y + other->GetRadius())
		return false;

	return true;
}


