#include <iostream>

using namespace std;

#ifndef MILESTONE_H
#define MILESTONE_H

class Milestone
{
    public:
        Milestone();
        Milestone(string milestoneName, int distance, bool fortStatus, int depthNum);
        
        //returns the milestone's name, distance from start, depth, or fort status
        string getMilestoneName() const;
        int getDistance() const;
        bool getIsFort() const;
        int getDepth()const;
        
        //sets the milestone's name, distance from start, depth, or fort status
        void setMilestoneName(string newName);
        void setDistance(int newDistance);
        void setIsFort(bool newIsFort);
        void setDepth(int newDepth);
        
    private:
       
        //name of the milestone
        string name;
        
        //distance in miles from the starting point
        int distanceFromStart;
        
        /*denotes whether the milestone is a fort (true).ß
        If this is false, the milestone is a river and must be dealt with accordingly
        */
        bool isFort;
    
        //integer value referring to the depth of a river in feet, this datamember is 0 and irrelevant for forts
        int depth;
};

#endif


//This is a current version of the file