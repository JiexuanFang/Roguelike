#include "Player.h"
#include <iostream>

using namespace std;



Player::Player(int row, int col)
	:Actor(row, col, 20, new ShortSword, 2,2,2)
{
	m_inventory.push_back(new ShortSword);
}

Player::~Player()
{
}


bool Player::isInventoryFull()
{
	if (m_inventory.size() > 26)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Player::addToInventory(Object* object)
{
	if (object == nullptr)
	{
		return false;
	}
	if (isInventoryFull())
	{
		return false;
	}
	m_inventory.push_back(object);
	return true;
}

void Player::displayInventory()
{
	//displays the inventory
	cout << "Inventory:" << endl;
	char index = 'a';
	for (size_t pos = 0; pos < m_inventory.size(); pos++)
	{
		cout << index << ". " << m_inventory[pos]->getName() << endl;
		index++;
	}
}

Object* Player::getInventoryObject(int pos)
{
	return m_inventory[pos];
}

int Player::inventorySize()
{
	size_t temp = m_inventory.size();
	int size = (int)(temp);
	return size;
}

char Player::icon()
{
	return '@';
}

string Player::name()
{
	return "You ";
}

void Player::removeFromInventory(int index)
{
	//create iterator pointing to the taget object and delete it.
	vector<Object*>::iterator temp = m_inventory.begin() + index;
	m_inventory.erase(temp);
}