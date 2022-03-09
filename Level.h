#pragma once
#include <array>
#include <vector>
#ifndef LEVEL_H
#define LEVEL_H
#include "objects.h"
#include "Player.h"
#include "Scroll.h"
#include "Monster.h"
// All coordinates are written in array form, eg. (0,0) is top left, (17,69) is top right.

class Level
{
public:
	// sets an 18 * 75 board with '#' in every cell.
	Level(Player* p, int level, int smelldistance);
	~Level();
	//displays the board.
	void display() const;
	// draws an empty rectangle on the board, with left top at sr, sc, and right bottom at er, ec.
	void drawRoom( int sr, int sc, int er, int ec);
	//set the value in the cell.
	void setCell( char value, int row, int col);
	//return the alue in the cell.
	char getCellStatus(int row, int col) const;
	//returns true if cell is empty
	bool isCellEmpty(int row, int col) const;
	//sets player on a random empty cell.
	void initPlayer();
	//moves player if the next cell is empty, if there is a monster in the next cell, attack the monster.
	std::string movePlayer(char direction);
	//change player Weapon
	void changePlayerWeapon(Weapon* newWeapon);
	//use scroll
	std::string useScroll(Scroll* scroll);
	std::string useInventory();
	//add object to map
	void addObject(Object* newObject);
	//sets 2-3 objects to the map
	void initObjects();
	//picks up object if there is one, if backpack if full print "Your knapsack is full; you can't pick that up."
	std::string pickUpObject();
	//adds a random monster into an empty cell.
	void addMonster(int numOfMonsters);
	//makes actor a1 attacks actor a2.
	std::string attack(Actor* a1, Actor* a2);
	// returns true if goblin can smell player. goblin's position should be er, ec, player should be sr, sc, nr. nc is the next step the goblin should travel, 
	// which is the position o fthe player a step before he reaches the goblin.
	bool goblinSmell(int sr, int sc, int er, int ec, int &min, int count, int &nr, int &nc);
	//move all monsters
	std::string moveAllMonsters();
	//move one monster in a direction
	std::string moveMonster(Actor* monster, char direction);
	//refresh the maze, since each goblinsmel will alter the maze.
	void refreshMaze();
	//draw 3 - 6 random rooms in the board.
	void initRooms();
	//add golden idol
	void addIdol();
	void addStair();
	//update the current level to the next level.
	void newLevel();
	//update objects on board.
	void updateObjects();
	//returns currentLavel.
	int getCurrentLevel();
private:
	char m_board[MAXROW][MAXCOL];
	Player* m_player;
	std::vector<Actor*> m_monsters;
	std::vector<Object*> m_objects;
	//maze for goblin smell function, with all the walls set as '#', and the empty cells initialized as ' '.
	char maze[MAXROW][MAXCOL];
	int currentLevel;
	int goblinSmellDistance;
	Stair* m_stair;
};
#endif // !LEVEL_H
