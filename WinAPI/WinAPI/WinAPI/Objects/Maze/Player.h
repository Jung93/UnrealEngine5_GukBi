#pragma once
class Maze;
class Block;

class Player
{
public:
	//path
	enum Direction
	{
		UP,
		LEFT,
		BOTTOM,
		RIGHT,

		DIR_COUNT = 4

	};

	Vector frontPos[8] =
	{
		{0 , -1},//UP
		{-1, 0},//LEFT
		{0, 1},//BOTTOM
		{1, 0},//RIGHT

		{-1, -1},//UP RIGHT
		{1, -1},//UP RIGHT
		{1, 1},//BOTTOM RIGHT
		{-1, 1},//BOTTOM LEFT

	};

	struct Vertex
	{
		Vertex() {}
		Vertex(Vector pos, int cost) : pos(pos), cost(cost) {}

		bool operator<(const Vertex& v) const
		{
			return cost < v.cost;
		}

		bool operator>(const Vertex& v) const
		{
			return cost > v.cost;
		}

		Vector pos;
		int cost;
	};

	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();
	bool CanGo(Vector pos);

	void BFS(Vector start);
	void DFS(Vector start);
	void Djikstra(Vector start);


private:
	weak_ptr<Maze> _maze;
	Vector _pos = { 1,1 };
	vector<Vector> _path;
	int _pathIndex = 0;
	float _delayTime = 0.0f;



	//Right Hand
	Vector _dir = Vector(0, -1);

	vector<vector<bool>> _discovered;
	vector<vector<Vector>> _parent;
	vector<vector<bool>> _visited;


	vector<vector<int>> _best;

};

