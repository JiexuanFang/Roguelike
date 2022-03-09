#include <iostream>
#include <string>
#include "Actor.h"
#include "utilities.h"
using namespace std;

Actor::Actor(int row, int col, int hitPoints, Weapon* weapon, int armorPoints, int strengthPoints, int dexterityPoints)
	:m_row(row), m_col(col), m_weapon(weapon), m_hit_points(hitPoints), m_armor_points(armorPoints), m_strength_points(strengthPoints),
	m_dexterity_points(dexterityPoints), m_sleep_time(0)
{
}

Actor::~Actor()
{
	delete m_weapon;
}

int Actor::attack(Actor* opponent)
{
	//calculate the damage dealt, and wether the enemy has been hit
	int attackerPoints = m_dexterity_points + m_weapon->getDexterityBonus();
	int defenderPoints = opponent->getDexeterityPoints() + opponent->getArmorPoints();
	int damage = this->damageDealt();
	if (randInt(1, attackerPoints) > randInt(1, defenderPoints))
	{
		opponent->setHitPoint(opponent->getHitPoints() - damage);
		return damage;
	}
	return 0;
}

string Actor::getWeaponAction()
{
	return m_weapon->getAction();
}

Weapon* Actor::getWeapon()
{
	return m_weapon;
}

int Actor::getHitPoints() const
{
	return m_hit_points;
}

int Actor::getArmorPoints() const
{
	return m_armor_points;
}

int Actor::getStrengthPoints() const
{
	return m_strength_points;
}

int Actor::getDexeterityPoints() const
{
	return m_dexterity_points;
}

int Actor::getSleepTime() const
{
	return m_sleep_time;
}

int Actor::getRow() const
{
	return m_row;
}

int Actor::getCol() const
{
	return m_col;
}
int Actor::damageDealt() const
{
	int damage = randInt(0, m_strength_points + m_weapon->getDamageAmount() - 1);
	return damage;
}
void Actor::setHitPoint( int newHitPoint)
{
	m_hit_points = newHitPoint;
}
void Actor::setSleepTime(int newSleepTime)
{
	m_sleep_time = newSleepTime;
}

void Actor::setArmorPoints(int newAP)
{
	m_armor_points = newAP;
}

void Actor::setStrengthPoints(int newSP)
{
	m_strength_points = newSP;
}

void Actor::setDexterityPoints(int newDP)
{
	m_dexterity_points = newDP;
}

void Actor::setPos(int row, int col)
{
	m_row = row;
	m_col = col;
}

void Actor::changeWeapon(Weapon* newWeapon)
{
	if (newWeapon == nullptr)
	{
		cerr << "weapon changed to nullptr.";
		return;
	}
	m_weapon = newWeapon;
}

char Actor::icon()
{
	return ' ';
}

string Actor::name()
{
	return "";
}

Object* Actor::dropObject()
{
	return nullptr;
}

