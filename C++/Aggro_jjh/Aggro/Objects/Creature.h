#pragma once


class Creature : public enable_shared_from_this<Creature>
{
public:
	Creature(string name, int hp, int atk, int def);
	~Creature();

	virtual void Attack(shared_ptr<Creature> other);
	virtual void TakeDamage(int amount);
	virtual void TakeDamage(int amount, shared_ptr<Creature> player);


	bool IsHit();
	bool IsCritical();
	bool IsDead();
	bool ISHalfHp();
	bool IsDodged();
	bool IsDodged(float dodgeRate);

	int GetDamage(int atk, bool isCritical, bool isHit);

	void SetHp(int hp) { _hp = hp; };

	const string&	GetName()		{ return _name; }
	const int&		GetHp()			{ return _hp; }
	const int&		GetMaxHp()		{ return _maxHp; }
	const int&		GetAtk()		{ return _atk; }
	const int&		GetDef()		{ return _def; }
	const float&	GetCriRate()	{ return _criticalRate; }
	const float&	GetHitRate()	{ return _hitRate; }
	const float&	GetDodgeRate()	{ return _dodgeRate; }


private:
	string _name;
	int _hp;
	int _maxHp;
	int _atk;
	int _def;
	float _criticalRate;
	float _hitRate;
	float _dodgeRate;
};

