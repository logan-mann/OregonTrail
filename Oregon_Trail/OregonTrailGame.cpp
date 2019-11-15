//IMPORTANT: THE PROGRAM READS FORTS AND RIVERS FROM TWO SEPARATE FILES, AND WILL NOT WORK READING ALL MILESTONES FROM ONE FILE

/*
SOURCES

https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored/12658029

https://stackoverflow.com/questions/9459035/why-does-rand-yield-the-same-sequence-of-numbers-on-every-run

https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input

*/


// CS1300 Fall 2018
// Author: Logan Mann
// Recitation: 108 – IsabellaH Huang
// Cloud9 Workspace Editor Link: https://ide.c9.io/loganmann/logan_mann_csci1300
// Homework 9 - Oregon Trail


#include <iostream>
#include <ctime>
#include "Game.h"

using namespace std;

/*
 Drives the overall functionality of the game
 The main function will be very similar to the driver function in the library database program
 1. While total miles != miles required to win and the deadline hasn't been reached and a lose condition hasn't been fulfilled, stays in a loop and simply keeps executing turns
 2. Asks player what they want to do (rest, continue, hunt, etc) calls appropriate function
 3. if player chooses to quit, appropriate message printed, game loop exited
 4. checks mileage, calls milestone function if milestone is reached
 5. if not at a milestone, calcs whether a misfortune occurs, calls function as needed
 6. if not at a milestone, calc whether raid occurs, calls raid function as needed
 7. if total miles == number required to win, prints win message
 8. if game lost, prints loss message
 9. writes final stats to results.txt
 */



int main()
{
    //seeds the random number generator
    srand(static_cast<unsigned int> (time(NULL)));
    bool quitGame = false;
    cout << "~~~~~~ WELCOME TO THE OREGON TRAIL ~~~~~~" << endl;
    //initializes the game object
    Game gameInstance;
    //string for the player name
    string playerName;
    //party member 1
    string member2;
    //party member 2
    string member3;
    //party member 3
    string member4;
    //party member 4
    string member5;
    cout << "What is your name?" << endl;
    //clears out cin, takes input for player's name
    cin.clear();
    cin.ignore(100, '\n');
    getline(cin, playerName);
    cout << "Hi, " << playerName << " who else will be joining you on your journey?" << endl << "Party member 2: " << endl;
    //does the same for all other party members
    getline(cin, member2);
    cout << "Member 3: " << endl;
    getline(cin, member3);
    cout << "Member 4: " << endl;
    getline(cin, member4);
    cout << "Member 5: " << endl;
    getline(cin, member5);
    //creates the party according to the names passed
    gameInstance.createParty(playerName, member2, member3, member4, member5);
    cout << endl << "Before you begin your journey, you have the opportunity to visit the shop." << endl << "You had saved $1200 for the trip, and you've just paid $200 for a wagon." << endl << "You will need to spend the rest of your money on the following items: " << endl << " - Oxen. The more you have in your team to start, the more likely you will be able to reach your goal." << endl << " - Food. The more you have, the less chance there is of starving to death along the trail." << endl << " - Ammunition. You will need bullets for hunting and fending off raiders along your journey." << endl << " - Wagon Parts and Medical Kits. These will help heal you or repair your wagon should your wagon break or your party become ill." << endl << "You can spend all your money before the start of the trip, or you can save some to spend at forst along the way, however, items cost more at forts." << endl << "You can also hunt along the way to get more food." << endl;
    //calls the store action
    gameInstance.storeAction();
    //keeps running turns until a loss or win condition is fulfilled
    while (gameInstance.dateOk() == true && gameInstance.wagonWorks() == true && gameInstance.haveFood() == true && gameInstance.leaderAlive() == true && gameInstance.haveOxen() == true && gameInstance.journeyComplete() == false && quitGame == false)
    {
        //prints status update
        cout << endl << "~~~~~~ STATUS ~~~~~~" << endl;
        gameInstance.statusUpdate();
        cout << endl << "What would you like to do?" << endl << "1. Rest" << endl << "2. Continue on trail" << endl << "3. Hunt" << endl << "4. Quit Game" << endl;
        int turnChoice;
        //takes input for the players decision for this turn
        cin >> turnChoice;
        //prints error and retakes player input if the input entered is invalid
        while (turnChoice != 1 && turnChoice != 2 && turnChoice != 3 && turnChoice != 4)
        {
            cout << "Invalid choice. Please enter a valid option." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            cin >> turnChoice;
        }
        //case 1: runs rest action, case 2: runs continue on trail action, case 3: runs hunting action, case 4: runs quitting action
        switch (turnChoice) {
            case 1:
                gameInstance.restingAction();
                break;
            case 2:
                gameInstance.continueOnTrail();
                break;
            case 3:
                gameInstance.huntingAction();
                break;
            case 4:
                cout << endl << endl <<"~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "         Quit         " << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                cout << "You've come so far! Are you sure you want to end your journey here?" << endl;
                //asks player if they're sure they want to quit
                cout << "1. Yes" << endl << "2. No" << endl;
                int quitChoice;
                cin >> quitChoice;
                //retakes input while the input entered is invalid
                while (quitChoice != 1 && quitChoice != 2)
                {
                    cout << endl << "Please enter a valid option." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> quitChoice;
                }
                //if the quit choice is still yes, sets quit game to true
                if (quitChoice == 1)
                {
                    cout << endl << "Sorry you had to end your trip! See you again soon!" << endl << endl;
                    quitGame = true;
                }
            default:
                break;
        }
        //performs the random occurences and milestone activities provided the game isn't won or lost during travel/rest/hunt portion of the turn
        if (gameInstance.dateOk() == true && gameInstance.wagonWorks() == true && gameInstance.haveFood() == true && gameInstance.leaderAlive() == true && gameInstance.haveOxen() == true && gameInstance.journeyComplete() == false && quitGame == false)
        {
            if(gameInstance.getNextMilestoneMileage() != 2040)
            {
                gameInstance.atMilestone();
            }
            if (gameInstance.getMilesTravelled() != gameInstance.getNextMilestoneMileage())
            {
                gameInstance.randomEventOccur();
                gameInstance.raiderAttack();
            }
            gameInstance.updateMilestone();
        }
    }
    //if the while loop is exited due to the journey being complete, win message is printed, stats are printed and written to file
    if (gameInstance.journeyComplete() == true)
    {
        cout << "Congratulations! You braved the Oregon Trail and have arrived in Oregon City!" << endl;
        cout << endl << "~~~~~~~~   YOU WIN!   ~~~~~~~~" << endl;
        gameInstance.writeGameStats();
        return 0;
    }
    //if a loss condition is fulfilled and the goal wasn't reached, loss message printed and stats printed/written to file
    else
    {
        if (quitGame != true)
        {
            cout << endl << "YOU HAVE DIED OF DYSENTERY!" << endl;
            cout << endl << "~~~~~~~~   GAME OVER!   ~~~~~~~~" << endl;
        }
        gameInstance.writeGameStats();
        return 0;
    }
    
}



//This is a current version of the file
