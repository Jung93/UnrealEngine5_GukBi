#include "framework.h"
#include "ArkanoidItem.h"

ArkanoidItem::ArkanoidItem()
{
	_body = make_shared<CircleCollider>(_pos, 5.0f);
}

ArkanoidItem::~ArkanoidItem()
{
}

void ArkanoidItem::Update()
{
	_body->Update();

	_body->SetCenter(_pos);

	if (_canFalling)
		_pos += _dir * _speed;
}

void ArkanoidItem::Render(HDC hdc)
{
	_body->Render(hdc);

}
