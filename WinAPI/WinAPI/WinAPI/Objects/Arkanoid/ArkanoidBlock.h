#pragma once
class ArkanoidBall;
class ArkanoidItem;

class ArkanoidBlock : public RectCollider
{
public:
	ArkanoidBlock();
	~ArkanoidBlock();

	enum class Type
	{
		NONE = 1,
		BLOCKS,
		ITEM_BLOCKS,

		TYPE_COUNT
	};


	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetBlockType(ArkanoidBlock::Type type) { _curType = type; }
	void SetItem(shared_ptr<ArkanoidItem> item);
	void DeActive() { isLive = false; };

	ArkanoidBlock::Type GetBlockType() { return _curType; }
	shared_ptr<ArkanoidItem> GetItem() { return _item.lock(); }


	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;


	bool isLive = true;

private:
	vector<HBRUSH> _brushes;
	ArkanoidBlock::Type _curType = Type::NONE;
	weak_ptr<ArkanoidItem> _item;
};

