#pragma once
class Ball
{
public:
	Ball();
	~Ball();

	void Update();
	void Render(HDC hdc);

	void SetPos(Vector pos) { _circle->SetCenter(pos); }
	void AddForce(Vector v);

	bool isActive = false;

private:
	shared_ptr<CircleCollider> _circle;

	Vector _ballDir = Vector(1,0);
	float _ballSpeed = 3.0f;
	Vector _gravity = Vector(0, 0.01f);
};

