#include "framework.h"
#include "Cannon.h"
#include "Barrel.h"
#include "Ball.h"

Cannon::Cannon()
	:_hp(3)
{
	_speed = 10.0f;

	_body = make_shared<CircleCollider>(CENTER, 50);
	_barrel = make_shared<Barrel>(dynamic_pointer_cast<CircleCollider>(_body));

	_poolCount = 10;
	for (int i = 0; i < _poolCount;i++)
	{
		shared_ptr<Ball> ball = make_shared<Ball>();
		_balls.push_back(ball);
	}
}

Cannon::Cannon(Vector vec, float size)
	:_hp(3)
{
	_speed = 10.0f;

	_body = make_shared<CircleCollider>(vec, size);
	_barrel = make_shared<Barrel>(dynamic_pointer_cast<CircleCollider>(_body));

	_poolCount = 10;
	for (int i = 0; i < _poolCount;i++)
	{
		shared_ptr<Ball> ball = make_shared<Ball>();
		_balls.push_back(ball);
	}


	for (int i = 0; i < _hp; i++)
	{
		shared_ptr<RectCollider> hpBar = make_shared<RectCollider>(_body->GetCenter() + Vector(-30 + i*30, 100), Vector(30, 50));
		_hpBar.push_back(hpBar);
	}

}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	if (IsDead())
		return;

	_body->Update();
	_barrel->Update();

	for (int i = 0; i < _hpBar.size();i++)
	{
		_hpBar[i]->SetCenter(_body->GetCenter() + Vector(-30 + i * 30, 100));

		_hpBar[i]->Update();
	}


	for (auto ball : _balls)
	{
		ball->Update();
		IsHited(ball);
	}

	_delay += 0.1f;

	Fire();
	Move();
}

void Cannon::Render(HDC hdc)
{
	if (IsDead())
		return;

	_barrel->Render(hdc);
	_body->Render(hdc);

	for (auto ball : _balls)
	{
		ball->Render(hdc);
	}

	for (auto hp : _hpBar)
	{
		hp->Render(hdc);
	}
}

void Cannon::Move()
{
	if (_isFired == false)
	{
		if (GetKeyState('A') & 0x8000)
		{
			_body->SetCenter(_body->GetCenter() + Vector(-1, 0) * _speed);
		}

		if (GetKeyState('D') & 0x8000)
		{
			_body->SetCenter(_body->GetCenter() + Vector(1, 0) * _speed);
		}

		if (GetKeyState('W') & 0x8000)
		{
			_barrel->SetAngle(_barrel->GetAngle() - 0.1f);
		}

		if (GetKeyState('S') & 0x8000)
		{
			_barrel->SetAngle(_barrel->GetAngle() + 0.1f);
		}
	}
}

void Cannon::Fire()
{
	if (_delay < _attackSpeed)
		return;

	auto iter = find_if(_balls.begin(), _balls.end(), [](shared_ptr<Ball> ball)-> bool
		{
			if (ball->isActive == false)
				return true;
			return false;
		});

	if (iter == _balls.end()) return;

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		(*iter)->SetPos(_barrel->GetMuzzle());
		(*iter)->AddForce(_barrel->GetDir());

		(*iter)->isActive = true;
		//(*iter)->SetDir(_barrel->GetDir());

		_delay = 0.0f;
		(*iter)->InitGravity();
		_isFired == true;
	}

}

bool Cannon::IsHited(shared_ptr<Ball> ball)
{
	if (ball != nullptr && ball->isActive == true && _body->IsCollision(ball->GetCircle()))
	{
		ball->DeActiveByHit(dynamic_pointer_cast<CircleCollider>(_body));
		--_hp;

		_hpBar[_hp]->SetBrushRed();
		_hpBar[_hp]->SetRed();

		return true;
	}
	return false;
}

bool Cannon::IsMissed(shared_ptr<Ball> ball)
{
	if (ball != nullptr && ball->DeActiveByMiss())
	{
		return true;
	}
	return false;

}

bool Cannon::IsDead()
{
	return _hp <= 0;
}

shared_ptr<Ball> Cannon::GetBall()
{
	auto iter = find_if(_balls.begin(), _balls.end(), [](shared_ptr<Ball> ball)-> bool
		{
			if (ball->isActive == true)
				return true;
			return false;
		});

	if (iter == _balls.end())
		return nullptr;

	return (*iter);


}
