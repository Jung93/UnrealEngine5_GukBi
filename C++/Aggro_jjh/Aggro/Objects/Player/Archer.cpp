#include "pch.h"
#include "Archer.h"

Archer::Archer(string name, int hp, int atk, int def)
	:Player(name, hp, atk, def)
{
}

Archer::~Archer()
{
}



void Archer::TakeDamage(int amount)
{
	if (amount <= 0)
		return;


	if (ISHalfHp())
	{
		float dodgeRate = GetDodgeRate();
		dodgeRate *= 3.0f;

		if (IsDodged(dodgeRate))
			return;
	}
	else
	{
		if (IsDodged())
			return;
	}


	int hp = GetHp();
	int def = GetDef();
	int finalDamage = amount - def;

	if (finalDamage <= 0)
		return;

	hp -= finalDamage;

	if (hp < 0)
		hp = 0;

	SetHp(hp);
}
