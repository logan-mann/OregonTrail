#include <iostream>
#include "Map.h"

using namespace std;

Map::Map()
{
    //sets all integer data members to 0
    numMilestones = 0;
    nextMilestone = 0;
    milesTravelled = 0;
}

Map::Map(Milestone milestones[], int totalMilestones)
{
    //sets the number of milestones to the value passed
    numMilestones = totalMilestones;
    //initializes the all milestones array based on the milestones array passed
    for (int i = 0; i < totalMilestones; i++)
    {
        allMilestones[i] = milestones[i];
    }
    //miles travelled and next milestone are set to 0
    milesTravelled = 0;
    nextMilestone = 0;
}

//returns number of milestones
int Map::getNumMilestones() const
{
    return numMilestones;
}

//returns the index of the next milestone
int Map::getNextMilestone() const
{
    return nextMilestone;
}

//returns miles travelled by the player
int Map::getMilesTravelled() const
{
    return milesTravelled;
}

//sets the number of milestones
void Map::setNumMilestones(int newNumMilestones)
{
    numMilestones = newNumMilestones;
}

//sets the index of the new next milestone if it is within the confines of the array of milestones
void Map::setNextMilestone(int newNextMilestone)
{
    if (newNextMilestone < numMilestones)
    {
        nextMilestone = newNextMilestone;
    }
}

//sets the number of miles travelled by the player
void Map::setMilesTravelled(int newMilesTravelled)
{
    milesTravelled = newMilesTravelled;
}

//increments the next milestone index by 1
void Map::incrementNextMilestone()
{
    nextMilestone++;
}

//adds the number of miles passed to miles travelled
void Map::addMilesTravelled(int miles)
{
    //if the number of miles travelled + miles passed is greater than or equal to the mile marker of the next milestone, the miles travelled is set to the mileage of the next milestone
    if (milesTravelled + miles >= allMilestones[nextMilestone].getDistance())
    {
        milesTravelled = allMilestones[nextMilestone].getDistance();
    }
    //otherwise, miles passed are simply added to the total miles travelled
    else
    {
        milesTravelled = milesTravelled + miles;
    }
}


/*
 This function reads data from a fort and river file
 1. reads through each line in the fort file, gets distance from start and the name, puts this data into a milestone object, puts this object into an array of milestones, for each milestone added, increments a value of total milestones
 2. does the same for a river file
 3. goes through each pair of adjecent array elements in milestone array, if the first one has a greater distance from start, swap the elements (THIS SHOULD SORT THE MILESTONE ARRAY ACCORDING TO DISTANCE FROM START)
 4. Populates the allMilestones[] data member with the elements in the milestone array created
 */
int Map::readMilestones(string fortFile, string riverFile)
{
    //temporary array of milestones
    Milestone tempMilestoneArray[200];
    //stream for the fort file
    ifstream fortData;
    //stream for the river file
    ifstream riverData;
    //string for the current milestone's name
    string currentMilestoneName;
    //int value of the current milestone's distance from the start
    int currentDistanceInt;
    //string variable to clear random stuff from getline
    string clearGetline;
    //string for the current milestone's distance from the start
    string currentDistanceString;
    //string for the current milestone's depth (if the milestone is a fort, this value is 0 and is irrelevant)
    string currentDepthString;
    //int for the current milestone's depth (again irrelevant if the milestone is a fort
    int currentDepthInt;
    //milestone variable for the current milestone being read
    Milestone currentMilestone;
    //int for the total number of milestones
    int totalMilestones = 0;
    //open fort file
    fortData.open(fortFile);
    //if the fort file fails to open, error message prints and function returns -99
    if (fortData.fail())
    {
        cout << "The fort file name passed could not be found." << endl;
        return -99;
    }
    
    //this for loop reads all the fort milestones into the tempMilestoneArray
    for (int i = numMilestones; i < 200; i++)
    {
        //if read is successful, increments total milestones
        if (getline(fortData, currentMilestoneName))
        {
            totalMilestones++;
        }
        //reads distance into a string
        getline(fortData, currentDistanceString, 'm');
        //converts the string for distance into an int
        currentDistanceInt = stoi(currentDistanceString);
        //clears getline
        getline(fortData, clearGetline);
        //sets isFort for the current milestone to true, since we are reading from a fort file
        currentMilestone.setIsFort(true);
        //sets distance of the current milestone to the current distance value
        currentMilestone.setDistance(currentDistanceInt);
        //sets the milestone name to the current milestone name
        currentMilestone.setMilestoneName(currentMilestoneName);
        //puts the milestone into the temp milestone array
        tempMilestoneArray[i] = currentMilestone;
    }
    //sets numMilestones data member to the value of total milestones
    numMilestones = totalMilestones;
    //opens river file
    riverData.open(riverFile);
    //if the open fails, returns -99, prints error message
    if (riverData.fail())
    {
        cout << "The river file name passed could not be found." << endl;
        return -99;
    }
    
    //THIS OPERATES ESSENTIALLY THE SAME AS THE FORT READ EXCEPT IT SETS DEPTH TOO
    //reads all the river milestone types into the tempMilestoneArray
    for (int i = numMilestones; i < 200; i++)
    {
        if (getline(riverData, currentMilestoneName))
        {
            totalMilestones++;
        }
        getline(riverData, currentDistanceString, 'm');
        currentDistanceInt = stoi(currentDistanceString);
        getline(riverData, clearGetline, ' ');
        getline(riverData, currentDepthString, 'f');
        currentDepthInt = stoi(currentDepthString);
        getline(riverData, clearGetline);
        currentMilestone.setIsFort(false);
        currentMilestone.setDistance(currentDistanceInt);
        currentMilestone.setMilestoneName(currentMilestoneName);
        currentMilestone.setDepth(currentDepthInt);
        tempMilestoneArray[i] = currentMilestone;
    }
    numMilestones = totalMilestones;
    //represents whether the current pass swapped any values
    bool didSwap = true;
    //temporary holding spot for a milestone being swapped
    Milestone swapMilestone;
    //Keeps running passes of the sorting algorithm until no more swaps occur in the most recent pass
    while (didSwap != false)
    {
        //sets didswap to false
        didSwap = false;
        //for each index in the array besides the last, if it is further from the start than the index after it, the two get swapped in the array, if a swap occurs, didSwap = true for that pass
        for (int i = 0; i < numMilestones - 1; i++)
        if (tempMilestoneArray[i].getDistance() > tempMilestoneArray[i+1].getDistance())
        {
            swapMilestone = tempMilestoneArray[i];
            tempMilestoneArray[i] = tempMilestoneArray[i+1];
            tempMilestoneArray[i+1] = swapMilestone;
            didSwap = true;
        }
    }
    //sets the last milestone in the array to Oregon City
    Milestone lastMilestone("Oregon City", 2040, true, 0);
    tempMilestoneArray[numMilestones] = lastMilestone;
    numMilestones++;
    //sets all the values in the actual milestones array data member to the values in the temporary milestone array
    for (int i = 0; i < numMilestones; i++)
    {
        allMilestones[i] = tempMilestoneArray[i];
    }
    //returns number of milestones
    return numMilestones;
}

//advances next milestone to the next milestone in the array provided miles travelled are greater than or equal to the current milestone's mileage, and the current milestone number is less than the max value in the array
void Map::milestoneAdvance()
{
    if (milesTravelled >= allMilestones[nextMilestone].getDistance() && nextMilestone < numMilestones - 1)
    {
        nextMilestone++;
    }
}

//returns the mileage from the start of the next milestone
int Map::getNextMilestoneMileage() const
{
    return allMilestones[nextMilestone].getDistance();
}

//gets whether the next milestone is a fort
bool Map::getNextMilestoneFort() const
{
    return allMilestones[nextMilestone].getIsFort();
}

//gets the name of the next milestone
string Map::getNextMilestoneName() const
{
    return allMilestones[nextMilestone].getMilestoneName();
}

//gets the depth of the next milestone
int Map::getNextMilestoneDepth() const
{
    return allMilestones[nextMilestone].getDepth();
}

//This is a current version of the file