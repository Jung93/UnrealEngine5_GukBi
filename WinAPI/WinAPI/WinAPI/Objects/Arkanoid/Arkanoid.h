#pragma once

class ArkanoidPlayer;
class ArkanoidBlock;
class ArkanoidBall;
class ArkanoidItem;

class Arkanoid
{
public:
	Arkanoid();
	~Arkanoid();

	void Update();
	void Render(HDC hdc);

	void CreateBlock();
	void Init(shared_ptr<ArkanoidPlayer> bar);

	void IsCollision(vector<shared_ptr<ArkanoidBall>> balls);

	void GetItems(shared_ptr<ArkanoidPlayer> player);


private:
	vector<vector<shared_ptr<ArkanoidBlock>>> _blocks;
	vector<shared_ptr<ArkanoidItem>> _items;

	bool isFired = false;
	bool _gameOver = false;
};

