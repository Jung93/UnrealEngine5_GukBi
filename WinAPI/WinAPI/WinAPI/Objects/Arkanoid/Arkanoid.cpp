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

	CreateBlock();

	_ball = make_shared<ArkanoidBall>(Vector(offset.x, offset.y - 20));

	for (int i = 0; i < 3;i++)
	{
		shared_ptr<ArkanoidBall> life = make_shared<ArkanoidBall>(Vector(50 + 50 * i,650));
		_lifes.push_back(life);
	}
}

Arkanoid::~Arkanoid()
{
}

void Arkanoid::Update()
{
	srand(time(nullptr));

	if (_gameOver == true)
		return;

	_player->Update();

	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{

			_ball->IsCollison(block);

			if(block->isLive)
				block->Update();
		}
	}

	_ball->IsCollison(_player);

	_ball->Update();

	IsDead();

	for (int i = 0; i < _lifes.size();i++)
	{
		_lifes[i]->Update();
	}

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

	for (int i = 0; i < _lifes.size();i++)
	{
		_lifes[i]->Render(hdc);
	}

}

void Arkanoid::Fire()
{
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		isFired = true;
		_ball->SetDir(Vector(0, -1));
	}
}

bool Arkanoid::IsDead()
{
	if (_ball->GetCenter().y > WIN_HEIGHT)
	{
		if (_lifes.empty() == false)
		{
			_lifes.pop_back();
			_ball->SetDir(Vector(0, -1));
			isFired = false;
		}
		else
		{
			_gameOver = true;

		}

		return true;
	}
	return false;
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
