#include "framework.h"
#include "Player.h"

#include "Maze.h"
#include "Block.h"

Player::Player(shared_ptr<Maze> maze)
	:_maze(maze)
{
	_maze.lock()->SetBlockType(_pos, Block::Type::PLAYER);

	//RightHand();
	BFS(_maze.lock()->StartPos());

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

void Player::BFS(Vector start)
{
	_discovered = vector<vector<bool>>(MAX_Y, vector<bool>(MAX_X, false));
	_parent = vector<vector<Vector>>(MAX_Y, vector<Vector>(MAX_X, Vector(-1, -1)));

	queue<Vector> q;
	q.push(start);
	_discovered[start.y][start.x] = true;
	_parent[start.y][start.x] = start;

	while (true)
	{
		Vector here = q.front();
		q.pop();

		if (here == _maze.lock()->EndPos())
			break;

		for (int i = 0; i < 4; i++)
		{
			Vector there = here + frontPos[i];



			if (there == here)
				continue;

			if (CanGo(there) == false)
				continue;

			if (_discovered[there.y][there.x] == true)
				continue;

			q.push(there);
			_discovered[there.y][there.x] = true;
			_parent[there.y][there.x] = here;
			_maze.lock()->SetBlockType(there, Block::Type::SEARCHED);
		}

	}

	Vector vertex = _maze.lock()->EndPos();
	_path.push_back(vertex);

	while (true)
	{
		if (vertex == start)
			break;

		vertex = _parent[vertex.y][vertex.x];
		_path.push_back(vertex);
	}

	reverse(_path.begin(), _path.end());

}
