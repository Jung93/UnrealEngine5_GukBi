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
	_gravity += 0.1f;
	_circle->GetCenter() += _ballDir * _ballSpeed;

	_circle->GetCenter().y += _gravity;

	//마우스포인터로 유도
	//Vector newV = mousePos - _circle->GetCenter();
	//AddForce(newV.NormalVector());

	//if (_circle->IsCollision(mousePos))
	//	isActive = false;


	//진자운동
	//test
	//_deltaTime += 0.01f;

	//Vector sinV;
	//sinV.x = _ballDir.x;
	//sinV.y = sin(_deltaTime * 10);
	//sinV.x = sin(_deltaTime * 10);
	//sinV.y = _ballDir.y;
	//AddForce(_ballDir + sinV);

}

void Ball::Render(HDC hdc)
{
	if (isActive == false) return;

	_circle->Render(hdc);

}

void Ball::AddForce(Vector v)
{
	//if (isActive == false) return;

	_circle->SetCenter(_circle->GetCenter() + v * _ballSpeed);
}
