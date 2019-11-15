#include <iostream>

using namespace std;

#ifndef MONTH_H
#define MONTH_H

class Month
{
    public:
        Month();
        Month(string newName, int days, int monthNumber);
    
        //gets months name
        string getMonthName() const;
        //gets number of days in a month
        int getNumDays() const;
        //gets the month num (1-12)
        int getMonthNum() const;
    
        //sets the num days in a month
        void setNumDays(int newNumDays);
        //sets month name
        void setMonthName(string newName);
        //sets month number
        void setMonthNum(int newMonthNum);
    private:
        //month name
        string monthName;
        //number of days in a month
        int numDays;
        //number of the month (1-12)
        int monthNum;
        
};

#endif


//This is a current version of the file