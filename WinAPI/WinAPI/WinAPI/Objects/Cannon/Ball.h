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
	void SetDir(Vector dir) { _ballDir = dir.NormalVector(); }
	//void SetDir(Vector v) { _ballDir = v; }


	void InitGravity() { _gravity = 0.0f; }
	bool isActive = false;

private:
	shared_ptr<CircleCollider> _circle;

	Vector _ballDir = Vector(1,0);
	float _ballSpeed = 6.0f;
	float _gravity = 0.0f;
	float _deltaTime = 0.0f;
};

