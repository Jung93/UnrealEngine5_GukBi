#pragma once
class Block : public RectCollider
{
public:
	enum class Type
	{
		NONE,
		ABLE,
		BLOCKED,
		PLAYER,
		FOOTPRINT,
		SEARCHED,

		TYPE_COUNT
	};

	Block();
	~Block();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetType(Block::Type type) { _curType = type; }
	Block::Type GetType() { return _curType; }

private:
	//shared_ptr<RectCollider> _rectColider;
	vector<HBRUSH> _brushes;
	Block::Type _curType = Type::NONE;

};

