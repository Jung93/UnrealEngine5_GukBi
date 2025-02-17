#include "framework.h"
#include "Arkanoid.h"

#include "ArkanoidPlayer.h"
#include "ArkanoidBlock.h"
#include "ArkanoidBall.h"

#pragma comment(lib, "winmm.lib")

Arkanoid::Arkanoid()
{
	Vector offset = Vector(600, 600);

	PlaySound(TEXT("Objects//Arkanoid//ArkanoidSound//Arkanoid SFX (9).wav"), NULL, SND_FILENAME | SND_ASYNC);

	CreateBlock();
}

Arkanoid::~Arkanoid()
{
}

void Arkanoid::Update()
{
	srand(time(nullptr));

	if (_gameOver == true)
		return;


	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{


			if(block->isLive)
				block->Update();
		}
	}
}	

void Arkanoid::Render(HDC hdc)
{
	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{
			if (block->isLive)
				block->Render(hdc);
		}
	}
}

void Arkanoid::CreateBlock()
{
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
}

void Arkanoid::IsCollision(shared_ptr<ArkanoidBall> ball)
{
	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{
			if (block->isLive)
				ball->IsCollison(block);
		}
	}
}






