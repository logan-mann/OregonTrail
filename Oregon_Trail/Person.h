#include <iostream>

using namespace std;

#ifndef PERSON_H
#define PERSON_H

class Person
{
private:
    string name;
    bool health;
    bool alive;
public:
    Person();
    Person(string newName);
    string getName() const;
    bool getHealth() const;
    bool getAlive() const;
    void setName(string newName);
    void setHealth(bool newHealth);
    void setAlive(bool newAlive);
    void toggleHealth();
    void toggleAlive();
};

#endif

//This is a current version of the file