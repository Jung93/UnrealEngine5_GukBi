#pragma once
class Arkanoid;
class ArkanoidPlayer;

class ArkanoidScene : public Scene
{
public:
	ArkanoidScene();
	~ArkanoidScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Arkanoid> _arkanoid;
	shared_ptr<ArkanoidPlayer> _player;

};

