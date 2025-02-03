#pragma once
class ArkanoidBlock : public RectCollider
{
public:
	ArkanoidBlock();
	~ArkanoidBlock();


	enum class Type
	{
		NONE,
		BAR,
		BLOCKS,

		TYPE_COUNT
	};

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetBlockType(ArkanoidBlock::Type type) { _curType = type; }
	ArkanoidBlock::Type GetBlockType() { return _curType; }

	void Move();


private:
	vector<HBRUSH> _brushes;
	ArkanoidBlock::Type _curType = Type::NONE;
	float _speed = 5.0f;
};

