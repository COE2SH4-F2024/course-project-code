#include "Player.h"
#include <stdio.h>

Player::Player(GameMechs *thisGMRef, Food *thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();
    myDir = STOP;

    objPos headPos(thisGMRef->getBoardSizeX() / 2,
                   thisGMRef->getBoardSizeY() / 2,
                   42);
    playerPosList->insertHead(headPos); // Intial block
    foodRef = thisFoodRef;
}

Player::~Player()
{
    delete playerPosList;
}

objPosArrayList *Player::getPlayerPos() const
{
    return playerPosList;
}

int Player::CheckFoodConsumption()
{
    const objPosArrayList *foodList = foodRef->getFoodBucket();
    for (int i = 0; i < foodList->getSize(); i++)
    {
        objPos food = foodList->getElement(i);
        objPos specialFood = foodList->getTailElement();

        if (playerPosList->getHeadElement().getObjPos().pos->x == specialFood.pos->x &&
            playerPosList->getHeadElement().getObjPos().pos->y == specialFood.pos->y)
        {
            return 2; // special food
        }
        if (playerPosList->getHeadElement().getObjPos().pos->x == food.pos->x &&
            playerPosList->getHeadElement().getObjPos().pos->y == food.pos->y)
        {
            return 1; // regular food
        }
    }
    return 0; // no food consumed
}

bool Player::CheckSelfCollision()
{
    objPos headPos = playerPosList->getHeadElement().getObjPos();
    int size = playerPosList->getSize();

    for (int i = 1; i < size; i++) // dont check head element
    {
        objPos thisSegment = playerPosList->getElement(i).getObjPos();
        if (thisSegment.pos->x == headPos.pos->x && thisSegment.pos->y == headPos.pos->y)
        {
            return true;
        }
    }
    return false;
}

void Player::updatePlayerDir()
{
    char input;
    input = mainGameMechsRef->getInput();
    if (input != 0) // if not null character
    {
        switch (input)
        {
        case 32:
            mainGameMechsRef->setExitTrue();
            break;
        case 'W':
        case 'w': // w
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;

        case 'A':
        case 'a': // a
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;

        case 'S':
        case 's': // s
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;

        case 'D':
        case 'd': // d
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;

        default:
            break;
        }
        mainGameMechsRef->clearInput();
    }
}

void Player::movePlayer()
{
    updatePlayerDir();

    objPos tempHeadPos = playerPosList->getHeadElement().getObjPos(); // Copy current head ###(#)

    switch (myDir)
    {
    case 0:
        tempHeadPos.pos->y--;
        break;
    case 2:
        tempHeadPos.pos->x--;
        break;
    case 1:
        tempHeadPos.pos->y++;
        break;
    case 3:
        tempHeadPos.pos->x++;
        break;
    default:
        break;
    }

    // Wraparound logic
    if (tempHeadPos.pos->y < 1)
    {
        tempHeadPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (tempHeadPos.pos->y > mainGameMechsRef->getBoardSizeY() - 2)
    {
        tempHeadPos.pos->y = 1;
    }
    if (tempHeadPos.pos->x < 1)
    {
        tempHeadPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (tempHeadPos.pos->x > mainGameMechsRef->getBoardSizeX() - 2)
    {
        tempHeadPos.pos->x = 1;
    }

    playerPosList->insertHead(tempHeadPos);

    if (CheckFoodConsumption())
    {
        if (CheckFoodConsumption() == 2) // special food
        {
            for (int i = 0; i < 10; i++)
            {
                mainGameMechsRef->incrementScore(); // increment 10 times
            }
        }
        else
        {
            mainGameMechsRef->incrementScore(); // regular food
        }
        foodRef->generateFood(playerPosList, mainGameMechsRef); // create new locations of food
    }
    else
    {
        playerPosList->removeTail(); // if no food consumed
    }
    if (CheckSelfCollision())
    {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
}
