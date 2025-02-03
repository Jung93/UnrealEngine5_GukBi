#pragma once
class ArkanoidBall : public CircleCollider
{
public:
	ArkanoidBall(Vector pos);
	~ArkanoidBall();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;



private:
	HBRUSH _brush;


};

