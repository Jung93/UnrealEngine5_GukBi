#include "framework.h"
#include "Maze.h"

#include "Block.h"
Maze::Maze()
{
	Vector offset = Vector(300, 200);

	_blocks.resize(MAX_Y);

	for (int y = 0; y < MAX_Y; y++)
	{
		_blocks[y].reserve(MAX_X);
		for (int x = 0; x < MAX_X; x++)
		{
			shared_ptr<Block> block = make_shared<Block>();
			Vector pos;
			pos.x = x * 15;
			pos.y = y * 15;
			block->SetCenter(pos + offset);
			block->SetType(Block::Type::BLOCKED);

			_blocks[y].push_back(block);
		}
	}

	CreateMaze();
}

Maze::~Maze()
{
}

void Maze::Update()
{
	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{
			block->Update();
		}
	}

}

void Maze::Render(HDC hdc)
{
	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{
			block->Render(hdc);
		}
	}
}

void Maze::CreateMaze()
{
	for (int y = 0; y < MAX_Y;y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blocks[y][x]->SetType(Block::Type::BLOCKED);
			}
			else
			{
				_blocks[y][x]->SetType(Block::Type::ABLE);
			}
		}
	}


	for (int y = 0; y < MAX_Y;y++)
	{
		for (int x = 0; x < MAX_X;x++)
		{
			if (x == 1 && y == 1)
			{
				_blocks[y][x]->SetType(Block::Type::ABLE);
			}

			if (x == MAX_X - 2 && y == MAX_Y - 2)
			{
				_blocks[y][x]->SetType(Block::Type::ABLE);
				continue;
			}
			if (x % 2 == 0 || y % 2 == 0)
			{
				continue;
			}

			if (x == MAX_X - 2)
			{
				_blocks[y + 1][x]->SetType(Block::Type::ABLE);
				continue;
			}

			if (y == MAX_Y - 2)
			{
				_blocks[y][x + 1]->SetType(Block::Type::ABLE);
				continue;
			}

			int randNum = rand() % 2;
			if (randNum == 0)
				_blocks[y + 1][x]->SetType(Block::Type::ABLE);
			else
				_blocks[y][x + 1]->SetType(Block::Type::ABLE);
		}
	}
}
