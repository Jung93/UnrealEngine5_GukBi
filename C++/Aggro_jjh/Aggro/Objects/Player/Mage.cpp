#include "pch.h"
#include "Mage.h"

Mage::Mage(string name, int hp, int atk, int def)
	:Player(name, hp, atk, def)
{
}

Mage::~Mage()
{
}

void Mage::Attack(shared_ptr<Creature> other)
{
	bool isHit = IsHit();
	bool isCritical = IsCritical();

	int atk = GetAtk();

	if (ISHalfHp())
		atk *= 2;

	int damage = GetDamage(atk, isCritical, isHit);

	if (dynamic_pointer_cast<Boss>(other))
		other->TakeDamage(damage, shared_from_this());
	else
		other->TakeDamage(damage);

}
