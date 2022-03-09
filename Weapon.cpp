#include<iostream>
#include<string>
#include"Weapon.h"

using namespace std;
#include "Actor.h"


Weapon::Weapon(string type, string action, int dexBonus, int damage):
	Object(type), m_action_str(action), m_dexterity_bonus(dexBonus), m_damage_amount(damage)
{
}

Weapon::Weapon(string type,string action, int dexBonus, int damage,int row, int col)
	: Object(type, row, col), m_action_str(action), m_dexterity_bonus(dexBonus), m_damage_amount(damage)
{

}

Weapon::Weapon(const Weapon& other)
	: Object(other.getName(), other.getRow(), other.getCol()), m_action_str(other.getAction()), m_dexterity_bonus(other.getDexterityBonus()), m_damage_amount(other.getDamageAmount())
{

}


string Weapon::getWeaponType() const
{
	return getName();
}

std::string Weapon::getAction() const
{
	return m_action_str;
}

int Weapon::getDexterityBonus() const
{
	return m_dexterity_bonus;
}

int Weapon::getDamageAmount() const
{
	return m_damage_amount;
}

Mace::Mace()
	:Weapon("Mace",  "swings mace at", 0, 2)
{
}



ShortSword::ShortSword()
	: Weapon("ShortSword",  "slashes short sword at ", 0, 2)
{
}

LongSword::LongSword()
	:Weapon("LongSword", "swings long sword at ", 2, 4)
{
}

MagicAxe::MagicAxe()
	:Weapon("MagicAxe",  "chops magic axe at ", 5, 5)
{
}

MagicFang::MagicFang()
	:Weapon("MagicFangsOfSleep", "strikes magic fangs at ", 3, 2)
{

}

int MagicFang::PutToSleep(Actor* a)
{
	//simulates a 1 in 5 chance for the victim to be put to sleep
	int temp = randInt(1, 5);
	if (temp == 1)
	{
		int sleepTime = randInt(2, 6);
		if (sleepTime > a->getSleepTime())
		{
			a->setSleepTime(sleepTime);
		}
		return sleepTime;
	}
	else
	{
		return 0;
	}
}
