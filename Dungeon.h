#ifndef DUNGEON_H
#define DUNGEON_H
#include "Level.h"
#include "utilities.h"
class Actor;
class Player;

class Dungeon
{
public:
	Dungeon();
	~Dungeon();
	//returns the level the player is in
	int myLevel();
private:
	int m_level;
	Level lv1;
	Level lv2;
	Level lv3;
	Level Lv4;
	Player* m_player;
};

#endif