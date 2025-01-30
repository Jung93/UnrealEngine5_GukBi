#pragma once
class Barrel;
class Ball;

class Cannon : public enable_shared_from_this<Cannon>
{
public:
	Cannon();
	Cannon(Vector vec, float size);
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void Move();
	void Fire();

	bool IsHited(shared_ptr<Ball> ball);

	shared_ptr<CircleCollider> GetCollider() { return _body; }
	shared_ptr<Ball> GetBall();


private:
	shared_ptr<CircleCollider> _body;
	shared_ptr<Barrel> _barrel;

	//object pooling
	vector<shared_ptr<Ball>> _balls;
	//Vector _ballDir;
	
	int _poolCount;
	float _speed;

	float _delay = 0.0f;
	const float _attackSpeed = 3.0f;
	Vector _gravity = Vector(0, 1);
	bool _isFired = false;
};

