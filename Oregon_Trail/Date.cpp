#include <iostream>
#include "Date.h"

using namespace std;

//default constructor for date
Date::Date()
{
    //sets the current date to 3/28/1847
    currentDay = 28;
    //current month is 2 because month 3 is index 2 in the month array
    currentMonth = 2;
    currentYear = 1847;
    //array of month names
    string monthNames[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    //array of each month's number of days
    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //initializes the array of months with all 12 months and their respective data members
    for (int i = 0; i < 12; i++)
    {
        Month newMonth(monthNames[i], monthDays[i], i+1);
        allMonths[i] = newMonth;
    }
}

Date::Date(int day, int month, int year)
{
    string monthNames[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //initializes the array of months with the months and their respective data members
    for (int i = 0; i < 12; i++)
    {
        Month newMonth(monthNames[i], monthDays[i], i+1);
        allMonths[i] = newMonth;
    }
    //as long as the month passed is within the confines of the month array, index of the current month is set to the value passed for current month
    if (month >= 0 && month <= 11)
    {
        currentMonth = month;
    }
    //as long as the day number passed is within the date range of the current month, the current day is set to the day passed, else it defaults to the first day of the month
    if (day >= 1 && day <= allMonths[currentMonth].getNumDays())
    {
        currentDay = day;
    }
    else
    {
        currentDay = 1;
    }
    currentYear = 1847;
}

//returns the current day
int Date::getDay() const
{
    return currentDay;
}

//gets the month number of the current month index in the month array
int Date::getMonth() const
{
    return allMonths[currentMonth].getMonthNum();
}

//returns the current year
int Date::getYear() const
{
    return currentYear;
}

//sets the day to the day passed if it is within the date range of the current month, otherwise, date remains unchanged
void Date::setDay(int newDay)
{
    if (newDay >= 1 && newDay <= allMonths[currentMonth].getNumDays())
    {
        currentDay = newDay;
    }
}

//if the month passed is within the confines of the month array, sets current month to the new month
void Date::setMonth(int newMonth)
{
    if (newMonth >=0 && newMonth <= 11)
    {
        currentMonth = newMonth;
    }
}

//sets the year to a new year
void Date::setYear(int newYear)
{
    currentYear = newYear;
}


//increments the date the number of days passed to the function
//while the current day is less than the total number of days in the current month,
//currentDay is incremented by 1, and 1 day is subtracted from the number of days to be added to the date
//Once the end of the month is reached, the current month increases by 1 and the current day is set to 1
//Then 1 day is subtracted from the number of days to be added to the date
void Date::incrementDate(int days)
{
    //days refers to the number of days the date needs to be incremented by
    while (days > 0)
    {
        //if the current day is less than the total number of days in the current month, increments the day of the date by 1, subtracts a day from days to be incremented
        if (currentDay < allMonths[currentMonth].getNumDays())
        {
            currentDay++;
            days--;
        }
        //if the current day is the last day of the month, the current month is incremented by 1 and the day is set to 1, subtracts a day from days to be incremented
        if (currentDay == allMonths[currentMonth].getNumDays())
        {
            if (currentMonth < 11)
            {
                currentMonth++;
            }
            else
            {
                currentMonth = 0;
            }
            currentDay = 1;
            days--;
        }
    }
}


//This is a current version of the file