#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector center, Vector size)
	:_center(center), _halfSize(size * 0.5f)
{
	_pens.push_back(CreatePen(1, 3, GREEN));
	_pens.push_back(CreatePen(1, 3, RED));
}

RectCollider::~RectCollider()
{
	for (auto& pen : _pens)
		DeleteObject(pen);
}

void RectCollider::Update()
{
	//_center = LERP(_center, mousePos, 0.03f);
}

void RectCollider::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curPen]);



	float left = _center.x - _halfSize.x;
	float right = _center.x + _halfSize.x;
	float top = _center.y - _halfSize.y;
	float bottom = _center.y + _halfSize.y;


	Rectangle(hdc, left, top, right, bottom);
}

bool RectCollider::IsCollision(const Vector& pos)
{
	float left = _center.x - _halfSize.x;
	float right = _center.x + _halfSize.x;
	float top = _center.y - _halfSize.y;
	float bottom = _center.y + _halfSize.y;

	if (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom)
		return true;
	return false;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
	float left = _center.x - _halfSize.x;
	float right = _center.x + _halfSize.x;
	float top = _center.y - _halfSize.y;
	float bottom = _center.y + _halfSize.y;

	float otherLeft = other->_center.x - other->_halfSize.x;
	float otherRight = other->_center.x + other->_halfSize.x;
	float otherTop = other->_center.y - other->_halfSize.y;
	float otherBottom = other->_center.y + other->_halfSize.y;

	if (otherLeft >= left && otherLeft <= right || otherRight >= left && otherRight <= right)
	{
		if(otherTop >= top && otherTop <= bottom || otherBottom >= top && otherBottom <= bottom)
			return true;
	}

	return false;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	Vector newHalfSize(_halfSize.x + other->GetRadius(), _halfSize.y + other->GetRadius());
	
	float newLeft = _center.x - newHalfSize.x;
	float newRight = _center.x + newHalfSize.x;
	float newTop = _center.y - newHalfSize.y;
	float newBottom = _center.y + newHalfSize.y;

	Vector circleCenter = other->GetCenter();
	Vector dir = circleCenter - _center;

	if (circleCenter.x >= newLeft && circleCenter.x <= newRight && circleCenter.y >= newTop && circleCenter.y <= newBottom)
	{
		if (dir.Length() <= _halfSize.Length() + other->GetRadius())
		{
			return true;
		}
	}

	return false;
}