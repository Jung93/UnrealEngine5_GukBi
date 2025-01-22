#pragma once
class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	// Scene을(를) 통해 상속됨
	void Update() override;

	void Render(HDC hdc) override;
private:
	shared_ptr<CircleCollider> _circle;
	shared_ptr<CircleCollider> _movingCircle;

	shared_ptr<RectCollider> _rect;
	shared_ptr<RectCollider> _movingRect;



};

