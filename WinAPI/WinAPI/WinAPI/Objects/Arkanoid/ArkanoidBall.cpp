#include "framework.h"
#include "ArkanoidBall.h"

#include "ArkanoidBlock.h"

ArkanoidBall::ArkanoidBall(Vector pos)
	:CircleCollider(pos, 10)
{
	_brush = CreateSolidBrush(BLACK);
}

ArkanoidBall::~ArkanoidBall()
{
}

void ArkanoidBall::Update()
{
	CircleCollider::Update();

	Vector center = GetCenter();

	if (center.x < 0 || center.x > WIN_WIDTH)
		_ballDir.x *= -1;
	if (center.y < 0)
		_ballDir.y *= -1;


	SetCenter(GetCenter() + _ballDir);
}

void ArkanoidBall::Render(HDC hdc)
{
	SelectObject(hdc, _brush);
	CircleCollider::Render(hdc);


}

void ArkanoidBall::IsCollison(shared_ptr<ArkanoidBlock> block)
{
	Vector dir = GetCenter() - block->GetCenter();
	Vector rightV = Vector(1, 0);
	Vector upV = Vector(0, -1);

	Vector halfSize = block->GetHalfSize();

	if (block->isLive == false)
		return;

	//����ó��
	if (dir.Length() > halfSize.Length() + GetRadius())
		return;

	//x�� ����
	float lengthX = abs(rightV.Dot(dir));
	if (lengthX > halfSize.x + GetRadius())
		return;

	//y�� ����
	float lengthY = abs(upV.Dot(dir));
	if (lengthY > halfSize.y + GetRadius())
		return;

	//�浹�� ��� ����
	block->DeActive();
	_ballDir.y *= -1;

	//�ݻ�ó��


}


