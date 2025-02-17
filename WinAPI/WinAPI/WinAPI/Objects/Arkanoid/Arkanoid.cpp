#include "framework.h"
#include "Arkanoid.h"

#include "ArkanoidPlayer.h"
#include "ArkanoidBlock.h"
#include "ArkanoidBall.h"
#include "ArkanoidItem.h"

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

void Arkanoid::Init(shared_ptr<ArkanoidPlayer> bar)
{
	for (int i = 0; i < 3; i++)
	{
		shared_ptr<ArkanoidItem> item = make_shared<ArkanoidItem>();
		item->SetSkill(std::bind(&ArkanoidPlayer::TwoBall_Skill, bar));
		_items.push_back(item);

		int randY = rand() % _blocks.size();
		int randX = rand() % _blocks[randY].size();
		_blocks[randY][randX]->SetItem(item);
		_blocks[randY][randX]->SetBlockType(ArkanoidBlock::Type::ITEM_BLOCKS);
		_blocks[randY][randX]->SetBlue();

	}
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

	for (auto item : _items)
		item->Update();
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

	for (auto item : _items)
	{
		if (item->IsActive())
			item->Render(hdc);
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

void Arkanoid::IsCollision(vector<shared_ptr<ArkanoidBall>> balls)
{
	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{
			if (block->isLive)
			{
				for (auto ball : balls)
				{
					ball->IsCollison(block);
				}

			}
		}
	}
}

void Arkanoid::GetItems(shared_ptr<ArkanoidPlayer> player)
{
	for (auto item : _items)
	{
		// item과 bar 충돌 했을 때...
		if (item->GetCollider()->IsCollision(dynamic_pointer_cast<RectCollider>(player)))
		{
			// 충돌
			if (item->IsActive())
			{
				item->ActiveSkill();
				item->DeActive();
			}
		}
	}
}






