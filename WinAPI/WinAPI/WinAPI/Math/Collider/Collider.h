#pragma once

class CircleCollider;
class RectCollider;

class Collider : public enable_shared_from_this<Collider>
{
public:
	Collider(Vector center);
	~Collider();

	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;


	bool IsCollision(shared_ptr<Collider> other);
	virtual bool IsCollision(const Vector& pos) abstract;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) abstract;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) abstract;

	void SetGreen() { _curPen = 0; }
	void SetRed() { _curPen = 1; }

	Vector& GetCenter() { return _center; }
	void SetCenter(const Vector& pos) { _center = pos; }

	vector<HPEN> GetPens() { return _pens; }
	UINT GetCurPen() { return _curPen; }

private:
	UINT			_curPen = 0;
	vector<HPEN>	_pens;

	Vector _center;

};

