#include "objects.h"
#include "utilities.h"
#include "Weapon.h"
#include <string>
#ifndef ACTOR_H
#define ACTOR_H

class Actor
{
public:
	Actor(int row, int col, int hitPoints, Weapon* weapon, int armorPoints, int strengthPoints, int dexterityPoints);
	~Actor();
	int attack(Actor* opponent);
	std::string getWeaponAction();
	Weapon* getWeapon();
	virtual Object* dropObject();
	//accessors
	int getHitPoints() const;
	int getArmorPoints() const;
	int getStrengthPoints() const;
	int getDexeterityPoints() const;
	int getSleepTime() const;
	int getRow() const;
	int getCol() const;
	//mutators
	void setHitPoint( int newHitPoint);
	void setSleepTime(int newSleepTime);
	void setArmorPoints(int newAP);
	void setStrengthPoints(int newSP);
	void setDexterityPoints(int newDP);
	void setPos(int row, int col);
	int damageDealt() const;
	virtual void changeWeapon(Weapon* newWeapon);
	virtual std::string name();
	virtual char icon();
private:
	int m_row;
	int m_col;
	int m_hit_points;
	Weapon* m_weapon;
	int m_armor_points;
	int m_strength_points;
	int m_dexterity_points;
	int m_sleep_time;
};



#endif