#include <iostream>
#include <fstream>
#include "Milestone.h"

using namespace std;

#ifndef MAP_H
#define MAP_H

class Map
{
    public:
        Map();
        Map(Milestone milestones[], int totalMilestones);
        
        //returns the number of milestones, index of next milestone, miles travelled, or the distance to the next milestone
        int getNumMilestones() const;
        int getNextMilestone() const;
        int getMilesTravelled() const;
    
        int getNextMilestoneMileage() const;
        bool getNextMilestoneFort() const;
        string getNextMilestoneName() const;
        int getNextMilestoneDepth()const;
        
        //sets total number of milestones, index of next milestone, or miles travelled to a new value
        void setNumMilestones(int newNumMilestones);
        void setNextMilestone(int newNextMilestone);
        void setMilesTravelled(int newMilesTravelled);
    
        //increments the next milestone index
        void incrementNextMilestone();
    
        //adds the passed number of miles to the total number of miles travelled
        void addMilesTravelled(int miles);
    
        //reads milestones from files
        int readMilestones(string fortFile, string riverFile);
    
        //increments the next milestone index
        void milestoneAdvance();
    
    private:
        //array of all the milestones, there can be a maximum of 200 milestones on the map
        Milestone allMilestones[200];
        //total number of milestones on the map, must be less than or equal to 200
        int numMilestones;
        //refers to the index in the array of the next milestone to be reached 
        int nextMilestone;
        //total number of miles the player has travelled
        int milesTravelled;
};

#endif


//This is a current version of the file