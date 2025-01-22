#pragma once
class Mage : public Player
{
public:
	Mage(string name, int hp, int atk, int def);
	~Mage();


	virtual void Attack(shared_ptr<Creature> other) override;


private:

};

