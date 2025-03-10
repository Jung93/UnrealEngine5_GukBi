#pragma once
class ArkanoidHpBar
{
public:
	ArkanoidHpBar(Vector center, Vector size);
	~ArkanoidHpBar();

	void Update();
	void Render(HDC hdc);
	void SetValue(float value);

private:
	shared_ptr<RectCollider> _bg;
	shared_ptr<RectCollider> _value;

	HBRUSH _redBrush;
	HBRUSH _oldBrush;
};

