#pragma once
class RectCollider : public Collider
{
public:
	RectCollider(Vector center, Vector size);
	~RectCollider();


	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	Vector GetHalfSize() { return _halfSize; }


	virtual bool IsCollision(const Vector& pos) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;

private:
	Vector _halfSize;
};

