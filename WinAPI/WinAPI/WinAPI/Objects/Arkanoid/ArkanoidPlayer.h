#pragma once
class ArkanoidBall;

class ArkanoidPlayer : public RectCollider
{
public:
	ArkanoidPlayer();
	~ArkanoidPlayer();

	void Init();


	virtual void Update() override;
	virtual void Render(HDC hdc) override;


	void Move();
	bool IsDead();


private:
	HBRUSH _brush;
	float _speed = 5.0f;

	shared_ptr<ArkanoidBall> _ball;
	vector<shared_ptr<ArkanoidBall>> _lifes;

};

