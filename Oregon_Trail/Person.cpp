#include <iostream>
#include "Person.h"

using namespace std;

Person::Person()
{
    name = "";
    health = true;
    alive = true;
}

Person::Person(string newName)
{
    name = newName;
    health = true;
    alive = true;
}

string Person::getName() const
{
    return name;
}

bool Person::getHealth() const
{
    return health;
}

bool Person::getAlive() const
{
    return alive;
}

void Person::setName(string newName)
{
    name = newName;
}

void Person::setHealth(bool newHealth)
{
    health = newHealth;
}

void Person::setAlive(bool newAlive)
{
    alive = newAlive;
}

void Person::toggleHealth()
{
    if (health == true)
    {
        health = false;
        return;
    }
    else if (health == false)
    {
        health = true;
        return;
    }
}

void Person::toggleAlive()
{
    if (alive == true)
    {
        alive = false;
        return;
    }
    else if (alive == false)
    {
        alive = true;
        return;
    }
}

//This is a current version of the file