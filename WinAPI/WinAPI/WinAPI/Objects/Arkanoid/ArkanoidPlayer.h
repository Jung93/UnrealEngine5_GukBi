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

	shared_ptr<ArkanoidBall> GetBall() { return _ball; }
	vector<shared_ptr<CircleCollider>> GetLife() { return _lifes; }

private:
	HBRUSH _brush;
	float _speed = 5.0f;

	shared_ptr<ArkanoidBall> _ball;
	vector<shared_ptr<CircleCollider>> _lifes;

	bool _gameOver = false;
};

