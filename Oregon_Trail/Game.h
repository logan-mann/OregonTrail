#include <iostream>
#include "Map.h"
#include "Supply.h"
#include "Date.h"
#include "Person.h"
#include "Store.h"

using namespace std;

#ifndef GAME_H
#define GAME_H

class Game
{
    public:
        Game();
        //creates the party
        void createParty(string playerName, string person2, string person3, string person4, string person5);
        //advances the date throughout the game
        void dateAdvancer(int days);
        //advances milestones throughout the game
        void updateMilestone();
        //called when the player shops at the store
        void storeAction();
        //called when hunting occurs
        void huntingAction();
        //called when the player decides to rest
        void restingAction();
        //called when the player continues on the trail
        void continueOnTrail();
        //called when a misfortune/positive event occurs
        void randomEventOccur();
        //called when a raider attack occures
        void raiderAttack();
        //called when the player reaches a milestone
        void atMilestone();
        //called when a puzzle is needed
        bool puzzle();
        //returns the number of party members still alive
        int getMembersAlive() const;
        //returns total miles travelled
        int getMilesTravelled() const;
        //returns the distance from start of the next milestone
        int getNextMilestoneMileage() const;
        //prints welcome signs when arriving at forts
        void printFortSign() const;
        //returns whether the leader is still alive
        bool leaderAlive() const;
        //returns whether the party still has food
        bool haveFood() const;
        //returns whether the party still has oxen
        bool haveOxen() const;
        //returns whether the wagon is functional/able to be fixed
        bool wagonWorks() const;
        //returns whether the deadline has been reached or not
        bool dateOk() const;
        //returns whether the goal has been reached
        bool journeyComplete() const;
        //prints a status update
        void statusUpdate() const;
        //prints the final game stats and writes them to a file
        int writeGameStats() const;
    
        
    private:
        //all part members
        Person partyMembers[5];
        //supplies of the party
        Supply supplies;
        //current date during the game
        Date currentDate;
        //map w/ milestones etc.
        Map gameMap;
        //store w/ prices etc.
        Store store;
};

#endif

//This is a current version of the file
