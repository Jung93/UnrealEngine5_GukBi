#pragma once

struct Attacker
{
	weak_ptr<Player> player;
	int totalDamage;

	bool operator>(const Attacker& attacker) const
	{
		if (totalDamage > attacker.totalDamage)
			return true;
		return false;
	}


};

class Boss : public Monster
{
public:
	Boss(string name, int hp, int atk, int def);
	~Boss();


	void AttackPlayer();
	virtual void Attack(shared_ptr<Creature> other) override;
	virtual void TakeDamage(int amount, shared_ptr<Creature> player) override;


private:
	vector<Attacker> _aggroPlayers;


};

