#pragma once

class ArkanoidBlock;
class ArkanoidBall;

class Arkanoid
{
public:
	Arkanoid();
	~Arkanoid();

	void Update();
	void Render(HDC hdc);

	void Fire();

private:
	shared_ptr<ArkanoidBlock> _bar;
	vector<vector<shared_ptr<ArkanoidBlock>>> _blocks;
	shared_ptr<ArkanoidBall> _ball;

	bool isFired = false;
};

