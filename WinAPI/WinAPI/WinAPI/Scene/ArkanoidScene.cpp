#include "framework.h"
#include "ArkanoidScene.h"

#include "Objects/Arkanoid/Arkanoid.h"
#include "Objects/Arkanoid/ArkanoidPlayer.h"

ArkanoidScene::ArkanoidScene()
{
	_player = make_shared<ArkanoidPlayer>();
	_arkanoid = make_shared<Arkanoid>();

	Vector offset = Vector(600, 600);
	_player->SetCenter(offset);
	_player->SetGreen();

	_player->Init();
	_arkanoid->Init(_player);
}

ArkanoidScene::~ArkanoidScene()
{
}

void ArkanoidScene::Update()
{
	_arkanoid->Update();
	_player->Update();

	_player->Move();

	_arkanoid->IsCollision(_player->GetBall());


	for (auto life : _player->GetLife())
	{
		life->Update();
	}
	_arkanoid->GetItems(_player);
}

void ArkanoidScene::Render(HDC hdc)
{
	_arkanoid->Render(hdc);
	_player->Render(hdc);

	for (auto life : _player->GetLife())
	{
		life->Render(hdc);
	}
}
