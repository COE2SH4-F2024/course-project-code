#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"


class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

public:
    enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    }; // This is the direction state

    Player(GameMechs *thisGMRef, Food *thisFoodRef);
    ~Player();

    objPosArrayList *getPlayerPos() const; // Upgrade this in iteration 3.
    void updatePlayerDir();
    void movePlayer();
    int CheckFoodConsumption();
    bool CheckSelfCollision();
    // More methods to be added here

private:
    // objPos playerPos; // Upgrade this in iteration 3.
    objPosArrayList *playerPosList;
    enum Dir myDir;
    Food *foodRef;

    // Need a reference to the Main Game Mechanisms
    GameMechs *mainGameMechsRef;
};

#endif