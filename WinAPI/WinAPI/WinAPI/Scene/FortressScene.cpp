#include "framework.h"
#include "FortressScene.h"

#include "Objects/Cannon/Cannon.h"
#include "Objects/Cannon/Ball.h"


FortressScene::FortressScene()
{
	_cannon1 = make_shared<Cannon>(Vector(200, 500), 50);
	_cannon2 = make_shared<Cannon>(Vector(900, 500), 50);
}

FortressScene::~FortressScene()
{
}

void FortressScene::Update()
{
	if(isTurn == false)
		_cannon1->Update();
	else if(isTurn)
		_cannon2->Update();

	if (_cannon2->IsHited(_cannon1->GetBall()) || _cannon2->IsMissed(_cannon1->GetBall()))
	{
		isTurn = !isTurn;
	};

	if (_cannon1->IsHited(_cannon2->GetBall()) || _cannon1->IsMissed(_cannon2->GetBall()))
	{
		isTurn = !isTurn;
	};



}

void FortressScene::Render(HDC hdc)
{
	_cannon1->Render(hdc);
	_cannon2->Render(hdc);
}

