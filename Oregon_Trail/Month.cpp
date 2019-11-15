#include <iostream>
#include "Month.h"

using namespace std;

Month::Month()
{
    monthName = "Default Constructor Placeholder Name";
    numDays = -99;
    monthNum = -99;
}

Month::Month(string newName, int days, int monthNumber)
{
    monthName = newName;
    numDays = days;
    monthNum = monthNumber;
}

//returns the name of a month
string Month::getMonthName() const
{
    return monthName;
}

//returns the number of days in a month
int Month::getNumDays() const
{
    return numDays;
}

//returns the number of a month
int Month::getMonthNum() const
{
    return monthNum;
}

//sets a month's name to new string
void Month::setMonthName(string newName)
{
    monthName = newName;
}

//sets num days in a month to new value
void Month::setNumDays(int newNumDays)
{
    numDays = newNumDays;
}

//sets the month number to a new value
void Month::setMonthNum(int newMonthNum)
{
    monthNum = newMonthNum;
}


//This is a current version of the file