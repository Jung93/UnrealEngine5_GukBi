#pragma once
class Arkanoid;
class ArkanoidPlayer;

class ArkanoidScene : public Scene
{
public:
	ArkanoidScene();
	~ArkanoidScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render(HDC hdc) override;



private:
	shared_ptr<Arkanoid> _arkanoid;
	shared_ptr<ArkanoidPlayer> _player;

};

