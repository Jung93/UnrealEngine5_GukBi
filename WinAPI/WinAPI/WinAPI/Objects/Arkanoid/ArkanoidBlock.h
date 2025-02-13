#pragma once
class ArkanoidBall;

class ArkanoidBlock : public RectCollider
{
public:
	ArkanoidBlock();
	~ArkanoidBlock();

	enum class Type
	{
		NONE = 1,
		BLOCKS,

		TYPE_COUNT
	};


	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetBlockType(ArkanoidBlock::Type type) { _curType = type; }
	ArkanoidBlock::Type GetBlockType() { return _curType; }

	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;


	void DeActive() { isLive = false; };
	bool isLive = true;

private:
	vector<HBRUSH> _brushes;
	ArkanoidBlock::Type _curType = Type::NONE;

};

