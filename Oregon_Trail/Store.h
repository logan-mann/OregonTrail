#include <iostream>

using namespace std;

#ifndef STORE_H
#define STORE_H

class Store
{
    public:
        Store();
    
        double getInitialOxenPrice() const;
        double getInitialFoodPrice() const;
        double getInitialBulletsPrice() const;
        double getInitialPartsPrice() const;
        double getInitialMedKitPrice() const;
    
        double getOxenPrice() const;
        double getFoodPrice() const;
        double getBulletsPrice() const;
        double getPartsPrice() const;
        double getMedKitPrice() const;
    
        int getStoreNumber() const;
        
        //pass a decimal, for example, .5 means a 50% increase in price
        void increaseOxenPrice(double percentIncrease);
        void increaseFoodPrice(double percentIncrease);
        void increaseBulletPrice(double percentIncrease);
        void increasePartsPrice(double percentIncrease);
        void increaseMedKitPrice(double percentIncrease);
        void increasePrices();
    private:
        //initial price per 2 oxen
        double initialOxenPrice;
        //initial price per pound
        double initialFoodPrice;
        //initial price for box of 20 bullets
        double initialBulletPrice;
        //initial price per part
        double initialPartsPrice;
        //initial price per med kit
        double initialMedKitPrice;
    
        //price per 2 oxen
        double oxenPrice;
        //price per pound
        double foodPrice;
        //price for box of 20 bullets
        double bulletPrice;
        //price per part
        double partsPrice;
        //price per med kit
        double medKitPrice;
        //number of the store currently at
        int storeNumber;
};

#endif

//This is a current version of the file