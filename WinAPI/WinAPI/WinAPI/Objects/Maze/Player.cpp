#include "framework.h"
#include "Player.h"

#include "Maze.h"
#include "Block.h"

Player::Player(shared_ptr<Maze> maze)
	:_maze(maze)
{
	_maze.lock()->SetBlockType(_pos, Block::Type::PLAYER);

	RightHand();
}

Player::~Player()
{
}

void Player::Update()
{
	if (_pathIndex >= _path.size())
		return;

	_delayTime += 0.5f;
	if (_delayTime > 1.0f)
	{
		_delayTime = 0.0f;
		_pos = _path[_pathIndex];


		if (_pathIndex > 0)
		{
			_maze.lock()->SetBlockType(_path[_pathIndex - 1], Block::Type::FOOTPRINT);
		}
		_maze.lock()->SetBlockType(_pos, Block::Type::PLAYER);

		_pathIndex++;
	}




}

void Player::RightHand()
{
	shared_ptr<Maze> maze = _maze.lock();

	Vector pos = maze->StartPos();
	Vector endPos = maze->EndPos();

	int curDir = Direction::UP;


	while (true)
	{
		if (pos == endPos)
			break;

		int newDir = (curDir - 1 + DIR_COUNT) % DIR_COUNT;
		Vector oldVector = pos + frontPos[curDir];
		Vector newVector = pos + frontPos[newDir];
		


		//
		if (CanGo(newVector))
		{
			curDir = newDir;
			pos = newVector;
			_path.push_back(pos);
		}
		else if (CanGo(oldVector))
		{
			pos = oldVector;
			_path.push_back(pos);

		}
		else 
		{
			curDir = (curDir + 1 + DIR_COUNT) % DIR_COUNT;
		}
	}

	stack<Vector> s;
	//사이클 처리
	for (int i = 0; i < _path.size() - 1;i++)
	{
		_maze.lock()->SetBlockType(_path[i], Block::Type::SEARCHED);

		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
		{
			s.push(_path[i]);
		}
	}

	_path.clear();

	while (true)
	{
		if (s.empty())
			break;
		Vector top = s.top();
		_path.push_back(top);
		s.pop();
	}

	reverse(_path.begin(), _path.end());

}

bool Player::CanGo(Vector pos)
{
	return _maze.lock()->GetBlockType(pos) == Block::Type::ABLE;
}
