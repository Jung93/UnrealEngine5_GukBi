#pragma once
class ArkanoidPlayer : public RectCollider
{
public:
	ArkanoidPlayer();
	~ArkanoidPlayer();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;


	void Move();


private:
	HBRUSH _brush;
	float _speed = 5.0f;

};

