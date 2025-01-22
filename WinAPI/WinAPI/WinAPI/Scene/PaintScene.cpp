#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
	_circle = make_shared<CircleCollider>(Vector(100, 100), 50.0f);
	_rect = make_shared<RectCollider>(Vector(200, 200), Vector(70, 30));

	_pens.push_back(CreatePen(1, 3, RGB(164, 119, 100)));
	_pens.push_back(CreatePen(1, 3, RGB(0, 0, 0)));

	_brushes.push_back(CreateSolidBrush(RGB(164, 119, 100)));
	_brushes.push_back(CreateSolidBrush(RGB(0, 0, 0)));
}

PaintScene::~PaintScene()
{
	for (auto& pen : _pens)
		DeleteObject(pen);

	for (auto& brush : _brushes)
		DeleteObject(brush);
}

void PaintScene::Update()
{
	_circle->Update();
	_rect->Update();
	
}

void PaintScene::Render(HDC hdc)
{

	SelectObject(hdc, _pens[0]);
	SelectObject(hdc, _brushes[0]);
	_rect->Render(hdc);



	SelectObject(hdc, _pens[1]);
	SelectObject(hdc, _brushes[1]);
	_circle->Render(hdc);
}
