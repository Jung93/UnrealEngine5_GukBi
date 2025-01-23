#include "framework.h"
#include "Line.h"

Line::Line(Vector start, Vector end)
	: start(start), end(end)
{
	_pens.push_back(CreatePen(1, 3, GREEN));
	_pens.push_back(CreatePen(1, 3, RED));
}

Line::~Line()
{
	for(auto& pen : _pens)
		DeleteObject(pen);
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curPen]);

	MoveToEx(hdc, start.x, start.y, nullptr);
	LineTo(hdc, end.x, end.y);



}

Line::Cross Line::IsCollision(shared_ptr<Line> other)
{
	Cross result;

	Vector startV = start - other->start;
	Vector endV = end - other->start;
	Vector line1V = other->end - other->start;
	Vector myVector = end - start;

	float cross1 = startV.Cross(line1V);
	float cross2 = endV.Cross(line1V);

	if (cross1 * cross2 >= 0)
		return result;

	Vector otherEndV = other->end - start;

	if (otherEndV.Cross(myVector) > 0)
		return result;


	float left = fabs(cross1);
	float right = fabs(cross2);
	float ratio = left / (left + right);

	Vector crossPoint = start + myVector * ratio;

	result.corssPoint = crossPoint;
	result.isCollision = true;

	return result;
}
