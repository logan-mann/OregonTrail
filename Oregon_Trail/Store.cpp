#include <iostream>
#include "Store.h"

using namespace std;

Store::Store()
{
    //sets the initial store prices
    initialOxenPrice = 40.00;
    initialFoodPrice = 0.50;
    initialBulletPrice = 2.00;
    initialPartsPrice = 20.00;
    initialMedKitPrice = 25.00;
    
    //sets the current store prices
    oxenPrice = 40.00;
    foodPrice = 0.50;
    bulletPrice = 2.00;
    partsPrice = 20.00;
    medKitPrice = 25.00;
    //sets the current store number to 0
    storeNumber = 0;
}

//THESE GETTERS RETURN INITIAL STORE PRICES
double Store::getInitialOxenPrice() const
{
    return initialOxenPrice;
}

double Store::getInitialFoodPrice() const
{
    return initialFoodPrice;
}

double Store::getInitialBulletsPrice() const
{
    return initialBulletPrice;
}

double Store::getInitialPartsPrice() const
{
    return initialPartsPrice;
}

double Store::getInitialMedKitPrice() const
{
    return initialMedKitPrice;
}

//THESE GETTERS RETURN THE CURRENT STORE PRICES
double Store::getOxenPrice() const
{
    return oxenPrice;
}

double Store::getFoodPrice() const
{
    return foodPrice;
}

double Store::getBulletsPrice() const
{
    return bulletPrice;
}

double Store::getPartsPrice() const
{
    return partsPrice;
}

double Store::getMedKitPrice() const
{
    return medKitPrice;
}

//adds 0.25 * the store the player is at to the current store prices
void Store::increasePrices()
{
    storeNumber++;
    oxenPrice = initialOxenPrice * (1.00 + (0.25 * storeNumber));
    foodPrice = initialFoodPrice * (1.00 + (0.25 * storeNumber));
    bulletPrice = initialBulletPrice * (1.00 + (0.25 * storeNumber));
    partsPrice = initialPartsPrice * (1.00 + (0.25 * storeNumber));
    medKitPrice = initialMedKitPrice * (1.00 + (0.25 * storeNumber));
    
}

//THESE FUNCTIONS INCREASE THE PRICE OF THAT ITEM BY THE PERCENT INCREASE PASSED OF THE INITIAL ITEM PRICE
void Store::increaseOxenPrice(double percentIncrease)
{
    oxenPrice = initialOxenPrice * (1.00 + percentIncrease);
}

void Store::increaseFoodPrice(double percentIncrease)
{
    foodPrice = initialFoodPrice * (1.00 + percentIncrease);
}

void Store::increaseBulletPrice(double percentIncrease)
{
    bulletPrice = initialBulletPrice * (1.00 + percentIncrease);
}

void Store::increasePartsPrice(double percentIncrease)
{
    partsPrice = initialPartsPrice * (1.00 + percentIncrease);
}

void Store::increaseMedKitPrice(double percentIncrease)
{
    medKitPrice = initialMedKitPrice * (1.00 + percentIncrease);
}

//returns the store number the player is at
int Store::getStoreNumber() const
{
    return storeNumber;
}

//This is a current version of the file