#include <iostream>
#include "Month.h"

using namespace std;

#ifndef DATE_H
#define DATE_H

class Date
{
public:
    //constructors
    Date();
    Date(int day, int month, int year);
    
    //getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    
    //setters
    void setDay(int newDay);
    void setMonth(int newMonth);
    void setYear(int newYear);
    
    //increments the date by x number of days
    void incrementDate(int days);
    
private:
    //current day
    int currentDay;
    //index of the current month in the month array
    int currentMonth;
    int currentYear;
    //array of all months
    Month allMonths[12];
};

#endif


//This is a current version of the file