#pragma once
class ArkanoidItem
{
public:
	ArkanoidItem();
	~ArkanoidItem();

	void Update();
	void Render(HDC hdc);

	Vector& Pos() { return _pos; }
	bool& CanFalling() { return _canFalling; }
	shared_ptr<CircleCollider> GetCollider() { return _body; }
	void SetSkill(function<void(void)> fn) { _barSkill = fn; }
	void ActiveSkill() { if (_barSkill) { _barSkill(); } }
	void DeActive() { _isActive = false; }
	bool IsActive() { return _isActive; }

private:
	function<void(void)> _barSkill;

	shared_ptr<CircleCollider> _body;

	bool _canFalling = false;
	bool _isActive = true;

	Vector _pos = { 0,0 };
	Vector _dir = { 0,1 };
	float _speed = 4.0f;
};

