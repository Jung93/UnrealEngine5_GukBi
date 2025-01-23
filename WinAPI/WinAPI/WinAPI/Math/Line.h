#pragma once
class Line
{
public:
	struct Cross
	{
		bool isCollision = false;
		Vector corssPoint;
	};

	Line(Vector start, Vector end);
	~Line();

	void Update();
	void Render(HDC hdc);

	Cross IsCollision(shared_ptr<Line> other);

	void SetGreen() { _curPen = 0; }
	void SetRed() { _curPen = 1; }

	Vector start;
	Vector end;

private:
	UINT			_curPen = 0;
	vector<HPEN>	_pens;

};

