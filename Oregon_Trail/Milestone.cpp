#include <iostream>
#include "Milestone.h"

using namespace std;

Milestone::Milestone()
{
    name = "";
    distanceFromStart = 0;
    isFort = true;
    depth = 0;
}

Milestone::Milestone(string milestoneName, int distance, bool fortStatus, int depthNum)
{
    name = milestoneName;
    distanceFromStart = distance;
    isFort = fortStatus;
    depth = depthNum;
}

//returns the name of the milestone
string Milestone::getMilestoneName() const
{
    return name;
}

//returns distance from start of milestone
int Milestone::getDistance() const
{
   return distanceFromStart; 
}

//returns fort status of milestone
bool Milestone::getIsFort() const
{
    return isFort;
}

//sets the name of milestone to new string
void Milestone::setMilestoneName(string newName)
{
    name = newName;
}

//sets distance from start of milestone to new value
void Milestone::setDistance(int newDistance)
{
    distanceFromStart = newDistance;
}

//sets fort status to new value
void Milestone::setIsFort(bool newIsFort)
{
    isFort = newIsFort;
}

//returns depth of milestone
int Milestone::getDepth() const
{
    return depth;
}
//sets depth of milestone
void Milestone::setDepth(int newDepth)
{
    depth = newDepth;
}


//This is a current version of the file