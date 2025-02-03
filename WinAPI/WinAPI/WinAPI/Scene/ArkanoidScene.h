#pragma once
class Arkanoid;

class ArkanoidScene : public Scene
{
public:
	ArkanoidScene();
	~ArkanoidScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render(HDC hdc) override;



private:
	shared_ptr<Arkanoid> _arkanoid;

};

