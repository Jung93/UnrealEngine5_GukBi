#pragma once
class Cannon;

class FortressScene : public Scene
{
public:

	FortressScene();
	~FortressScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;


	bool isTurn = false;

private:
	shared_ptr<Cannon> _cannon1;
	shared_ptr<Cannon> _cannon2;

};

