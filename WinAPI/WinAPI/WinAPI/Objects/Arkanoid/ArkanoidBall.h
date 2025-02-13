#pragma once

class ArkanoidBlock;
class ArkanoidPlayer;

class ArkanoidBall : public CircleCollider
{
public:
	ArkanoidBall(Vector pos);
	~ArkanoidBall();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void IsCollison(shared_ptr<ArkanoidBlock> block);
	void IsCollison(shared_ptr<ArkanoidPlayer> player);

	Vector GetDir() { return _ballDir; }
	void SetDir(Vector dir) { _ballDir = dir; }

private:
	HBRUSH _brush;

	Vector _ballDir;

	float _ballSpeed = 3.0f;
};

