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
	//AddForce(newV.NormalVector());

	//if (_circle->IsCollision(mousePos))
	//	isActive = false;


	//진자운동
	//test
	_deltaTime += 0.05f;

	Vector sinVec = Vector(_ballDir.x, _ballSpeed * -sin(_deltaTime * _ballSpeed));
	//_circle->GetCenter() += _ballDir * _ballSpeed;
	//_circle->GetCenter().y += (_ballSpeed * -sin(_deltaTime * _ballSpeed));
	//_circle->GetCenter().x += (_ballDir.x);



	float cosSeta = abs(_ballDir.Dot(_initDir));
	float sinSeta = _ballDir.Cross(_initDir);

	Vector sinVec2 = Vector(sinVec.x * cosSeta - sinVec.y * sinSeta, sinVec.y * cosSeta + sinVec.x * sinSeta);
	//sinVec.x = sinVec.x * cosSeta - sinVec.y * sinSeta;
	//sinVec.y = sinVec.y * cosSeta + sinVec.x * sinSeta;

	_circle->GetCenter() += sinVec2;

	//_circle->GetCenter() += sinVec;
	//_circle->GetCenter().x += sinVec.x * (cos(_deltaTime * _ballSpeed)) - sinVec.y * sin(_deltaTime * _ballSpeed);
	//_circle->GetCenter().y += sinVec.y * (cos(_deltaTime * _ballSpeed)) + sinVec.x * cos(_deltaTime * _ballSpeed);

	//_circle->GetCenter() += Vector(0, sin(_deltaTime));


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

