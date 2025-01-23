#include "framework.h"
#include "Collider.h"

Collider::Collider(Vector center)
	:_center(center)
{
	_pens.push_back(CreatePen(1, 3, GREEN));
	_pens.push_back(CreatePen(1, 3, RED));

}

Collider::~Collider()
{
	for (auto& pen : _pens)
		DeleteObject(pen);
}

bool Collider::IsCollision(shared_ptr<Collider> other)
{
	if (dynamic_pointer_cast<CircleCollider>(other))
	{
		shared_ptr<CircleCollider> circle = dynamic_pointer_cast<CircleCollider>(other);
		return IsCollision(circle);
	}

	if (dynamic_pointer_cast<RectCollider>(other)) 
	{
		shared_ptr<RectCollider> rect = dynamic_pointer_cast<RectCollider>(other);
		return IsCollision(rect);
	}

    return false;
}
