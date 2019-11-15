#include <iostream>
#include "Supply.h"

using namespace std;

Supply::Supply()
{
    money = 1000.00;
    food = 0;
    oxen = 0;
    bullets = 0;
    wagonParts = 0;
    medKits = 0;
}

//GETTERS FOR ALL THE SUPPLIES
double Supply::getMoney() const
{
    return money;
}

double Supply::getFood() const
{
    return food;
}

int Supply::getOxen() const
{
    return oxen;
}

int Supply::getBullets() const
{
   return bullets;
}

int Supply::getParts() const
{
    return wagonParts;
}

int Supply::getMeds() const
{
    return medKits;
}

//SETTERS FOR ALL THE SUPPLIES
void Supply::setMoney(double newMoney)
{
    money = newMoney;
}

void Supply::setFood(double newFood)
{
    food = newFood;
}

void Supply::setOxen(int newOxen)
{
    oxen = newOxen;
}

void Supply::setBullets(int newBullets)
{
    bullets = newBullets;
}

void Supply::setParts(int newParts)
{
    wagonParts = newParts;
}

void Supply::setMeds(int newMeds)
{
    medKits = newMeds;
}

//ADDS AMOUNT PASSED TO THE SUPPLY
void Supply::addMoney(double add_Money)
{
    money = money + add_Money;
}

void Supply::addFood(double add_Food)
{
    food = food + add_Food;
}

void Supply::addOxen(int add_Oxen)
{
    oxen = oxen + add_Oxen;
}

void Supply::addBullets(int add_Bullets)
{
    bullets = bullets + add_Bullets;
}

void Supply::addParts(int add_Parts)
{
    wagonParts = wagonParts + add_Parts;
}

void Supply::addMeds(int add_Meds)
{
    medKits = medKits + add_Meds;
}

//This is a current version of the file