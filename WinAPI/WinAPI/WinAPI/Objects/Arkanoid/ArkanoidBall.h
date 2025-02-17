#pragma once

class ArkanoidBlock;
class ArkanoidPlayer;

class ArkanoidBall : public CircleCollider
{
public:
	ArkanoidBall(shared_ptr<ArkanoidPlayer> player);
	~ArkanoidBall();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void IsCollison(shared_ptr<ArkanoidBlock> block);
	void IsCollison(shared_ptr<ArkanoidPlayer> player);

	Vector GetDir() { return _ballDir; }

	void SetDir(Vector dir) { _ballDir = dir; }
	void SetActive() { _isActive = true; }
	void DeAtive() { _isActive = false; }

	void Fire() { _isFired = true; }
	void ReadyFire() { _isFired = false; }

	bool IsFired() { return _isFired; }
	bool IsActive() { return _isActive; }

	void Fixed();

private:
	HBRUSH _brush;

	weak_ptr<ArkanoidPlayer> _player;
	Vector _ballDir;
	float _ballSpeed = 3.0f;

	bool _isFired = false;
	bool _isActive = false;

};

