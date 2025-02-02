#include "framework.h"
#include "Ball.h"

Ball::Ball()
{
	_circle = make_shared<CircleCollider>(Vector(-1000, -1000), 10);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (isActive == false) return;

	_circle->Update();

	DeActiveByMiss();
	//DeActive();

	//중력
	//_gravity += 0.1f;
	//_circle->GetCenter() += _ballDir * _ballSpeed;
	//_circle->GetCenter().y += _gravity;

	//마우스포인터로 유도
	//Vector newV = mousePos - _circle->GetCenter();
	//AddVector(newV.NormalVector());

	//if (_circle->IsCollision(mousePos))
	//	isActive = false;


	//진자운동
	_deltaTime += 0.05f; 

	Vector forwardMove = _ballDir * 2.0f;
	Vector sinVec = Vector(0, _ballSpeed * -sin(_deltaTime * _ballSpeed));

	float cosSeta = _ballDir.x;
	float sinSeta = _ballDir.y;

	Vector rotatedSinVec = Vector(sinVec.y * sinSeta, -sinVec.y * cosSeta);
	Vector totalMove = forwardMove + rotatedSinVec;

	_circle->GetCenter() += totalMove;
}

void Ball::Render(HDC hdc)
{
	if (isActive == false) return;

	_circle->Render(hdc);

}

void Ball::AddVector(Vector v)
{
	if (isActive == false) return;
	_circle->SetCenter(_circle->GetCenter() + v);
	//SetDir(v);



}

bool Ball::DeActiveByHit(shared_ptr<CircleCollider> enemy)
{
	if (enemy != nullptr && _circle->IsCollision(enemy))
	{
		isActive = false;
		return true;
	}

	return false;
}

bool Ball::DeActiveByMiss()
{
	if (_circle->GetCenter().x > WIN_WIDTH || _circle->GetCenter().x < 0
		|| _circle->GetCenter().y > WIN_HEIGHT || _circle->GetCenter().y < 0)
	{
		isActive = false;
		return true;
	}

	return false;
}

