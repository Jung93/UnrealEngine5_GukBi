#pragma once

class ArkanoidPlayer;
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


	void CreateBlock();

private:
	vector<vector<shared_ptr<ArkanoidBlock>>> _blocks;
	shared_ptr<ArkanoidBall> _ball;

	bool isFired = false;
	bool _gameOver = false;
};

