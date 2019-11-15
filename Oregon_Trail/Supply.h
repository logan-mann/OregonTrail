
#include <iostream>

using namespace std;

#ifndef SUPPLY_H
#define SUPPLY_H

class Supply
{
private:
    double money;
    double food;
    int oxen;
    int bullets;
    int wagonParts;
    int medKits;
public:
    
    Supply();
    
    //returns total money
    double getMoney() const;
    //returns total food
    double getFood() const;
    //returns total oxen
    int getOxen() const;
    //returns total bullets
    int getBullets() const;
    //returns total wagon parts
    int getParts() const;
    //returns total med kits
    int getMeds() const;
    
    //sets indicated data member to a new value
    void setMoney(double newMoney);
    void setFood(double newFood);
    void setOxen(int newOxen);
    void setBullets(int newBullets);
    void setParts(int newParts);
    void setMeds(int newKits);
    
    //adds passed value to the specified data member
    void addMoney(double add_Money);
    void addFood(double add_Food);
    void addOxen(int add_Oxen);
    void addBullets(int add_Bullets);
    void addParts(int add_Parts);
    void addMeds(int add_Meds);
};

#endif


//This is a current version of the file