#pragma once
#include"objects.h"
#include<string>

#ifndef WEAPON_H
#define WEAPON_H

class Actor;


class Weapon: public Object
{
public:
	Weapon(std::string type, std::string action, int dexBonus, int damage);
	Weapon(std::string type, std::string action, int dexBonus, int damage, int row, int col);
	Weapon(const Weapon& other);
	std::string getWeaponType() const;
	std::string getAction() const;
	int getDexterityBonus() const;
	int getDamageAmount() const;
private:
	std::string m_action_str;
	int m_dexterity_bonus;
	int m_damage_amount;
};

class Mace: public Weapon
{
public:
	Mace();
};

class ShortSword : public Weapon
{
public:
	ShortSword();
};

class LongSword : public Weapon
{
public:
	LongSword();
};

class MagicAxe : public Weapon
{
public:
	MagicAxe();
};

class MagicFang : public Weapon
{
public:
	MagicFang();
	int PutToSleep(Actor* a);
};
#endif // !WEAAPON_H
