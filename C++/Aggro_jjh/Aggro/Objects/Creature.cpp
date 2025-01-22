#include "pch.h"
#include "Creature.h"



Creature::Creature(string name, int hp, int atk, int def)
	: _name(name), _hp(hp), _maxHp(hp), _atk(atk), _def(def), _criticalRate(0.2f), _hitRate(0.8f), _dodgeRate(0.2f)
{
}

Creature::~Creature()
{
}

void Creature::Attack(shared_ptr<Creature> other)
{
	//todo
	// attack에서는 그냥 공격자의 공격력, 명중률만 넘기기. 방어력, 회피율 계산은 takedamage 쪽에서 하기

	
	bool isHit = IsHit();
	bool isCritical = IsCritical();

	int damage = GetDamage(_atk, isCritical, isHit);

	if (dynamic_pointer_cast<Boss>(other))
		other->TakeDamage(damage, shared_from_this());
	else
		other->TakeDamage(damage);
}

void Creature::TakeDamage(int amount)
{
	if (amount <= 0)
		return;

	if (IsDodged())
		return;

	int finalDamage = amount - _def;

	if (finalDamage <= 0)
		return;

	_hp -= finalDamage;

	if(_hp < 0)
		_hp = 0;

}

void Creature::TakeDamage(int amount, shared_ptr<Creature> player)
{

	//todo
	//어그로 시스템

}

bool Creature::IsHit()
{
	float hit = (rand() % 10 + 1) / 10.0f;

	if (_hitRate >= hit)
		return true;
	return false;
}

bool Creature::IsCritical()
{
	float critical = (rand() % 10 + 1) / 10.0f;

	if (_criticalRate <= critical)
		return true;
	return false;
}

int Creature::GetDamage(int atk, bool isCritical, bool isHit)
{
	if (!isHit)
		return 0;

	if (isCritical)
		return atk * 2;

	//int result = atk - targetDef;

	//if (result < 0)
	//	result = 0;

	//return result;
	return atk;
}


bool Creature::IsDead()
{
	return _hp <= 0;
}

bool Creature::ISHalfHp()
{
	float hpRate = _hp / (float)_maxHp;

	if (hpRate <= 0.5f)
		return true;
	return false;
}

bool Creature::IsDodged()
{
	float dodge = (rand() % 10 + 1) / 10.0f;

	if (_dodgeRate >= dodge)
		return true;
	return false;
}

bool Creature::IsDodged(float dodgeRate)
{
	float dodge = (rand() % 10 + 1) / 10.0f;

	if (dodgeRate >= dodge)
		return true;
	return false;
}
