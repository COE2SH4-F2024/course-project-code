#include "Food.h"
#include "GameMechs.h"
#include "Player.h"
#include <time.h>

Food::Food()
{
    foodBucket = new objPosArrayList(); // Initialize the food list
}

Food::~Food()
{
    delete foodBucket; // Clean up the list when done
}

Food::Food(const Food &other)
{
    // Perform deep copy of foodBucket
    foodBucket = new objPosArrayList(*other.foodBucket);
}

// Copy assignment operator
Food &Food::operator=(const Food &other)
{
    if (this == &other)
        return *this; // Self-assignment check

    // Clean up existing resources
    delete foodBucket;

    // Perform deep copy
    foodBucket = new objPosArrayList(*other.foodBucket);

    return *this;
}

void Food::generateFood(objPosArrayList *snakePositions, GameMechs *mainGameMechsRef)
{
    srand(time(NULL)); // Seed the random number generator
    int xRange = mainGameMechsRef->getBoardSizeX() - 2;
    int yRange = mainGameMechsRef->getBoardSizeY() - 2;

    while (foodBucket->getSize() != 0)
    {
        foodBucket->removeHead();
    }

    while (foodBucket->getSize() < maxFoodItems - 1) // Continue until the list is full
    {
        int randomX = rand() % xRange + 1;
        int randomY = rand() % yRange + 1;

        bool validPosition = true;
        for (int i = 0; i <= foodBucket->getSize(); i++)
        {
            objPos thisSegment = foodBucket->getElement(i);
            if (thisSegment.pos->x == randomX && thisSegment.pos->y == randomY)
            {
                validPosition = false;
                break;
            }
        }

        if (validPosition)
        {
            objPos newFood(randomX, randomY, '^');
            foodBucket->insertTail(newFood);
        }
    }

    while (foodBucket->getSize() < maxFoodItems)
    {
        int randomX = rand() % xRange + 1;
        int randomY = rand() % yRange + 1;

        bool validPosition = true;
        objPos thisSegment = foodBucket->getElement(foodBucket->getSize());
        if (thisSegment.pos->x == randomX && thisSegment.pos->y == randomY)
        {
            validPosition = false;
            break;
        }
        else
        {
            objPos newFood(randomX, randomY, '~'); // Special Food
            foodBucket->insertTail(newFood);
            break;
        }
    }
}

const objPosArrayList *Food::getFoodBucket() const
{
    return foodBucket;
}
