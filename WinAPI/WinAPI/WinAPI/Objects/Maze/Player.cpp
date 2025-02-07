#include "framework.h"
#include "Player.h"

#include "Maze.h"
#include "Block.h"

Player::Player(shared_ptr<Maze> maze)
	:_maze(maze)
{
	_maze.lock()->SetBlockType(_pos, Block::Type::PLAYER);

	//RightHand();
	//BFS(_maze.lock()->StartPos());
	//DFS(_maze.lock()->StartPos());
	Djikstra(_maze.lock()->StartPos());

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

		for (int i = 0; i < 8; i++)
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

void Player::DFS(Vector start)
{
	_visited = vector<vector<bool>>(MAX_Y, vector<bool>(MAX_X, false));


	for (int i = 0; i < 4; i++)
	{
		Vector there = start + frontPos[i];

		if (there == start)
			continue;

		if (CanGo(there) == false)
			continue;

		if (_visited[start.y][start.x] == true)
			continue;

		_visited[start.y][start.x] = true;
		_maze.lock()->SetBlockType(there, Block::Type::SEARCHED);

		DFS(there);
	}

	//Vector vertex = start;
	//_path.push_back(vertex);
	//reverse(_path.begin(), _path.end());

}

void Player::Djikstra(Vector start)
{
	_parent = vector<vector<Vector>>(MAX_Y, vector<Vector>(MAX_X, Vector(-1, -1)));
	_best = vector<vector<int>>(MAX_Y, vector<int>(MAX_X, INT_MAX));
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

	_parent[start.y][start.x] = start;
	_best[start.y][start.x] = 0;
	pq.push(Vertex(start, 0));


	while (true)
	{
		if (pq.empty())
			break;

		Vertex hereV = pq.top();
		pq.pop();
		Vector herePos = hereV.pos;

		//예약된 Vertex를 꺼냈는데 더 좋은 best가 있었다
		if (_best[herePos.y][herePos.x] < hereV.cost)
			continue;

		for (int i = 0; i < 8;i++)
		{
			Vector therePos = herePos + frontPos[i];

			if (CanGo(therePos) == false)
				continue;

			//thereCost 찾기
			int thereCost = 0;
			if (i < 4)
				thereCost = hereV.cost + 10;
			else
				thereCost = hereV.cost + 14;

			//전에 찾아놓은  best가 더 좋았다
			if (_best[therePos.y][therePos.x] < thereCost)
				continue;

			//예약
			Vertex thereV(therePos, thereCost);
			pq.push(thereV);
			_parent[therePos.y][therePos.x] = herePos;
			_best[therePos.y][therePos.x] = thereCost;

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
