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

	void CreateBlock();
	void IsCollision(shared_ptr<ArkanoidBall> ball);


private:
	vector<vector<shared_ptr<ArkanoidBlock>>> _blocks;

	bool isFired = false;
	bool _gameOver = false;
};

