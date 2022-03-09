// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
    :goblin_smell_distance(goblinSmellDistance), 
    p1(-1,-1), clv(&p1, 0, goblin_smell_distance)
{
}

void Game::play()
{
    //displays the board and statistics
    clv.display();
    cout << "Dungeon Level: " << clv.getCurrentLevel()<< ", Hit points: " << p1.getHitPoints()
        << ", Armor: " << p1.getArmorPoints() << ", Strength: " << p1.getStrengthPoints()
        << ", Dexterity: " << p1.getDexeterityPoints() << endl;
    cout << "Press q to exit game." << endl;
    string result = "";
    while (isAlive() == true)
    {
        clv.updateObjects();
        char command = getCharacter();
        if (command == 'q')
        {
            break;
        }
        switch (command)
        {
        //if the player moves, update the game
        case ARROW_LEFT:
        case ARROW_DOWN:
        case ARROW_RIGHT:
        case ARROW_UP:
        {
            result = clv.movePlayer(command);
            break;
        }
        //if the player types i, open inventory
        case 'i':
        {
           result =  clv.useInventory();
           break;
        }
        //if the player type g, pick up object
        case 'g':
        {
            result = clv.pickUpObject();
            break;
        }
        //if the player type c, increase the player;s statistics
        case 'c':
        {
            p1.setDexterityPoints(30);
            p1.setHitPoint(50);
            p1.setStrengthPoints(10);
            break;
        }
        //if the player type > or .(when he does not use shift), enter next level
        case '>':
        case '.':
        {
            clv.newLevel();
            break;
        }
        }
        //displays the game.
        result = result + clv.moveAllMonsters();
        clearScreen();
        clv.display();
        cout << "Dungeon Level: " << clv.getCurrentLevel() << ", Hit points: " << p1.getHitPoints()
            << ", Armor: " << p1.getArmorPoints() << ", Strength: " << p1.getStrengthPoints()
            << ", Dexterity: " << p1.getDexeterityPoints() << endl;
        cout << result << endl;
        cout << "Press q to exit game." << endl;
        //refresh result to empty string
        result = "";
    }
    return;
}

bool Game::isAlive()
{
    bool alive = true;
    if (p1.getHitPoints() <= 0)
    {
        alive = false;
    }
    return alive;
}


// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
