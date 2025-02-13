#pragma once
class ArkanoidBall;

class ArkanoidPlayer : public RectCollider
{
public:
	ArkanoidPlayer();
	~ArkanoidPlayer();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;


	void Move();
	bool IsDead();


private:
	HBRUSH _brush;
	float _speed = 5.0f;

	vector<shared_ptr<ArkanoidBall>> _lifes;

};

