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

	bool IsDead();

	void CreateBlock();

private:
	shared_ptr<ArkanoidPlayer> _player;
	vector<vector<shared_ptr<ArkanoidBlock>>> _blocks;
	shared_ptr<ArkanoidBall> _ball;
	vector<shared_ptr<ArkanoidBall>> _lifes;

	bool isFired = false;
	bool _gameOver = false;
};

