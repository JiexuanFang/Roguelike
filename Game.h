// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include "Player.h"
#include "Actor.h"
#include "Monster.h"
#include "Weapon.h"
#include "Dungeon.h"
#include "Level.h"
// You may add data members and other member functions to this class.

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
    bool isAlive();
private:
    int goblin_smell_distance;
    Player p1;
    Level clv;

};

#endif // GAME_INCLUDED
