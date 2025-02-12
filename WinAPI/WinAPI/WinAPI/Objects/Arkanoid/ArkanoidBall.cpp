#include "framework.h"
#include "ArkanoidBall.h"

#include "ArkanoidBlock.h"
#include "ArkanoidPlayer.h"

#pragma comment(lib, "winmm.lib")


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


	SetCenter(GetCenter() + _ballDir * _ballSpeed);
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

	//예외처리
	if (dir.Length() > halfSize.Length() + GetRadius())
		return;

	//x축 내적
	float lengthX = abs(rightV.Dot(dir));
	if (lengthX > halfSize.x + GetRadius())
		return;

	//y축 내적
	float lengthY = abs(upV.Dot(dir));
	if (lengthY > halfSize.y + GetRadius())
		return;

	//충돌한 블록 제거
	block->DeActive();
	_ballDir.y *= -1;
	PlaySound(TEXT("Objects//Arkanoid//ArkanoidSound//Arkanoid SFX (6).wav"), NULL, SND_FILENAME | SND_ASYNC);

}


void ArkanoidBall::IsCollison(shared_ptr<ArkanoidPlayer> player)
{
	Vector dir = GetCenter() - player->GetCenter();
	Vector rightV = Vector(1, 0);
	Vector upV = Vector(0, -1);

	Vector halfSize = player->GetHalfSize();

	//예외처리
	if (dir.Length() > halfSize.Length() + GetRadius())
		return;

	//x축 내적
	float lengthX = abs(rightV.Dot(dir));
	if (lengthX > halfSize.x + GetRadius())
		return;

	//y축 내적
	float lengthY = abs(upV.Dot(dir));
	if (lengthY > halfSize.y + GetRadius())
		return;

	Vector hit = GetCenter() - player->GetCenter();

	_ballDir = hit.NormalVector();

	//반사처리

	PlaySound(TEXT("Objects//Arkanoid//ArkanoidSound//Arkanoid SFX (8).wav"), NULL, SND_FILENAME | SND_ASYNC);

}
