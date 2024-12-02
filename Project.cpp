#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);
void LoseScreen(void);

////////////////////

Player *playerPtr;
GameMechs *gameMechsPtr;
Food *foodPtr;

int main(void)
{

    Initialize();

    while (gameMechsPtr->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    // Show losescreen before exiting out
    for (int i = 0; i < 20 && gameMechsPtr->getLoseFlagStatus() == true; i++)
    {
        LoseScreen();
        LoopDelay();
    }
    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    gameMechsPtr = new GameMechs(30, 15);
    foodPtr = new Food(); //
    playerPtr = new Player(gameMechsPtr, foodPtr);

    // Generate  food items
    foodPtr->generateFood(playerPtr->getPlayerPos(), gameMechsPtr);
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        char input = MacUILib_getChar();
        gameMechsPtr->setInput(input);
    }
    fflush(stdin);
}

void RunLogic(void)
{
    playerPtr->movePlayer();
}

// Display for lost game
void LoseScreen(void)
{
    MacUILib_clearScreen();
    int x_max = gameMechsPtr->getBoardSizeX();
    int y_max = gameMechsPtr->getBoardSizeY();
    for (int y = 0; y < y_max; y++)
    {
        for (int x = 0; x < x_max; x++)
        {
            if (y == 0 || y == y_max - 1 || x == 0 || x == x_max - 1)
            {
                MacUILib_printf("#");
            }
            else if (y == y_max / 2 - 2)
            {
                MacUILib_printf("L");
            }
            else if (y == y_max / 2 - 1)
            {
                MacUILib_printf("O");
            }
            else if (y == y_max / 2)
            {
                MacUILib_printf("S");
            }
            else if (y == y_max / 2 + 1)
            {
                MacUILib_printf("E");
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPosArrayList *pos = playerPtr->getPlayerPos();
    int playerSize = pos->getSize();
    const objPosArrayList *foodList = foodPtr->getFoodBucket(); // Get all the food items in the bucket
    int x_max = gameMechsPtr->getBoardSizeX();
    int y_max = gameMechsPtr->getBoardSizeY();

    for (int y = 0; y < y_max; y++)
    {
        for (int x = 0; x < x_max; x++)
        {
            // Draw the border
            if (y == 0 || y == y_max - 1 || x == 0 || x == x_max - 1)
            {
                MacUILib_printf("#");
            }
            else
            {
                bool isPrinted = false;

                // Check and print the player (snake)
                for (int k = 0; k < playerSize; k++)
                {
                    objPos thisSeg = pos->getElement(k);
                    if (x == thisSeg.pos->x && y == thisSeg.pos->y)
                    {
                        MacUILib_printf("%c", thisSeg.getSymbol());
                        isPrinted = true;
                        break;
                    }
                }

                // If not printed as part of the snake, check for food
                if (!isPrinted)
                {
                    // Loop through all food items
                    for (int i = 0; i < foodList->getSize(); i++)
                    {
                        objPos thisFood = foodList->getElement(i);
                        if (x == thisFood.pos->x && y == thisFood.pos->y)
                        {
                            MacUILib_printf("%c", thisFood.getSymbol()); // Print the food symbol
                            isPrinted = true;
                            break;
                        }
                    }

                    // If nothing else, print an empty space
                    if (!isPrinted)
                    {
                        MacUILib_printf(" ");
                    }
                }
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("SCORE: %d", gameMechsPtr->getScore()); // print score
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    MacUILib_uninit();

    // deallocate heap memory

    delete playerPtr;
    playerPtr = nullptr;
    delete foodPtr;
    foodPtr = nullptr;
    delete gameMechsPtr;
    gameMechsPtr = nullptr;
}
