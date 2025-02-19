#pragma once
class ArkanoidBall;
class ArkanoidItem;

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

	void EatItem(shared_ptr<ArkanoidItem> item);

	vector<shared_ptr<ArkanoidBall>> GetBall() { return _balls; }
	vector<shared_ptr<CircleCollider>> GetLife() { return _lifes; }
	//shared_ptr<Collider> GetCollider() { return shared_from_this(); }

	void TwoBall_Skill();
	void More_Life();
	void Game_Clear();

	map<int, function<void(void)>> GetSkill() { return _skills; }

private:
	HBRUSH _brush;
	float _speed = 5.0f;

	vector<shared_ptr<ArkanoidBall>> _balls;

	vector<shared_ptr<CircleCollider>> _lifes;

	map<int, function<void(void)>> _skills;


	bool _gameOver = false;
};

