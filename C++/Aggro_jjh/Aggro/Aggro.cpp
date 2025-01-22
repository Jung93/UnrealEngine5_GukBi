#include "pch.h"


int main()
{
	shared_ptr<Creature> boss = make_shared<Boss>("boss", 10000, 50, 30);

	vector<shared_ptr<Creature>> players;

	srand(time(nullptr));

	for (int i = 0; i < 10; i++)
	{
		int randPlayer = rand() % 3;

		switch (randPlayer)
		{
			case 0:
				players.push_back(make_shared<Knight>("Knight" + to_string(i + 1), 700, 100, 20));
				break;
			case 1:
				players.push_back(make_shared<Archer>("Archer" + to_string(i + 1), 500, 150, 10));
				break;
			case 2:
				players.push_back(make_shared<Mage>("Mage" + to_string(i + 1), 300, 200, 5));
				break;
			default:
				break;
		}

	}


	while (true)
	{
		bool AllDead = all_of(players.begin(), players.end(), [](const shared_ptr<Creature>& player)-> bool
			{
				if (player->IsDead())
					return true;
				return false;
			});
		if (AllDead)
		{
			cout << "Boss's Win" << endl;
			break;
		}

		if (boss->IsDead())
		{
			cout << "Player's Win" << endl;
			break;
		}


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

