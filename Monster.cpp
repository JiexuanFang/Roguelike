#include "Monster.h"

using namespace std;

int absolute(int i)
{
	if (i < 0)
	{
		i = -i;
	}
	return i;
}

Bogeymen::Bogeymen(int row, int col)
	:Actor(row, col, randInt(5, 10), new ShortSword, randInt(2,3), randInt(2,3), 2)
{

}

Bogeymen::~Bogeymen()
{
	
}

bool Bogeymen::smellsPlayer(int row, int col)
{
	if (absolute(row - getRow()) + absolute(col - getCol()) <= 5)
	{
		return true;
	}
	return false;
}

Object* Bogeymen::dropObject()
{
	//1 in 10 chance to drop a axe.
	int temp = randInt(1, 10);
	if (temp == 1)
	{
		Weapon* droppedAxe = new MagicAxe;
		droppedAxe->setPos(getRow(), getCol());
		return droppedAxe;
	}
	return nullptr;
}

//returns the direction to player regardless of walls.
char Bogeymen::moveDirection(int row, int col)
{

	if (getRow() < row)
	{
		return ARROW_DOWN;
	}
	else if (getRow() > row)
	{
		return ARROW_UP;
	}
	else if (getCol() < col)
	{
		return ARROW_RIGHT;
	}
	else
	{
		return ARROW_LEFT;
	}
}

char Bogeymen::icon()
{
	return 'B';
}

string Bogeymen::name()
{
	return "Bogeymen ";
}

Snakewomen::Snakewomen(int row, int col)
	:Actor(row, col, randInt(3,6), new MagicFang, 3,2,3)
{
}

Snakewomen::~Snakewomen()
{

}

bool Snakewomen::smellsPlayer(int row, int col)
{
	if (absolute(row - getRow()) + absolute(col - getCol()) <= 3)
	{
		return true;
	}
	return false;
}

Object* Snakewomen::dropObject()
{
	int temp = randInt(1, 3);
	if (temp == 1)
	{
		Weapon* droppedFangs = new MagicFang;
		droppedFangs->setPos(getRow(), getCol());
		return droppedFangs;
	}
	return nullptr;
}

char Snakewomen::moveDirection(int row, int col)
{
	if (getRow() < row)
	{
		return ARROW_DOWN;
	}
	else if (getRow() > row)
	{
		return ARROW_UP;
	}
	else if (getCol() < col)
	{
		return ARROW_RIGHT;
	}
	else
	{
		return ARROW_LEFT;
	}
}

char Snakewomen::icon()
{
	return 'S';
}

string Snakewomen::name()
{
	return "Snakewomen ";
}

Dragon::Dragon(int row, int col)
	:Actor(row, col, randInt(20,25), new LongSword, 4,4,4)
{
}

Dragon::~Dragon()
{
}

Object* Dragon::dropObject()
{
	//use a switch function to determine which scroll will be dropped
	int type = randInt(4);
	switch (type)
	{
	case 0:
	{
		return new teleportationScroll(getRow(), getCol());
		break;
	}
	case 1:
	{
		return new enhanceArmorScroll(getRow(), getCol());
		break;
	}
	case 2:
	{
		return new enhanceHealthScroll(getRow(), getCol());
		break;
	}
	case 3:
	{
		return new enhanceDexterityScroll(getRow(), getCol());
		break;
	}
	case 4:
	{
		return new StrengthScroll(getRow(), getCol());
		break;
	}
	}
	return nullptr;
}

void Dragon::gainHealth()
{
	int temp = randInt(1, 10);
	if (temp == 1)
	{
		setHitPoint(getHitPoints() + 1);
	}
}

char Dragon::icon()
{
	return 'D';
}

string Dragon::name()
{
	return "Dragon ";
}

Goblin::Goblin(int row, int col)
	:Actor(row, col, randInt(15,20), new ShortSword, 1, 3, 1)
{

}

Goblin::~Goblin()
{

}

Object* Goblin::dropObject()
{
	//one in three chance to drop weapon
	int temp = randInt(1, 3);
	if (temp == 1)
	{
		//drops either axe or magic Fang
		int type = randInt(1, 2);
		switch (type)
		{
		case 1:
		{
			Object* droppedAxe = new MagicAxe;
			droppedAxe->setPos(getRow(), getCol());
			return droppedAxe;
			break;
		}
		case 2:
		{
			Object* droppedFang = new MagicFang;
			droppedFang->setPos(getRow(), getCol());
			return droppedFang;
			break;
		}
		}
	}
	return nullptr;
}

char Goblin::icon()
{
	return 'G';
}

string Goblin::name()
{
	return "Goblin ";
}