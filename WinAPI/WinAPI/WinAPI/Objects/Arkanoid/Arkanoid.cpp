#include "framework.h"
#include "Arkanoid.h"

#include "ArkanoidPlayer.h"
#include "ArkanoidBlock.h"
#include "ArkanoidBall.h"

Arkanoid::Arkanoid()
{
	Vector offset = Vector(600, 600);

	_player = make_shared<ArkanoidPlayer>();

	_player->SetCenter(offset);
	_player->SetGreen();

	Vector blockOffset = Vector(300, 200);

	_blocks.resize(3);

	for (int y = 0; y < 3; y++)
	{
		_blocks[y].reserve(7);
		for (int x = 0; x < 7; x++)
		{
			shared_ptr<ArkanoidBlock> block = make_shared<ArkanoidBlock>();
			Vector pos;
			pos.x = x * 105;
			pos.y = y * 20;
			block->SetCenter(pos + blockOffset);
			block->SetBlockType(ArkanoidBlock::Type::BLOCKS);

			_blocks[y].push_back(block);
			_blocks[y][x]->SetRed();
		}
	}

	_ball = make_shared<ArkanoidBall>(Vector(offset.x, offset.y - 20));
}

Arkanoid::~Arkanoid()
{
}

void Arkanoid::Update()
{
	_player->Update();

	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{

			//if (block->IsCollision(_ball) == true) 
			//{
			//	block->DeActive();
			//}
			_ball->IsCollison(block);

			if(block->isLive)
				block->Update();
		}
	}

	_ball->Update();

	Fire();

	if(isFired == false)
		_ball->SetCenter(Vector(_player->GetCenter().x, _player->GetCenter().y - 20));




}	

void Arkanoid::Render(HDC hdc)
{

	_player->Render(hdc);

	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{
			if (block->isLive)
				block->Render(hdc);
		}
	}
	_ball->Render(hdc);
}

void Arkanoid::Fire()
{
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		isFired = true;
		_ball->SetDir(Vector(0, -1));
	}
}
