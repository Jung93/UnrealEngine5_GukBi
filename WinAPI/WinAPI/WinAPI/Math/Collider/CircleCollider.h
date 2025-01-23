#pragma once

class CircleCollider : public Collider
{
public:
	CircleCollider(Vector center, float raidus);
	~CircleCollider();


	virtual void Update() override;
	virtual void Render(HDC hdc) override;


	float GetRadius() { return _radius; }

	virtual bool IsCollision(const Vector& pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

private:
	float  _radius;


};

