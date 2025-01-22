#pragma once
class Archer : public Player
{
public:
	Archer(string name, int hp, int atk, int def);
	~Archer();

	virtual void TakeDamage(int amount) override;

private:


};

