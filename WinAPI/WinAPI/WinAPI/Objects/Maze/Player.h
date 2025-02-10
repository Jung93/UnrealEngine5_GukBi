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

	struct Vertex_Djikstra
	{
		Vertex_Djikstra() {}
		Vertex_Djikstra(Vector pos, int cost) : pos(pos), cost(cost) {}

		bool operator<(const Vertex_Djikstra& v) const
		{
			return cost < v.cost;
		}

		bool operator>(const Vertex_Djikstra& v) const
		{
			return cost > v.cost;
		}

		Vector pos;
		int cost;
	};

	struct Vertex
	{
		Vertex() {}
		Vertex(Vector pos, int g, int h) : pos(pos), g(g), h(h), f(g+h) {}

		bool operator<(const Vertex& v) const
		{
			return f < v.f;
		}

		bool operator>(const Vertex& v) const
		{
			return f > v.f;
		}

		Vector pos;
		int g;
		int h;
		int f;// g + h

	};


	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();
	bool CanGo(Vector pos);

	void BFS(Vector start);
	void DFS(Vector start);
	void Djikstra(Vector start);
	void AStar(Vector start, Vector end);


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

