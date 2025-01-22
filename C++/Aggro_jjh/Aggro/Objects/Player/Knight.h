#pragma once
class Knight : public Player
{
public:
	Knight(string name, int hp, int atk, int def);
	~Knight();


	//virtual void Attack(shared_ptr<Creature> other) override;
	virtual void TakeDamage(int amount) override;
	
private:


};

