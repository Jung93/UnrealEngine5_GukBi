#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector center, Vector size)
	: Collider(center), _halfSize(size * 0.5f)
{
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
}

void RectCollider::Render(HDC hdc)
{
	vector<HPEN> pens = GetPens();
	UINT curPen = GetCurPen();
	SelectObject(hdc, pens[curPen]);

	Vector center = GetCenter();

	float left = center.x - _halfSize.x;
	float right = center.x + _halfSize.x;
	float top = center.y - _halfSize.y;
	float bottom = center.y + _halfSize.y;

	Rectangle(hdc, left, top, right, bottom);
}

bool RectCollider::IsCollision(const Vector& pos)
{
	Vector center = GetCenter();

	float left = center.x - _halfSize.x;
	float right = center.x + _halfSize.x;
	float top = center.y - _halfSize.y;
	float bottom = center.y + _halfSize.y;

	if (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom)
		return true;
	return false;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
	Vector center = GetCenter();

	float left = center.x - _halfSize.x;
	float right = center.x + _halfSize.x;
	float top = center.y - _halfSize.y;
	float bottom = center.y + _halfSize.y;

	float otherLeft = other->GetCenter().x - other->_halfSize.x;
	float otherRight = other->GetCenter().x + other->_halfSize.x;
	float otherTop = other->GetCenter().y - other->_halfSize.y;
	float otherBottom = other->GetCenter().y + other->_halfSize.y;

	if (otherLeft >= left && otherLeft <= right || otherRight >= left && otherRight <= right)
	{
		if(otherTop >= top && otherTop <= bottom || otherBottom >= top && otherBottom <= bottom)
			return true;
	}

	return false;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	Vector dir = other->GetCenter() - GetCenter();
	Vector rightV = Vector(1, 0);
	Vector upV = Vector(0, -1);

	//예외처리
	if (dir.Length() > _halfSize.Length() + other->GetRadius())
		return false;


	//x축 내적
	float lengthX = abs(rightV.Dot(dir));
	if (lengthX > _halfSize.x + other->GetRadius())
		return false;

	//y축 내적
	float lengthY = abs(upV.Dot(dir));
	if (lengthY > _halfSize.y + other->GetRadius())
		return false;

	return true;


	//Vector newHalfSize(_halfSize.x + other->GetRadius(), _halfSize.y + other->GetRadius());
	//
	//float newLeft = _center.x - newHalfSize.x;
	//float newRight = _center.x + newHalfSize.x;
	//float newTop = _center.y - newHalfSize.y;
	//float newBottom = _center.y + newHalfSize.y;

	//Vector circleCenter = other->GetCenter();
	//Vector dir = circleCenter - _center;

	//if (circleCenter.x >= newLeft && circleCenter.x <= newRight && circleCenter.y >= newTop && circleCenter.y <= newBottom)
	//{
	//	if (dir.Length() <= _halfSize.Length() + other->GetRadius())
	//	{
	//		return true;
	//	}
	//}

	//return false;
}