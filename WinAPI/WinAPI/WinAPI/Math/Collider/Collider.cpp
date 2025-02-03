#include "framework.h"
#include "Collider.h"

Collider::Collider(Vector center)
	:_center(center)
{
	_pens.push_back(CreatePen(1, 3, BLACK));
	_pens.push_back(CreatePen(1, 3, GREEN));
	_pens.push_back(CreatePen(1, 3, RED));

	_brushes.push_back(CreateSolidBrush(GREEN));
	_brushes.push_back(CreateSolidBrush(RED));

}

Collider::~Collider()
{
	for (auto& pen : _pens)
		DeleteObject(pen);

	for (auto& brush : _brushes)
		DeleteObject(brush);
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
