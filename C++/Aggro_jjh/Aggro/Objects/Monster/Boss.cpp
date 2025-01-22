#include "pch.h"
#include "Boss.h"

Boss::Boss(string name, int hp, int atk, int def)
	:Monster(name, hp, atk, def)
{
}

Boss::~Boss()
{
}


void Boss::AttackPlayer()
{

	if (_aggroPlayers.size() == 0)
		return;


	vector<Attacker>::iterator iter = remove_if(_aggroPlayers.begin(), _aggroPlayers.end(), [](const Attacker& attacker)->bool
		{
			if (attacker.player.expired() == true)
				return true;
			else
			{
				shared_ptr<Player> p = attacker.player.lock();

				if (p->IsDead() == true)
					return true;
				else
					return false;
			}
		});


	_aggroPlayers.erase(iter, _aggroPlayers.end());

	sort(_aggroPlayers.begin(), _aggroPlayers.end(), greater<Attacker>());


	int range = 4;

	if (_aggroPlayers.size() < range)
		range = _aggroPlayers.size();

	for (int i = 0; i < range; i++)
	{
		Attack(_aggroPlayers[i].player.lock());
	}


}

void Boss::Attack(shared_ptr<Creature> other)
{

	Creature::Attack(other);

}

void Boss::TakeDamage(int amount, shared_ptr<Creature> player)
{
	Creature::TakeDamage(amount);


	vector<Attacker>::iterator iter = find_if(_aggroPlayers.begin(), _aggroPlayers.end(), [player](const Attacker& attacker)->bool 
		{
			if (attacker.player.lock().get() == player.get())
				return true;
			return false;
		});

	if (iter == _aggroPlayers.end())
	{
		Attacker attacker = {dynamic_pointer_cast<Player>(player), amount};
		_aggroPlayers.push_back(attacker);
	}
	else
	{
		iter->totalDamage += amount;
	}
}
