#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector center, float raidus)
	: Collider(center), _radius(raidus)
{
	SetGreen();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{


}

void CircleCollider::Render(HDC hdc)
{
	vector<HPEN> pens = GetPens();
	UINT curPen = GetCurPen();
	SelectObject(hdc, pens[curPen]);

	Vector center = GetCenter();

	float left		= center.x - _radius;
	float right		= center.x + _radius;
	float top		= center.y - _radius;
	float bottom	= center.y + _radius;

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
	//Vector newHalfSize(other->GetHalfSize().x + _radius, other->GetHalfSize().y + _radius);
	//Vector center = GetCenter();

	//float newLeft = center.x - newHalfSize.x;
	//float newRight = center.x + newHalfSize.x;
	//float newTop = center.y - newHalfSize.y;
	//float newBottom = center.y + newHalfSize.y;

	//Vector rectCenter = other->GetCenter();
	//Vector dir = rectCenter - center;

	//if (rectCenter.x >= newLeft && rectCenter.x <= newRight && rectCenter.y >= newTop && rectCenter.y <= newBottom)
	//{
	//	if (dir.Length() <= other->GetHalfSize().Length() + _radius)
	//	{
	//		return true;
	//	}
	//}

	return other->IsCollision(dynamic_pointer_cast<CircleCollider>(shared_from_this()));
}