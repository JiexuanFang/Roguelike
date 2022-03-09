#include "Actor.h"
#include <string>
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H

class Player : public Actor
{
public:
	Player(int row, int col);
	~Player();
	bool addToInventory(Object* object);
	bool isInventoryFull();
	void displayInventory();
	void removeFromInventory(int index);
	Object* getInventoryObject(int pos);
	int inventorySize();
	virtual char icon();
	virtual std::string name();
private:
	std::vector<Object*> m_inventory;
};



#endif 

