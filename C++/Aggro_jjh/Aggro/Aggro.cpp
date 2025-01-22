#include "pch.h"


int main()
{

	





	shared_ptr<Creature> boss = make_shared<Boss>("boss", 10000, 50, 10);

	vector<shared_ptr<Creature>> players;

	players.push_back(make_shared<Knight>("knight1", 500, 100, 10));
	players.push_back(make_shared<Knight>("knight2", 500, 100, 10));
	players.push_back(make_shared<Knight>("knight3", 500, 100, 10));
	players.push_back(make_shared<Knight>("knight4", 500, 100, 10));
	players.push_back(make_shared<Knight>("knight5", 500, 100, 10));
	players.push_back(make_shared<Knight>("knight6", 500, 100, 10));
	players.push_back(make_shared<Knight>("knight7", 500, 100, 10));
	players.push_back(make_shared<Knight>("knight8", 500, 100, 10));
	players.push_back(make_shared<Knight>("knight9", 500, 100, 10));
	players.push_back(make_shared<Knight>("knight10", 500, 100, 10));


	while (true)
	{
		if (boss->IsDead())
			break;

		bool AllDead = all_of(players.begin(), players.end(), [](const shared_ptr<Creature>& player)-> bool
			{
				if (player->IsDead())
					return true;
				return false;
			});

		if (AllDead)
			break;


		shared_ptr<Boss> curBoss = dynamic_pointer_cast<Boss>(boss);

		if (curBoss != nullptr)
			curBoss->AttackPlayer();


		for (auto player : players)
		{
			player->Attack(boss);
		}

	}

	


	return 0;
}

