#pragma once
class LineCollisionScene : public Scene
{

public:
	LineCollisionScene();
	~LineCollisionScene();


	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Line> _line1;
	shared_ptr<Line> _line2;
	shared_ptr<CircleCollider> _crossCircle;

};

