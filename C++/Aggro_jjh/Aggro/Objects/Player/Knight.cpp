#include "pch.h"
#include "Knight.h"

Knight::Knight(string name, int hp, int atk, int def)
	:Player(name, hp, atk, def)
{
}

Knight::~Knight()
{
}


void Knight::TakeDamage(int amount)
{
	if (amount <= 0)
		return;

	if (IsDodged())
		return;

	int hp = GetHp();
	int def = GetDef();

	if (ISHalfHp())
		def *= 2;

	int finalDamage = amount - def;

	if (finalDamage <= 0)
		return;

	hp -= finalDamage;

	if (hp < 0)
		hp = 0;

	SetHp(hp);
}
