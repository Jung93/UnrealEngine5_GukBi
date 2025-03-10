#include "framework.h"
#include "ArkanoidScene.h"

#include "Objects/Arkanoid/Arkanoid.h"
#include "Objects/Arkanoid/ArkanoidPlayer.h"
#include "Objects/Arkanoid/ArkanoidHpBar.h"

ArkanoidScene::ArkanoidScene()
{
	_player = make_shared<ArkanoidPlayer>();
	_arkanoid = make_shared<Arkanoid>();

	Vector offset = Vector(600, 600);
	_player->SetCenter(offset);
	_player->SetGreen();

	_player->Init();
	_arkanoid->Init(_player);

	_ui_hpBar = make_shared<ArkanoidHpBar>(CENTER + Vector(0, 300), Vector(600, 30));

	_ui_hpBar->SetValue(0.5);

}

ArkanoidScene::~ArkanoidScene()
{
}

void ArkanoidScene::Update()
{
	_arkanoid->Update();
	_player->Update();
	_ui_hpBar->Update();

	_player->Move();

	_arkanoid->IsCollision(_player->GetBall());


	//for (auto life : _player->GetLife())
	//{
	//	life->Update();
	//}
	_arkanoid->GetItems(_player);
}

void ArkanoidScene::Render(HDC hdc)
{
	_arkanoid->Render(hdc);
	_player->Render(hdc);

	//for (auto life : _player->GetLife())
	//{
	//	life->Render(hdc);
	//}

	_ui_hpBar->Render(hdc);

}
