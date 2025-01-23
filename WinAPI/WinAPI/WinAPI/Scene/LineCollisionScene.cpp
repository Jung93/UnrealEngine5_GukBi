#include "framework.h"
#include "LineCollisionScene.h"

LineCollisionScene::LineCollisionScene()
{
	_line1 = make_shared<Line>(Vector(100, 100), Vector(100, 100));
	_line2 = make_shared<Line>(Vector(100, 500), Vector(700, 200));
	_crossCircle = make_shared<CircleCollider>(Vector(-100, -100), 30.0f);

}

LineCollisionScene::~LineCollisionScene()
{
}

void LineCollisionScene::Update()
{
	_line1->Update();
	_line2->Update();

	_line1->end = mousePos;

	Line::Cross cross = _line2->IsCollision(_line1);

	if (cross.isCollision)
	{
		_line2->SetRed();
		_crossCircle->SetCenter(cross.corssPoint);
	}
	else
	{
		_line2->SetGreen();
	}

}

void LineCollisionScene::Render(HDC hdc)
{
	_crossCircle->Render(hdc);
	_line1->Render(hdc);
	_line2->Render(hdc);
}
