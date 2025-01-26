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


	if (_circle->GetCenter().x > WIN_WIDTH || _circle->GetCenter().x < 0
		|| _circle->GetCenter().y > WIN_HEIGHT || _circle->GetCenter().y < 0)
		isActive = false;

	//중력
	//AddForce(_ballDir + _gravity);


	//마우스포인터로 유도
	Vector newV = mousePos - _circle->GetCenter();
	AddForce(newV.NormalVector());

	if (_circle->IsCollision(mousePos))
		isActive = false;


	//진자운동
	
}

void Ball::Render(HDC hdc)
{
	if (isActive == false) return;

	_circle->Render(hdc);

}

void Ball::AddForce(Vector v)
{
	//if (isActive == false) return;

	_ballDir = v;
	_circle->SetCenter(_circle->GetCenter() + _ballDir * _ballSpeed);
}
