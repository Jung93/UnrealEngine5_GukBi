#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_circle = make_shared<CircleCollider>(Vector(450, 500), 100.0f);
	_movingCircle = make_shared<CircleCollider>(Vector(0, 0), 60.0f);

	_rect = make_shared<RectCollider>(Vector(300, 300), Vector(200, 200));
	_movingRect = make_shared<RectCollider>(Vector(0, 0), Vector(200, 200));
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	_movingRect->SetCenter(mousePos);

	if (_circle->IsCollision(_movingRect))
	{
		_circle->SetRed();
	}
	else
	{
		_circle->SetGreen();
	}


	_circle->Update();
	_rect->Update();
	_movingRect->Update();

}

void CollisionScene::Render(HDC hdc)
{
	_circle->Render(hdc);
	_rect->Render(hdc);
	_movingRect->Render(hdc);
}
