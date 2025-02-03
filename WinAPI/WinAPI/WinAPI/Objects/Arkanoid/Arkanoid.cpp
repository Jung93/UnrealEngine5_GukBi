#include "framework.h"
#include "Arkanoid.h"

#include "ArkanoidBlock.h"
#include "ArkanoidBall.h"

Arkanoid::Arkanoid()
{

	Vector offset = Vector(600, 600);

	_bar = make_shared<ArkanoidBlock>();

	_bar->SetCenter(offset);
	_bar->SetBlockType(ArkanoidBlock::Type::BAR);
	_bar->SetGreen();

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
		}
	}

	_ball = make_shared<ArkanoidBall>(Vector(offset.x, offset.y - 20));

}

Arkanoid::~Arkanoid()
{
}

void Arkanoid::Update()
{
	_bar->Update();

	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{
			block->Update();
		}
	}

	_ball->Update();

	if (isFired == false)
	{
		_ball->SetCenter(Vector(_bar->GetCenter().x, _bar->GetCenter().y - 20));
		Fire();
	}
	else 
	{
		_ball->SetCenter(_ball->GetCenter() + Vector(0, -1));
	}
}	

void Arkanoid::Render(HDC hdc)
{

	_bar->Render(hdc);

	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{
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
	}
}
