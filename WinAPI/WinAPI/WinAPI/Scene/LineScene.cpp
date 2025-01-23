#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	_floor = make_shared<Line>(Vector(100, 600), Vector(1200, 600));
	_line1 = make_shared<Line>(Vector(100, 100), Vector(100, 100));
	_shadow = make_shared<Line>(Vector(100, 500), Vector(101, 500));

}

LineScene::~LineScene()
{
}

void LineScene::Update()
{
	_floor->Update();
	_line1->Update();
	_shadow->Update();
	_line1->end = mousePos;

	Vector line1V = _line1->end - _line1->start;
	Vector floorV = _floor->end - _floor->start;

	Vector ev = floorV.NormalVector();
	float shadowLength = ev.Dot(line1V);

	_shadow->end = _shadow->start + ev * shadowLength;


}

void LineScene::Render(HDC hdc)
{
	_floor->Render(hdc);
	_line1->Render(hdc);
	_shadow->Render(hdc);
}
