#include "pch.h"
#include "Player.h"

Player::Player(string name, int hp, int atk, int def)
	: Creature(name, hp, atk, def)
{
}

Player::~Player()
{
}
