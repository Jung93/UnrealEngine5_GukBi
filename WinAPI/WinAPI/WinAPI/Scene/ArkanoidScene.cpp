#include "framework.h"
#include "ArkanoidScene.h"

#include "Objects/Arkanoid/Arkanoid.h"
#include "Objects/Arkanoid/ArkanoidPlayer.h"

ArkanoidScene::ArkanoidScene()
{
	_arkanoid = make_shared<Arkanoid>();

	_player = make_shared<ArkanoidPlayer>();
	Vector offset = Vector(600, 600);

	_player->SetCenter(offset);
	_player->SetGreen();
}

ArkanoidScene::~ArkanoidScene()
{
}

void ArkanoidScene::Update()
{
	_arkanoid->Update();
	_player->Update();
}

void ArkanoidScene::Render(HDC hdc)
{
	_arkanoid->Render(hdc);
	_player->Render(hdc);
}
