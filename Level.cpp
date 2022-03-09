#include "Level.h"
#include <iostream>


using namespace std;

Level::Level(Player* p, int level, int smelldistance)
	:currentLevel(level), goblinSmellDistance(smelldistance)
{
	m_player = p;
	for (int pos1 = 0; pos1 < MAXROW; pos1++)
	{
		for (int pos2 = 0; pos2 < MAXCOL; pos2++)
		{
			m_board[pos1][pos2] = '#';
			maze[pos1][pos2] = '#';
		}
	}

	initRooms();
	refreshMaze();
	initPlayer();
	initObjects();
	addMonster(level);
	if (level < 4)
	{
		addStair();
	}
	if (level == 4)
	{
		addIdol();
	}
}

Level::~Level()
{
	for (vector<Object*>::iterator pos = m_objects.begin(); pos != m_objects.end(); pos++)
	{
		pos = m_objects.erase(pos);
	}
	for (vector<Actor*>::iterator pos = m_monsters.begin(); pos != m_monsters.end(); pos++)
	{
		pos = m_monsters.erase(pos);
	}
}

void Level::display() const
{
	for (int pos1 = 0; pos1 < MAXROW; pos1++)
	{
		for (int pos2 = 0; pos2 < MAXCOL; pos2++)
		{
			cout << m_board[pos1][pos2];
		}
		cout << endl;
	}
	cout << endl;
}


//draw the room via a double for loop.
void Level::drawRoom(int sr, int sc, int er, int ec)
{
	for (int pos1 = sr; pos1 <= er; pos1++)
	{
		for (int pos2 = sc; pos2 <= ec; pos2++)
		{
			m_board[pos1][pos2] = ' ';
		}
	}
}

void  Level::setCell(char value, int row, int col)
{
	m_board[row][col] = value;
}

char Level::getCellStatus(int row, int col) const
{
	return m_board[row][col];
}

bool Level::isCellEmpty(int row, int col) const
{
	bool isEmpty = false;
	if (m_board[row][col] == ' ')
	{
		isEmpty = true;
	}
	return isEmpty;
}
//initializes the player's position without changing his inventory.
void Level::initPlayer()
{
	int row = randInt(1,16);
	int col = randInt(1,68);
	while (!isCellEmpty(row, col))
	{
		row = randInt(1,16);
		col = randInt(1, 68);
	}
	m_player->setPos(row, col);
	m_board[row][col] = '@';
}

string Level::movePlayer(char direction)
{
	string result = "";
	int row = m_player->getRow();
	int col = m_player->getCol();
	switch (direction)
	{
	case ARROW_LEFT:
	{
		char nextCell = getCellStatus(row, col - 1);
		//if next cell is golden idol, return "congratulations, you won!" and set m_player's hitpoint to -1, thus ending the game
		if (nextCell == '&')
		{
			result = "Congratulations, you won!";
			m_player->setHitPoint(-1);
		}
		//if the next cell is empty or holds scroll or weapon, move to next cell
		if (nextCell == ' ' || nextCell == ')' || nextCell == '?' || nextCell == '>')
		{
			m_player->setPos(row, col - 1);
			m_board[row][col] = ' ';
			m_board[row][col - 1] = '@';
		}
		//if the next cell holds a monster, attack it.
		if (nextCell == 'B' || nextCell == 'S' || nextCell == 'D' || nextCell == 'G')
		{
			//use for loop to search for the monster in that position.
			for (vector<Actor*>::iterator pos = m_monsters.begin(); pos != m_monsters.end(); pos++)
			{
				Actor* monster = *pos;
				if (monster->getRow() == row && monster->getCol() == col - 1)
				{
					result = attack(m_player, monster);
					//if the monster is dead, erase monster from m_board and m_monsters, and 
					//drops weapon at each monster's item drop rate.
					if (monster->getHitPoints() <= 0)
					{						
						Object* droppedObject = monster->dropObject();
						//if the monster did not drop any object, set the cell to empty.
						if (droppedObject == nullptr)
						{
							m_board[row][col - 1] = ' ';
						}
						//otherwise drop the item on the board and update the relevant information.
						else
						{
							m_objects.push_back(droppedObject);
							Scroll* newScroll = dynamic_cast<Scroll*>(droppedObject);
							Weapon* newWeapon = dynamic_cast<Weapon*>(droppedObject);
							if (newScroll != nullptr)
								m_board[droppedObject->getRow()][droppedObject->getCol()] = '?';
							if (newWeapon != nullptr)
								m_board[droppedObject->getRow()][droppedObject->getCol()] = ')';
						}
						m_monsters.erase(pos);
					}
					break;
				}
			}
		}
		break;
	}
	case ARROW_RIGHT:
	{
		char nextCell = getCellStatus(row, col + 1);
		//if next cell is golden idol, return "congratulations, you won!" and set m_player's hitpoint to -1, thus ending the game
		if (nextCell == '&')
		{
			result = "Congratulations, you won!";
			m_player->setHitPoint(-1);
		}
		//if the next cell is empty or holds scroll or weapon, move to next cell
		if (nextCell == ' ' || nextCell == ')' || nextCell == '?' || nextCell == '>')
		{
			m_player->setPos(row, col + 1);
			m_board[row][col] = ' ';
			m_board[row][col + 1] = '@';
		}
		//if the next cell holds a monster, attack it.
		if (nextCell == 'B' || nextCell == 'S' || nextCell == 'D' || nextCell == 'G')
		{
			//use for loop to search for the monster in that position.
			for (vector<Actor*>::iterator pos = m_monsters.begin(); pos != m_monsters.end(); pos++)
			{
				Actor* monster = *pos;
				if (monster->getRow() == row && monster->getCol() == col + 1)
				{
					result = attack(m_player, monster);
					if (monster->getHitPoints() <= 0)
					{
						Object* droppedObject = monster->dropObject();
						if (droppedObject == nullptr)
						{
							m_board[row][col + 1] = ' ';
						}
						else
						{
							m_objects.push_back(droppedObject);
							Scroll* newScroll = dynamic_cast<Scroll*>(droppedObject);
							Weapon* newWeapon = dynamic_cast<Weapon*>(droppedObject);
							if (newScroll != nullptr)
								m_board[droppedObject->getRow()][droppedObject->getCol()] = '?';
							if (newWeapon != nullptr)
								m_board[droppedObject->getRow()][droppedObject->getCol()] = ')';
						}
						m_monsters.erase(pos);
					}
					break;
				}
			}
		}
		break;
	}
	case ARROW_UP:
	{char nextCell = getCellStatus(row - 1, col);
	//if next cell is golden idol, return "congratulations, you won!" and set m_player's hitpoint to -1, thus ending the game
	if (nextCell == '&')
	{
		result = "Congratulations, you won!";
		m_player->setHitPoint(-1);
	}
	//if the next cell is empty or holds scroll or weapon, move to next cell
	if (nextCell == ' ' || nextCell == ')' || nextCell == '?' || nextCell == '>')
	{
		m_player->setPos(row - 1, col);
		m_board[row][col] = ' ';
		m_board[row - 1][col] = '@';
	}
	//if the next cell holds a monster, attack it.
	if (nextCell == 'B' || nextCell == 'S' || nextCell == 'D' || nextCell == 'G')
	{
		//use for loop to search for the monster in that position.
		for (vector<Actor*>::iterator pos = m_monsters.begin(); pos != m_monsters.end(); pos++)
		{
			Actor* monster = *pos;
			if (monster->getRow() == row - 1 && monster->getCol() == col)
			{
				result = attack(m_player, monster);
				if (monster->getHitPoints() <= 0)
				{
					Object* droppedObject = monster->dropObject();
					if (droppedObject == nullptr)
					{
						m_board[row - 1][col] = ' ';
					}
					else
					{
						m_objects.push_back(droppedObject);
						Scroll* newScroll = dynamic_cast<Scroll*>(droppedObject);
						Weapon* newWeapon = dynamic_cast<Weapon*>(droppedObject);
						if (newScroll != nullptr)
							m_board[droppedObject->getRow()][droppedObject->getCol()] = '?';
						if (newWeapon != nullptr)
							m_board[droppedObject->getRow()][droppedObject->getCol()] = ')';
					}
					m_monsters.erase(pos);
				}
				break;
			}
		}
	}
	break;
	}
	case ARROW_DOWN:
	{char nextCell = getCellStatus(row + 1, col);
	//if next cell is golden idol, return "congratulations, you won!" and set m_player's hitpoint to -1, thus ending the game
	if (nextCell == '&')
	{
		result = "Congratulations, you won!";
		m_player->setHitPoint(-1);
	}
	//if the next cell is empty or holds scroll or weapon, move to next cell
	if (nextCell == ' ' || nextCell == ')' || nextCell == '?' || nextCell == '>')
	{
		m_player->setPos(row + 1, col);
		m_board[row][col] = ' ';
		m_board[row + 1][col] = '@';
	}
	//if the next cell holds a monster, attack it.
	if (nextCell == 'B' || nextCell == 'S' || nextCell == 'D' || nextCell == 'G')
	{
		//use for loop to search for the monster in that position.
		for (vector<Actor*>::iterator pos = m_monsters.begin(); pos != m_monsters.end(); pos++)
		{
			Actor* monster = *pos;
			if (monster->getRow() == row + 1 && monster->getCol() == col)
			{
				result = attack(m_player, monster);
				if (monster->getHitPoints() <= 0)
				{
					Object* droppedObject = monster->dropObject();
					if (droppedObject == nullptr)
					{
						m_board[row + 1][col] = ' ';
					}
					else
					{
						m_objects.push_back(droppedObject);
						Scroll* newScroll = dynamic_cast<Scroll*>(droppedObject);
						Weapon* newWeapon = dynamic_cast<Weapon*>(droppedObject);
						if (newScroll != nullptr)
							m_board[droppedObject->getRow()][droppedObject->getCol()] = '?';
						if (newWeapon != nullptr)
							m_board[droppedObject->getRow()][droppedObject->getCol()] = ')';
					}
					m_monsters.erase(pos);
				}
				break;
			}
		}
	}
	break;
	}
	default:
		break;
	}
	return result;
}

void Level::changePlayerWeapon(Weapon* newWeapon)
{
	m_player->changeWeapon(newWeapon);
}

string Level::useScroll(Scroll* scroll)
{
	//if scroll does not exist, cerr.
	if (scroll == nullptr)
	{
		cerr << "scroll if a nullptr";
		return "";
	}
	//if is scroll of teleportation, teleport to random empty cell.
	if (scroll->getName() == "scroll of teleportation")
	{
		int row = randInt(17);
		int col = randInt(69);
		while (!isCellEmpty(row, col))
		{
			int row = randInt(17);
			int col = randInt(69);
		}
		m_board[m_player->getRow()][m_player->getCol()] = ' ';
		m_player->setPos(row, col);
		m_board[row][col] = '@';
		return "You feel your body wrenched in space and time.";
	}
	//if it is scroll of enhance armor, increase armor points.
	if (scroll->getName() == "scroll of enhance armor")
	{
		int improveAmount = randInt(1, 3);
		m_player->setArmorPoints(m_player->getArmorPoints() + improveAmount);
		return "Your armor glows blue.";
	}
	//if is strength scroll, increase streaght points
	if (scroll->getName() == "scroll of strength")
	{
		int improveAmount = randInt(1, 3);
		m_player->setStrengthPoints(m_player->getStrengthPoints() + improveAmount);
		return "Your muscles bulge.";
	}
	//if is scroll of enhace health, increase health points
	if (scroll->getName() == "scroll of enhance health")
	{
		int improveAmount = randInt(3, 8);
		m_player->setHitPoint(m_player->getHitPoints() + improveAmount);
		return "You feel your heart beating stronger.";
	}
	//if is scroll of dexterity, increase dexterity points.
	if (scroll->getName() == "scroll of enhance dexterity")
	{
		m_player->setDexterityPoints(m_player->getDexeterityPoints() + 1);
		return "You feel like less of a klutz.";
	}
	//if it is none of the above, return empty string( so that all control paths return a string, even though this one should never be called.)
	return "";
}

string  Level::useInventory()
{
	//create empty string and display inventory
	string result = "";
	clearScreen();
	m_player->displayInventory();
	char command = getCharacter();
	switch (command)
	{
	case 'w':
	case 'W':
	{
		//convert index from int to char.
		char temp = getCharacter();
		int index = (int)(temp - 97);
		if (index >= m_player->inventorySize())
		{
			break;
		}
		//if it is a weapon, wield it, otherwise print you can't wield the item.
		Weapon* chosenWeapon = dynamic_cast<Weapon*>(m_player->getInventoryObject(index));
		if (chosenWeapon == nullptr)
		{
			result = "You can't weild " + m_player->getInventoryObject(index)->getName();
			break;
		}
		else 
		{
			changePlayerWeapon(chosenWeapon);
			result =  "You are wielding " + m_player->getInventoryObject(index)->getName();
			break;
		}
	}
	case'r':
	case'R':
	{
		//if it is a scroll, use it and erase if from inventory.
		char temp = getCharacter();
		int index = (int)(temp - 97);
		if (index >= m_player->inventorySize())
		{
			break;
		}
		//if the object is not a scroll, print "you can not use ..."
		Scroll* chosenScroll = dynamic_cast<Scroll*>(m_player->getInventoryObject(index));
		if (chosenScroll == nullptr)
		{
			result = "You can't use the scroll called " + m_player->getInventoryObject(index)->getName();
			break;
		}
		//else use the scroll and remove it from inventory.
		else 
		{
			result = useScroll(chosenScroll);
			m_player->removeFromInventory(index);
			break;
		}
	}
	default:break;
	}
	return result;
}

void Level::addObject(Object* newObject)
{
	m_objects.push_back(newObject);
	Scroll* newScroll = dynamic_cast<Scroll*>(newObject);
	Weapon* newWeapon = dynamic_cast<Weapon*>(newObject);
	if (newScroll != nullptr)
	{
		m_board[newObject->getRow()][newObject->getCol()] = '?';
		return;
	}
	if (newWeapon != nullptr)
	{
		m_board[newObject->getRow()][newObject->getCol()] = ')';
		return;
	}
}

void Level::initObjects()
{
	int numObjects = randInt(2, 3);
	for (int temp = 0; temp < numObjects; temp++)
	{
		int row = randInt(1,16);
		int col = randInt(1,68);
		while (!isCellEmpty(row, col))
		{
			row = randInt(1,16);
			col = randInt(1,68);
		}
		int type = randInt(6);
		switch (type)
		{
		case 0:
		{
			Object* newObject = new ShortSword;
			newObject->setPos(row, col);
			addObject(newObject);
			break;
		}
		case 1:
		{
			Object* newObject = new Mace;
			newObject->setPos(row, col);
			addObject(newObject);
			break;
		}
		case 2:
		{
			Object* newObject = new LongSword;
			newObject->setPos(row, col);
			addObject(newObject);
			break;
		}
		case 3:
		{
			Object* newObject = new enhanceArmorScroll;
			newObject->setPos(row, col);
			addObject(newObject);
			break;
		}
		case 4:
		{
			Object* newObject = new enhanceHealthScroll;
			newObject->setPos(row, col);
			addObject(newObject);
			break;
		}
		case 5:
		{
			Object* newObject = new StrengthScroll;
			newObject->setPos(row, col);
			addObject(newObject);
			break;
		}
		case 6:
		{
			Object* newObject = new enhanceDexterityScroll;
			newObject->setPos(row, col);
			addObject(newObject);
			break;
		}
		}
	}
} 
// to be debugged
string Level::pickUpObject()
{
	string result = "";
	if (m_player->isInventoryFull())
	{
		result = result + "Your knapsack is full; you can't pick that up.";
		return result;
	}
	else
	{
		int size = (int)(m_objects.size());
		for (int pos = 0; pos < size; pos++)
		{
			if (m_objects[pos]->getRow() == m_player->getRow() && m_objects[pos]->getCol() == m_player->getCol())
			{
				Scroll* isScroll = dynamic_cast<Scroll*>(m_objects[pos]);
				Weapon* isWeapon = dynamic_cast<Weapon*>(m_objects[pos]);
				if (isScroll != nullptr)
				{
					result = result + "You pick up a scroll called " + m_objects[pos]->getName();
				}
				if (isWeapon != nullptr)
				{
					result = result + "You pick up " + m_objects[pos]->getName();
				}
				m_objects[pos]->setPos(-1, -1);
				m_player->addToInventory(m_objects[pos]);
				vector<Object*>::iterator temp = m_objects.begin() + pos;
				temp = m_objects.erase(temp);
				break;
			}
		}
	}
	return result;
}
 
void Level::addMonster(int Level)
{
	int numOfMonsters = randInt(2, 5 * (Level + 1) + 1);
	for (int pos = 0; pos < numOfMonsters; pos++)
	{
		int type;
		if (Level < 3)
		{
			type = randInt(1, 3);
		}
		else
		{
			type = randInt(1, 4);
		}
		int row = randInt(1, 16);
		int col = randInt(1, 68);
		while (!isCellEmpty(row, col))
		{
			row = randInt(1, 16);
			col = randInt(1, 68);
		}
		switch (type)
		{
		case 1:
		{
			m_monsters.push_back(new Bogeymen(row, col));
			m_board[row][col] = 'B';
			break;
		}
		case 2:
		{
			m_monsters.push_back(new Snakewomen(row, col));
			m_board[row][col] = 'S';
			break;
		}

		case 3:
		{
			m_monsters.push_back(new Goblin(row, col));
			m_board[row][col] = 'G';
			break;
		}
		case 4:
		{
			m_monsters.push_back(new Dragon(row, col));
			m_board[row][col] = 'D';
			break;
		}
		}
	}
}

string Level::attack(Actor* a1, Actor* a2)
{
	string result = "";
	if (a1->getSleepTime() == 0)
	{
		int damage = m_player->attack(a2);
		result = a1->name() + a1->getWeaponAction() + a2->name() + ",";
		if (damage == 0)
		{
			result = result + " and misses.\n";
		}
		else if (a2->getHitPoints() <= 0)
		{
			result = result +" dealing a final blow\n";
		}
		else
		{
			result =   result + " and hits.\n";
		}
		if (a1->getWeaponAction() == "strikes magic fangs at " && a2->getHitPoints() > 0 && damage != 0)
		{
			int temp = randInt(1, 5);
			if (temp == 1)
			{
				int sleepTime = randInt(2, 6);
				if (sleepTime > a2->getSleepTime())
				{
					a2->setSleepTime(sleepTime);
				}
				result = result + " and hits, putting " +  a2->name() + " to sleep.\n";
			}
		}
	}
	else
	{
		a1->setSleepTime(a1->getSleepTime() - 1);
	}
	return result;
}

bool Level::goblinSmell(int sr, int sc, int er, int ec, int& minimum, int count, int& nr, int& nc)
{
	//is there is a faster path, quit this path.
	if (count > minimum)
	{
		return false;
	}

	//if the next step is a wall, return false
	if (maze[sr][sc] != ' ' && count != 0)
	{
		return false;
	}
	maze[sr][sc] = '*';

	//if player is next to goblin, return true, and set nr, nc to the current position.
	if (sr + 1 == er && sc == ec)
	{
		minimum = count + 1;
		nr = sr;
		nc = sc;
		return true;
	}
	if (sr - 1 == er && sc == ec)
	{
		minimum = count + 1;
		nr = sr;
		nc = sc;
		return true;
	}
	if (sr == er && sc - 1 == ec)
	{
		minimum = count + 1;
		nr = sr;
		nc = sc;
		return true;
	}
	if (sr == er && sc + 1 == ec)
	{
		minimum = count + 1;
		nr = sr;
		nc = sc;
		return true;
	}
	//check the adjacent position.
	bool result1 = goblinSmell(sr - 1, sc, er, ec, minimum, count + 1, nr, nc);
	bool result2 = goblinSmell(sr + 1, sc, er, ec, minimum, count + 1, nr, nc);
	bool result3 = goblinSmell(sr, sc + 1, er, ec, minimum, count + 1, nr, nc);
	bool result4 = goblinSmell(sr, sc + 1, er, ec, minimum, count + 1, nr, nc);

	return result1 || result2 || result3 || result4;
}

string Level::moveAllMonsters()
{
	string result = "";
	for (vector<Actor*>::iterator pos = m_monsters.begin(); pos != m_monsters.end(); pos++)
	{
		Actor* monster = *pos;
		Bogeymen* bogeymen = dynamic_cast<Bogeymen*>(monster);
		Snakewomen* snakewomen = dynamic_cast<Snakewomen*>(monster);
		Goblin* goblin = dynamic_cast<Goblin*>(monster);
		int row = m_player->getRow();
		int col = m_player->getCol();
		//if the monster is bogey man and smells player, move the bogeyman.
		if (bogeymen != nullptr)
		{
			if (bogeymen->smellsPlayer(row, col))
			{
				char direction = bogeymen->moveDirection(row, col);
				result = moveMonster(bogeymen, direction);
			}
		}
		//likewise, move teh snakewomen.
		if (snakewomen != nullptr)
		{
			if (snakewomen->smellsPlayer(row, col))
			{
				char direction = snakewomen->moveDirection(row, col);
				result = moveMonster(snakewomen, direction);
			}
		}
		//if is goblin and can bne smelled, move goblin.
		if (goblin != nullptr)
		{
			refreshMaze();
			int nextRow = -1;
			int nextCol = -1;
			//min is the smell distance of the goblin, edit in the future.
			int min = goblinSmellDistance;
			if (goblinSmell(row, col, goblin->getRow(), goblin->getCol(), min, 0, nextRow, nextCol))
			{
				if (m_board[nextRow][nextCol] == ' ')
				{
					m_board[goblin->getRow()][goblin->getCol()] = ' ';
					m_board[nextRow][nextCol] = 'G';
					goblin->setPos(nextRow, nextCol);
				}
				else if(m_board[nextRow][nextCol] == '@')
				{
					result = attack(goblin, m_player);
				}
			}
		}
	}
	return result;
}

string Level::moveMonster(Actor* monster, char direction)
{
	//similar to move player, if the cell in front of the monster is empty, the monster will move to it
	//if it is next to the player, it will attack the player.
	string result = "";
	int row = monster->getRow();
	int col = monster->getCol();
	switch (direction)
	{
	case ARROW_DOWN:
	{
		//if the cell is empty, move to the cell
		if (m_board[row + 1][col] == ' ')
		{
			m_board[row][col] = ' ';
			m_board[row + 1][col] = monster->icon();
			monster->setPos(row + 1, col);
			break;
		}
		//if the cell is where the player is , attack it.
		if (m_board[row + 1][col] == '@')
		{
			result = attack(monster, m_player);
		}
		break;
	}
	//same for all four switch cases, exepct they are in different direction.
	case ARROW_UP:
	{
		if (m_board[row - 1][col] == ' ')
		{
			m_board[row][col] = ' ';
			m_board[row - 1][col] = monster->icon();
			monster->setPos(row - 1, col);
			break;
		}
		if (m_board[row - 1][col] == '@')
		{
			result = attack(monster, m_player);
		}
		break;
	}
	case ARROW_LEFT:
	{
		if (m_board[row][col - 1] == ' ')
		{
			m_board[row][col] = ' ';
			m_board[row][col - 1] = monster->icon();
			monster->setPos(row , col - 1);
			break;
		}
		if (m_board[row ][col - 1] == '@')
		{
			result = attack(monster, m_player);
		}
		break;
	}
	case ARROW_RIGHT:
	{
		if (m_board[row][col + 1] == ' ')
		{
			m_board[row][col] = ' ';
			m_board[row][col + 1] = monster->icon();
			monster->setPos(row, col + 1);
			break;
		}
		if (m_board[row][col + 1] == '@')
		{
			result = attack(monster, m_player);
		}
		break;
	}
	}
	return result;
}

void Level::refreshMaze()
{
	//resets the maze.
	for (int row = 0; row < MAXROW; row++)
	{
		for (int col = 0; col < MAXCOL; col++)
		{
			if (m_board[row][col] != '#')
			{
				maze[row][col] = ' ';
			}
		}
	}
}

void Level::initRooms()
{
	//separate m_board into 3 vertical regions, each generating 1 - 2 rooms. If there are two rooms, connect them with a corridoor
	//by picking 1 random spot in the top room, connecting it downward, to the top row of bottom room, and search horizontally if 
	//the corridoor still have not reached the secound room.
	//generate the first region: col 0 - 23.
	if (trueWithProbability(0.7))
	{
		//if true, generate 2 rooms.
		//generate first room
		int sr = randInt(1, 3);
		int sc = randInt(1, 5);
		int height = randInt(4, 6);
		int width = randInt(8, 16);
		drawRoom(sr, sc, sr + height, sc + width);
		//choose corridoor col
		int corridoor = randInt(sc, sc + width);
		int corridoorLength = randInt(3, 6);
		int botRoomTop = sr + height + corridoorLength;
		drawRoom(sr + height, corridoor, botRoomTop, corridoor);
		int botRoomBot = randInt(botRoomTop, 16);
		int botRoomLeft = randInt(1, 5);
		int botRoomRight = randInt(botRoomLeft + 8, botRoomLeft + 16);
		drawRoom(botRoomTop, botRoomLeft, botRoomBot, botRoomRight);
		//if the the corridoor is to the right of the room, conect it to the left
		if (corridoor > botRoomRight)
		{
			int temp = corridoor - 1;
			while (m_board[botRoomTop][temp] != ' ' && temp > 1)
			{
				m_board[botRoomTop][temp] = ' ';
				temp--;
			}
		}
		//likewise for the left.
		if (corridoor < botRoomLeft)
		{
			int temp = corridoor + 1;
			while (m_board[botRoomTop][temp] != ' ' && temp < 22)
			{
				m_board[botRoomTop][temp] = ' ';
				temp++;
			}
		}
	}
	else
	{
		int sr = randInt(2, 5);
		int sc = randInt(2, 6);
		int er = randInt(10, 16);
		int ec = randInt(12, 20);
		drawRoom(sr, sc, er, ec);
	}
	//generate the secound region: col 24 - 46
	if (trueWithProbability(0.4))
	{
		//if true, generate 2 rooms.
		//generate first room
		int sr = randInt(1, 3);
		int sc = randInt(24, 29);
		int height = randInt(4, 6);
		int width = randInt(8, 16);
		drawRoom(sr, sc, sr + height, sc + width);
		//choose corridoor col
		int corridoor = randInt(sc, sc + width);
		int corridoorLength = randInt(3, 6);
		int botRoomTop = sr + height + corridoorLength;
		drawRoom(sr + height, corridoor, botRoomTop, corridoor);
		int botRoomBot = randInt(botRoomTop, 16);
		int botRoomLeft = randInt(24, 29);
		int botRoomRight = randInt(botRoomLeft + 8, botRoomLeft + 16);
		drawRoom(botRoomTop, botRoomLeft, botRoomBot, botRoomRight);
		//if the the corridoor is to the right of the room, conect it to the left
		if (corridoor > botRoomRight)
		{
			int temp = corridoor - 1;
			while (m_board[botRoomTop][temp] != ' ' && temp > 24)
			{
				m_board[botRoomTop][temp] = ' ';
				temp--;
			}
		}
		//likewise for the left.
		if (corridoor < botRoomLeft)
		{
			int temp = corridoor + 1;
			while (m_board[botRoomTop][temp] != ' ' && temp < 46)
			{
				m_board[botRoomTop][temp] = ' ';
				temp++;
			}
		}
	}
	else
	{
		int sr = randInt(2, 5);
		int sc = randInt(24, 29);
		int er = randInt(12, 16);
		int ec = randInt(35, 44);
		drawRoom(sr, sc, er, ec);
	}
	//generate the third region: col 47 - 69
	if (trueWithProbability(0.8))
	{
		//if true, generate 2 rooms.
		//generate first room
		int sr = randInt(1, 3);
		int sc = randInt(47, 51);
		int height = randInt(4, 6);
		int width = randInt(8, 16);
		drawRoom(sr, sc, sr + height, sc + width);
		//choose corridoor col
		int corridoor = randInt(sc, sc + width);
		int corridoorLength = randInt(3, 6);
		int botRoomTop = sr + height + corridoorLength;
		drawRoom(sr + height, corridoor, botRoomTop, corridoor);
		int botRoomBot = randInt(botRoomTop, 16);
		int botRoomLeft = randInt(47, 51);
		int botRoomRight = randInt(botRoomLeft + 8, botRoomLeft + 16);
		drawRoom(botRoomTop, botRoomLeft, botRoomBot, botRoomRight);
		//if the the corridoor is to the right of the room, conect it to the left
		if (corridoor > botRoomRight)
		{
			int temp = corridoor - 1;
			while (m_board[botRoomTop][temp] != ' ' && temp > 47)
			{
				m_board[botRoomTop][temp] = ' ';
				temp--;
			}
		}
		//likewise for the left.
		if (corridoor < botRoomLeft)
		{
			int temp = corridoor + 1;
			while (m_board[botRoomTop][temp] != ' ' && temp < 51)
			{
				m_board[botRoomTop][temp] = ' ';
				temp++;
			}
		}
	}
	else
	{
		int sr = randInt(2, 5);
		int sc = randInt(47, 51);
		int er = randInt(10, 16);
		int ec = randInt(35, 44);
		drawRoom(sr, 48, er, 67);
	}
	//because row 8-10 will always have empty cells, connect them.
	int row1 = randInt(8, 10);
	int col1 = 23;
	//find empty cell in first region
	while (m_board[row1][col1] != ' ' && col1 > 1)
	{
		col1--;
	}
	col1++;
	while (m_board[row1][col1] != ' ')
	{
		m_board[row1][col1] = ' ';
		col1++;
	}
	//do the same for secound and third region
	int row2 = randInt(8, 10);
	int col2 = 47;
	//find empty cell in first region
	while (m_board[row2][col2] != ' '&& col2 > 1)
	{
		col2--;
	}
	col2++;
	while (m_board[row1][col2] != ' ' && col2 < 68)
	{
		m_board[row1][col2] = ' ';
		col2++;
	}
	
}

void Level::addIdol()
{
	//generates a valid random position to for the idol and initiates it.
	int row = randInt(1, 16);
	int col = randInt(1, 68);
	while(!isCellEmpty(row, col))
	{
		row = randInt(1, 16);
		col = randInt(1, 68);
	}
	//because only lv4 has the idol and once the player moves to it the game is over,
	//so we only record the idol on m_board.
	m_board[row][col] = '&';
}

void Level::addStair()
{
	//if it is level 4, do not add stair.
	if (currentLevel == 4)
	{
		m_stair = nullptr;
		return;
	}
	//gernerate random valid address for stair.
	int row = randInt(1, 16);
	int col = randInt(1, 68);
	while (!isCellEmpty(row, col))
	{
		row = randInt(1, 16);
		col = randInt(1, 68);
	}
	m_stair = new Stair(row, col);
	m_board[row][col] = '>';
}

void Level::newLevel()
{
	if (m_player->getRow() == m_stair->getRow() && m_player->getCol() == m_stair->getCol())
	{
		currentLevel = currentLevel + 1;
		for (int pos1 = 0; pos1 < MAXROW; pos1++)
		{
			for (int pos2 = 0; pos2 < MAXCOL; pos2++)
			{
				m_board[pos1][pos2] = '#';
				maze[pos1][pos2] = '#';
			}
		}
		initRooms();
		refreshMaze();
		initPlayer();
		initObjects();
		addMonster(currentLevel);
		if (currentLevel < 4)
		{
			addStair();
		}
		if (currentLevel == 4)
		{
			addIdol();
		}
	}
}

void Level::updateObjects()
{
	for (vector<Object*>::iterator pos = m_objects.begin(); pos != m_objects.end(); pos++)
	{
		Object* temp = *pos;
		//double check that the object is indeed on the board.
		if (temp->getRow() >= 0 && temp->getCol() >= 0)
		{
			//use dynamic cast to check if the object is a weapon or scroll.
			Weapon* weapon = dynamic_cast<Weapon*>(temp);
			if (weapon == nullptr)
			{
				m_board[temp->getRow()][temp->getCol()] = '?';
			}
			else
			{
				m_board[temp->getRow()][temp->getCol()] = ')';
			}
		}
	}
}

int Level::getCurrentLevel()
{
	return currentLevel;
}