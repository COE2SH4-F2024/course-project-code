#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <ctime>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food
{
private:
    objPosArrayList *foodBucket; // A list to store food items
    const int maxFoodItems = 5;  // Number of food items to generate

public:
    Food();  
    ~Food();
    Food(int initialX, int initialY, int symbol);
    Food(const Food &other);
    Food &operator=(const Food &other);

    void generateFood(objPosArrayList *snakePositions, GameMechs *mainGameMechsRef);

    const objPosArrayList *getFoodBucket() const;
};

#endif // FOOD_H
