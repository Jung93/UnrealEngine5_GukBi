#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector center, float raidus)
	: _center(center), _radius(raidus)
{
	_pens.push_back(CreatePen(1, 3, GREEN));
	_pens.push_back(CreatePen(1, 3, RED));
}

CircleCollider::~CircleCollider()
{
	for (auto& pen : _pens)
		DeleteObject(pen);
}

void CircleCollider::Update()
{
}

void CircleCollider::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curPen]);

	float left		= _center.x - _radius;
	float right		= _center.x + _radius;
	float top		= _center.y - _radius;
	float bottom	= _center.y + _radius;

	Ellipse(hdc, left, top, right, bottom);
}

bool CircleCollider::IsCollision(const Vector& pos)
{
	Vector circleCenter = GetCenter();
	Vector dir = pos - circleCenter;

	return dir.Length() < _radius;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	Vector thisCenter = GetCenter();
	Vector otherCenter = other->GetCenter();
	Vector dir = otherCenter - thisCenter;

	return dir.Length() < _radius + other->_radius;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other)
{
	Vector newHalfSize(other->GetHalfSize().x + _radius, other->GetHalfSize().y + _radius);

	float newLeft = _center.x - newHalfSize.x;
	float newRight = _center.x + newHalfSize.x;
	float newTop = _center.y - newHalfSize.y;
	float newBottom = _center.y + newHalfSize.y;

	Vector rectCenter = other->GetCenter();
	Vector dir = rectCenter - _center;

	if (rectCenter.x >= newLeft && rectCenter.x <= newRight && rectCenter.y >= newTop && rectCenter.y <= newBottom)
	{
		if (dir.Length() <= other->GetHalfSize().Length() + _radius)
		{
			return true;
		}
	}

	return false;
}