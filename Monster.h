#pragma once
#ifndef MONSTER_H
#define MONSTER_H
#include "Actor.h"
#include "Scroll.h"
#include<string>

class Bogeymen : public Actor
{
public:
	Bogeymen(int row, int col);
	~Bogeymen();
	//returns true if the player can be smelled by Bogeyman.
	bool smellsPlayer(int row, int col);
	//return magic axe or nullptr.
	virtual Object* dropObject();
	//return the direction Bogeyman will move, regardless of wether there is obstacles in front of him.
	char moveDirection(int row, int col);
	virtual char icon();
	virtual std::string name();
};

class Snakewomen : public Actor
{
public:
	Snakewomen(int row, int col);
	~Snakewomen();
	//returns true if the player can be smelled by Bogeyman.
	bool smellsPlayer(int row, int col);
	//drops fangs at 1 in 3 chance.
	virtual Object* dropObject();
	//return the direction Bogeyman will move, regardless of wether there is obstacles in front of him.
	char moveDirection(int row, int col);
	virtual char icon();
	virtual std::string name();
};

class Dragon : public Actor
{
public:
	Dragon(int row, int col);
	~Dragon();
	virtual Object* dropObject();
	void gainHealth();
	virtual char icon();
	virtual std::string name();
};

class Goblin : public Actor
{
public:
	Goblin(int row, int col);
	~Goblin();
	//drops either axe or fangs at 1 in 3 chance.
	virtual Object* dropObject();
	//goblin's smell finction is lovated in Level.cpp since it needs access to the dungeon.
	virtual char icon();
	virtual std::string name();
};

#endif // !MONSTER_H
