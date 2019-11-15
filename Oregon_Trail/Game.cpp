#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include "Game.h"

using namespace std;

//determines whether an event w/ a given probability occurs
bool eventOccured(int percentChance)
{
    //generates a random number between 0 and 100, if it is less than the % value passed, returns true
    bool occured = ((rand() % 100) < percentChance);
    return occured;
}


//returns true if the player solved the puzzle, false if failed
bool Game::puzzle()
{
    //generates a random number from 1 to 10
    int number = (rand()%(9)) + 1;
    cout << "You have 3 chances to guess the correct number between 1 and 10. If you guess the correct number, you succeed." << endl;
    int guess = -1;
    int guessCount = 0;
    //lets the player keep guessing until 3 guesses are made or the number is guessed
    while (guessCount < 3 && guess != number)
    {
        cout << "Guess a number between 1 and 10" << endl;
        cin >> guess;
        //takes input while the input is invalid
        while (cin.fail() || (guess < 1 && guess > 10))
        {
            cout << "Invalid input, please guess a number between 1 and 10" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            cin >> guess;
        }
        //if the guess isn't the number, prints message
        if (guess != number)
        {
            cout << "Wrong number!" << endl;
        }
        //increments guess count
        guessCount++;
    }
    //at the end of the loop, if the guess is the number, returns true, if not false
    if (guess == number)
    {
        return true;
    }
    return false;
}

Game::Game()
{
    //new supply object
    Supply newSupplies;
    supplies = newSupplies;
    //asks when the player wants to start date
    cout << "Do you want to start your journey on:" << endl << "1. The default date of 03/28/1847" << endl << "2. A different date between 03/01/1847 and 05/01/1847" << endl << "Keep in mind, the later you start, the harder it will be to reach Oregon City in time." << endl;
    int dateChoice;
    //takes input until the input entered is valid
    cin >> dateChoice;
    while (dateChoice != 1 && dateChoice != 2)
    {
        cout << "That option was not valid. Please select a valid choice." << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cin >> dateChoice;
    }
    //new date object w/ default starting date
    Date newDate;
    //if the player chooses a custom date, sets the day, month, etc to the date they enter, makes sure it is in the range of valid starting dates
    if (dateChoice == 2)
    {
        cout << "Ok. What date would you like to start on?" << endl << "Month: " << endl;
        int monthChoice;
        cin >> monthChoice;
        while (monthChoice != 3 && monthChoice != 4 && monthChoice != 5)
        {
            cout << "That is not a valid starting month. Please enter either 3, 4, or 5 for the starting month." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            cin >> monthChoice;
        }
        cout << "Great!, what day would you like to start on?" << endl << "Day: " << endl;
        int dayChoice;
        cin >> dayChoice;
        while (((monthChoice == 3 || monthChoice == 5)&& (dayChoice < 1 || dayChoice > 31)) || (monthChoice == 4 && (dayChoice < 1 || dayChoice > 30)))
        {
            cout << "That is not a valid starting day for the month you selected. Please choose a valid date within your starting month (i.e. 1-31 for month 3)" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            cin >> dayChoice;
        }
        newDate.setMonth(monthChoice - 1);
        newDate.setDay(dayChoice);
    }
    //sets the current date
    currentDate = newDate;
    
    //makes placeholder person object
    Person placeHolderPerson;
    
    //initializes the party array
    for (int i = 0; i < 5; i++)
    {
        partyMembers[i] = placeHolderPerson;
    }
    
    Map newMap;
    newMap.readMilestones("fort-milestones.txt", "river-milestones.txt");
    gameMap = newMap;
    
    Store newStore;
    store = newStore;
}

//creates the party according to the names of the party members passed
void Game::createParty(string playerName, string person2, string person3, string person4, string person5)
{
    Person player(playerName);
    Person member2(person2);
    Person member3(person3);
    Person member4(person4);
    Person member5(person5);
    
    partyMembers[0] = player;
    partyMembers[1] = member2;
    partyMembers[2] = member3;
    partyMembers[3] = member4;
    partyMembers[4] = member5;
}

int Game::getMembersAlive() const
{
    //increments members alive for each party member who has true alive status, then returns the number of party members alive
    int membersAlive = 0;
    for (int i = 0; i < 5; i++)
    {
        if (partyMembers[i].getAlive() == true)
        {
            membersAlive++;
        }
    }
    return membersAlive;
}

//advances the date by the number of days passed
void Game::dateAdvancer(int days)
{
    currentDate.incrementDate(days);
}

//updates the next milestone accordingly
void Game::updateMilestone()
{
    gameMap.milestoneAdvance();
}

/*
    Handles shop interactions throughout the game
    1. variables made for total money spent and amount bought for each item
    2. Displays pricing information for all supplies
    3. Asks user what item they want to buy and what quantity
    4. updates variables, prints total bill
    5. repeats above until player exits shop
    6. updates player's supplies and money according to the amount bought
 */
void Game::storeAction()
{
    double moneySpent = 0;
    int oxenBought = 0;
    int foodBought = 0;
    int bulletsBought = 0;
    int partsBought = 0;
    int medsBought = 0;
    int choice = -1;
    int amountBought;
    while (choice != 7)
    {
        cout << endl;
        cout << "Total bill so far: $" << moneySpent << endl;
        cout << "Oxen bought: " << oxenBought << " Yoke, (" << oxenBought * 2 << " Oxen Total)" << endl;
        cout << "Food Bought: " << foodBought << " lbs" << endl;
        cout << "Bullets Bought: " << bulletsBought << " Cases of 20 Bullets Each" << endl;
        cout << "Wagon Parts Bought: " << partsBought << endl;
        cout << "Medical Kits Bought: " << medsBought << endl;
        cout << "You can afford to buy $" << supplies.getMoney() - moneySpent << " more of supplies." << endl << endl;
        cout << "What would you like to purchase?" << endl << "1. Yoke of oxen: $" << store.getOxenPrice() << " per yoke." << endl << "2. Food: $" << store.getFoodPrice() << " per pound." << endl << "3. Bullets: $" << store.getBulletsPrice() << " per 20 bullets." << endl << "4. Wagon Parts: $" << store.getPartsPrice() << " per part" << endl << "5. Medical Kits: $" << store.getMedKitPrice() << " per medical Kit" << endl << "6. Clear your bill and restart the transaction." << endl << "7. Pay and exit shop" << endl << endl;
        cin >> choice;
        switch (choice) {
            case 1 :
                BUY_OXEN:
                cout << "How many yoke would you like to buy? Enter 0 if you don't want to buy any." << endl;
                cin >> amountBought;
                if (cin.fail())
                {
                    cout << "Invalid input. Enter an integer amount you would like to purchase." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_OXEN;
                }
                //if the player is at the first store and they try to buy more than $200 worth of oxen, it doesn't let them
                while (store.getStoreNumber() == 0 && (store.getOxenPrice()* (amountBought+oxenBought) > 200))
                {
                    cout << "You must spend between $100 and $200 on your initial oxen team. (If you have already bought $200 worth of oxen, enter 0 to go back to the shop menu)" << endl;
                    cin.clear();
                    cin.ignore(100,'\n');
                    cin >> amountBought;
                }
                //if they try to buy more than they can pay for, error printed, asks for new amount
                if (moneySpent + (store.getOxenPrice() * amountBought) > supplies.getMoney())
                {
                    cout << "You can't afford that, enter a new amount." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_OXEN;
                }
                //if it is a negative value, error printed, takes new input
                if (amountBought < 0)
                {
                    cout << "That is an invalid amount, enter a new amount." << endl;
                    cin.clear();
                    cin.ignore(100,'\n');
                    goto BUY_OXEN;
                }
                //adds to total oxen bought
                oxenBought = oxenBought + amountBought;
                moneySpent = moneySpent + (store.getOxenPrice() * amountBought);
                break;
            case 2 :
                BUY_FOOD:
                //prints reccommended amount of food at the first store
                if (store.getStoreNumber() == 0)
                {
                    cout << "To start out, I reccommend you buy at least 200 lbs of food." << endl << endl;
                }
                cout << "How many pounds of food would you like to buy? Enter 0 if you don't want to buy any." << endl;
                cin >> amountBought;
                //error messages and new input requests if input fails, can't afford, etc.
                if (cin.fail())
                {
                    cout << "Invalid input. Enter an integer amount you would like to purchase." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_FOOD;
                }
                if (moneySpent + (store.getFoodPrice() * amountBought) > supplies.getMoney())
                {
                    cout << "You can't afford that, enter a new amount." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_FOOD;
                }
                if (amountBought < 0)
                {
                    cout << "That is an invalid amount, enter a new amount." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_FOOD;
                }
                //if they try to buy more than the wagon can hold, error prints, goes back to main shop menu
                if (amountBought + foodBought + supplies.getFood() > 1000)
                {
                    cout << "Your wagon can only hold 1000 lbs of food. You requested to buy more than you could hold." << endl;
                    break;
                }
                //adds amount bought to total food bought, adds amount spent on the items to the total bill
                foodBought = foodBought + amountBought;
                moneySpent = moneySpent + (store.getFoodPrice() * amountBought);
                break;
            case 3 :
                BUY_BULLETS:
                cout << "How many cases of 20 bullets would you like to buy? Enter 0 if you don't want to buy any." << endl;
                cin >> amountBought;
                //error messages and new input requests if input fails, can't afford, etc.
                if (cin.fail())
                {
                    cout << "Invalid input. Enter an integer amount you would like to purchase." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_BULLETS;
                }
                if (moneySpent + (store.getBulletsPrice() * amountBought) > supplies.getMoney())
                {
                    cout << "You can't afford that, enter a new amount." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_BULLETS;
                }
                if (amountBought < 0)
                {
                    cout << "That is an invalid amount, enter a new amount." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_FOOD;
                }
                bulletsBought = bulletsBought + amountBought;
                moneySpent = moneySpent + (store.getBulletsPrice() * amountBought);
                break;
            case 4 :
                BUY_PARTS:
                cout << "How many parts would you like to buy? Enter 0 if you don't want to buy any." << endl;
                cin >> amountBought;
                //error messages and new input requests if input fails, can't afford, etc.
                if (cin.fail())
                {
                    cout << "Invalid input. Enter an integer amount you would like to purchase." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_PARTS;
                }
                if (moneySpent + (store.getPartsPrice() * amountBought) > supplies.getMoney())
                {
                    cout << "You can't afford that, enter a new amount." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_PARTS;
                }
                if (amountBought < 0)
                {
                    cout << "That is an invalid amount, enter a new amount." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_PARTS;
                }
                //adds amount purchased and money spent to totals
                partsBought = partsBought + amountBought;
                moneySpent = moneySpent + (store.getPartsPrice() * amountBought);
                break;
            case 5 :
                BUY_MEDS:
                cout << "How many medical kits would you like to buy? Enter 0 if you don't want to buy any." << endl;
                cin >> amountBought;
                //error messages and new input requests if input fails, can't afford, etc.
                if (cin.fail())
                {
                    cout << "Invalid input. Enter an integer amount you would like to purchase." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_MEDS;
                }
                if (moneySpent + (store.getMedKitPrice() * amountBought) > supplies.getMoney())
                {
                    cout << "You can't afford that, enter a new amount." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_MEDS;
                }
                if (amountBought < 0)
                {
                    cout << "That is an invalid amount, enter a new amount." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto BUY_MEDS;
                }
                //updates totals bought and spent
                medsBought = medsBought + amountBought;
                moneySpent = moneySpent + (store.getMedKitPrice() * amountBought);
                break;
            case 6 :
                //case 6 resets the totals spent/bought
                moneySpent = 0;
                oxenBought = 0;
                foodBought = 0;
                bulletsBought = 0;
                partsBought = 0;
                medsBought = 0;
                break;
            case 7:
                //if the player tries to leave the first store without any food or enough oxen, it sends them back to the shop menu
                if (store.getStoreNumber() == 0 && foodBought + supplies.getFood() == 0 && supplies.getOxen() + oxenBought < 2.5)
                {
                    cout << "You can't start your journey without at least $100 of oxen and enough food! How do you expect to travel the trail?" << endl << "Buy some food and oxen before you leave." << endl;
                    choice = 0;
                }
                else if (store.getStoreNumber() == 0 && supplies.getOxen() + oxenBought >= 2.5 && foodBought + supplies.getFood() == 0)
                {
                    cout << "You can't start your journey without food! You'll starve before you make any progress! Buy some food before you leave." << endl;
                    choice = 0;
                }
                else if (store.getStoreNumber() == 0 && supplies.getOxen() + oxenBought < 2.5 && foodBought + supplies.getFood() > 0)
                {
                    cout << "You can't start your journey without at least $100 of oxen! How do you expect to pull your wagon? Buy at least $100 worth of oxen before you leave." << endl;
                    choice = 0;
                }
                break;
            default:
                //defaults to invalid choice, goes back to main shop menu
                cout << "Invalid choice. Please reenter a valid selection." << endl;
                cin.clear();
                cin.ignore(100, '\n');
                choice = -99;
                break;
        }
    }
    //once the player exits the shop, updates supply totals based on supplies bought/money spent
    //subtracts amount spent
    supplies.addMoney((moneySpent * -1));
    //adds 2 oxen for each yoke bought
    supplies.addOxen(oxenBought * 2);
    supplies.addFood(foodBought);
    //adds 20 bullets per case
    supplies.addBullets(bulletsBought * 20);
    supplies.addParts(partsBought);
    supplies.addMeds(medsBought);
    cout << "Thank you for your purchase! Come again!" << endl;
    //if the player is at the first store, prices are increased after leaving the store
    if (store.getStoreNumber() == 0)
    {
        store.increasePrices();
    }
}
/*
    Handles hunting activity
    1. Figures out whether the player encounters each animal, prints appropriate messages
    For each animal encountered:
    2. asks player if they want to hunt
    3. checks bullet count, either fails the hunt or calls a puzzle
    4. if the puzzle is solved, the hunt is successful
    5. updates bullets and food as apppropriate
 */
void Game::huntingAction()
{
    //This is an array of whether or not the player encounters each animal
    bool encounterAnimal[5] = {eventOccured(50), eventOccured(25), eventOccured(15), eventOccured(7), eventOccured(5)};
    //Names of all animals
    string animalNames[5] = {"rabbit", "fox", "deer", "bear", "moose"};
    //Determines pounds of food gained from each animal
    int foodGained[5] = {2, 5, (rand()%(55-35) + 35), (rand()%(350-100) + 100), (rand()%(600-300) + 300)};
    //Bullets needed for each animal
    int bulletsNeeded[5] = {10, 8, 5, 10, 12};
    //Variable representing the player's decision to hunt an animal or not
    int huntChoice = 0;
    //represents the number of animals the player encounters
    int animalsEncountered = 0;
    //for each animal, if the animal has been encountered, lets the player try and hunt it
    for (int i = 0; i < 5; i++)
    {
        if (encounterAnimal[i] == true)
        {
            animalsEncountered++;
            cout << "You got lucky! You encountered a " << animalNames[i] << "! Do you want to hunt: 1. Yes, 2. No" << endl;
            cin >> huntChoice;
            //retakes input until valid
            while (huntChoice != 1 && huntChoice != 2)
            {
                cout << "Invalid input, please enter a valid choice" << endl;
                cin.clear();
                cin.ignore(100, '\n');
                cin >> huntChoice;
            }
            //if the player chooses to hunt, if they have enough bullets, runs a puzzle
            if (huntChoice == 1)
            {
                if (supplies.getBullets() >= bulletsNeeded[i])
                {
                    cout << "You will have to solve a puzzle to determine whether the hunt was successful." << endl;
                    bool huntSucceed = Game::puzzle();
                    //if the puzzle is solved, updates food & bullet total
                    if (huntSucceed == true)
                    {
                        cout << "You successfully hunted the " << animalNames[i] << "!" << endl;
                        //if food + the food gained is less than 1000, adds food gained to food total
                        if (foodGained[i] + supplies.getFood() <= 1000)
                        {
                            supplies.addFood(foodGained[i]);
                        }
                        //otherwise, notifies the player they had to leave food behind and sets food to 1000
                        else
                        {
                            cout << "Your wagon can only hold 1000 lbs of food, so you had to leave some behind." << endl;
                            supplies.setFood(1000);
                        }
                        //subtracts the bullets needed from bullet total
                        supplies.addBullets(bulletsNeeded[i] * -1);
                    }
                    //if the hunt fails, notifies the player
                    else if (huntSucceed == false)
                    {
                        cout << "Sorry, you failed to hunt the " << animalNames[i] << "." << endl;
                    }
                }
                //if they don't have enough bullets, notifies the player
                else if (supplies.getBullets() < bulletsNeeded[i])
                {
                    cout << "You don't have enought bullets to hunt the " << animalNames[i] << "." << endl;
                }
            }
            //prints message if the player chooses not to hunt the animal
            else if (huntChoice == 2)
            {
                cout << "You choose not to hunt the " << animalNames[i] << endl;
            }
            
        }
    }
    //prints a notification if no animals are found, asks how well they want to eat
    if (animalsEncountered == 0)
    {
        cout << endl << "Unfortunately, you scoured the forest all day, but couldn't find any game before dark." << endl;
        cout << endl << "How well do you want to eat tonight?" << endl << "1. Poorly, 2 lbs per person" << endl << "2. Moderately, 3 lbs per person" << endl << "3. Well, 5 lbs per person" << endl;
    }
    else
    {
        cout << endl << "How well do you want to eat tonight?" << endl << "1. Poorly, 2 lbs per person" << endl << "2. Moderately, 3 lbs per person" << endl << "3. Well, 5 lbs per person" << endl;
    }
    int eatingChoice;
    //takes input until valid
    cin >> eatingChoice;
    while (eatingChoice != 1 && eatingChoice != 2 && eatingChoice != 3)
    {
        cout << "Invalid choice. Please reenter a valid choice." << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cin >> eatingChoice;
    }
    //updates food totals based on how well they choose to eat and how many party members are alive
    switch (eatingChoice) {
        case 1:
            supplies.addFood(-1 * 2 * getMembersAlive());
            break;
        case 2:
            supplies.addFood(-1 * 3 * getMembersAlive());
            break;
        case 3:
            supplies.addFood(-1 * 5 * getMembersAlive());
        default:
            break;
    }
}

/*
    Handles resting
    1. when the player chooses to read, advances the date by a random number of days 1-3
    2. subtracts 3 lbs of food per person from total food for each day rested
 */
void Game::restingAction()
{
    int restingChoice;
    cout << "How long would you like to rest for?" << endl << "1. 1 day" << endl << "2. 2 days" << endl << "3. 3 days" << endl << "Note: You will consume 3lbs of food per person for each day you rest." << endl;
    cin >> restingChoice;
    while (restingChoice != 1 && restingChoice != 2 && restingChoice != 3)
    {
        cout << "That is not a valid choice. Please reenter a valid choice." << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cin >> restingChoice;
    }
    //updates food totals based on days rested and members alive, increments date accordingly
    switch (restingChoice) {
        case 1:
            currentDate.incrementDate(1);
            supplies.addFood(-1 * 3 * getMembersAlive());
            break;
        case 2:
            currentDate.incrementDate(2);
            supplies.addFood(-1 * 3 * getMembersAlive() * 2);
            break;
        case 3:
            currentDate.incrementDate(3);
            supplies.addFood(-1 * 3 * getMembersAlive() * 3);
            break;
        default:
            break;
    }
}

/*
    Handles continuing on the trail
    1. advances the date by 2 weeks (14 days)
    2. subtracts 3 lbs of food per person per day travelled
    3. updates miles travelled by a value between 70 and 140 miles
 */
void Game::continueOnTrail()
{
    //increments date by 14 days
    currentDate.incrementDate(14);
    //subtracts 3lbs of food per person alive per day
    supplies.addFood(-1 * 3 * getMembersAlive() * 14);
    //Number of miles travelled in this turn
    int turnMilesTravelled = ((rand() % (140-70 + 1)) + 70);
    //adds miles travelled in the turn to total miles
    gameMap.addMilesTravelled(turnMilesTravelled);
}

/*
    Handles random events
    1. chooses a random int between 1 and 3 to designate a random event occuring
    2. if a party member gets sick, prints appropriate message, gives player the option of how to handle it
        - if player uses a med kit, updates total medkits, calculates whether the party member lives (50% chance of death)
        - if the player chooses to rest, updates date accordingly, calcs whether party member lives (30% chance of death)
        - if the player chooses to keep going, calcs whether the party member dies (70% chance of death)
    3. if an oxen dies, prints appropriate message, updates oxen total
    4. if a wagon part breaks, prints message, updates wagon supplies or ends game as appropriate
 */
void Game::randomEventOccur()
{
    //bool that states whether a random event occurred or not
    bool eventOccur = eventOccured(40);
    //integer value of the event (1-5)
    int event = 0;
    //string array of possible disease names
    string diseaseNames[6] = {"typhoid", "cholera", "diarrhea", "the measles", "dysentery", "a fever"};
    //selects an event number 1-5
    event = ((rand() % (5-1 + 1)) + 1);
    //bool that states whether a person dies or not
    bool death;
    //if event occurs, runs the correct event based on the random event number selected
    if (eventOccur == true && gameMap.getMilesTravelled() != gameMap.getNextMilestoneMileage())
    {
    switch (event) {
        case 1:{
            //index of the disease caught in the diseaseNames array
            int diseaseCaught = ((rand() % (6-1+1)) + 1);
            //refers to the index of the diseased party member in the partyMembers array
            int diseasedMember = ((rand() % (5-1+1)) + 1);
            //keeps picking a new party member until the one chosen is currently alive
            while (partyMembers[diseasedMember - 1].getAlive() == false)
            {
                diseasedMember = ((rand() % (5-1+1)) + 1);
            }
            //prints message
            cout << "Oh no! " << partyMembers[diseasedMember - 1].getName() << " has " << diseaseNames[diseaseCaught - 1] << endl;
            //if they have a med kit, it is used
            if (supplies.getMeds() > 0)
            {
                supplies.addMeds(-1);
                //determines whether the person dies
                death = eventOccured(50);
                //if death occurs, sets the persons alive status to false, prints message
                if (death == true)
                {
                    partyMembers[diseasedMember - 1].setAlive(false);
                    cout << "You used one of your medical kits on " << partyMembers[diseasedMember - 1].getName() << " but it was uneffective. " << partyMembers[diseasedMember - 1].getName() << " has died." << endl;
                }
                //prints success message if the player lives
                else
                {
                    cout << "You used a medical kit and it worked! " << partyMembers[diseasedMember - 1].getName() << " has been cured of " << diseaseNames[diseaseCaught - 1] << "!" << endl;
                }
            }
            //if the player doesn't have a medkit, asks what they want to do
            else
            {
                cout << "You do not have a medical kit to use. Would you like to: " << endl << "1. Rest" << endl << "2. Press on?" << endl;
                int optionChoice;
                //takes input until valid
                cin >> optionChoice;
                while (optionChoice != 1 && optionChoice != 2)
                {
                    cout << "That is not a valid option. Please reenter a valid choice." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> optionChoice;
                }
                switch (optionChoice) {
                    case 1:
                        //if player chooses to rest, increments date, determines if player lives, subtracts food from total for the days rested
                        currentDate.incrementDate(3);
                        supplies.addFood(-1 * 3 * getMembersAlive() * 3);
                        death = eventOccured(30);
                        //prints message according to whether or not the party member dies, updates alive status.
                        if (death == true)
                        {
                            partyMembers[diseasedMember - 1].setAlive(false);
                            cout << partyMembers[diseasedMember - 1].getName() << " has died." << endl;
                        }
                        else
                        {
                            cout << partyMembers[diseasedMember -1].getName() << " has been cured of " << diseaseNames[diseaseCaught - 1] << "!" << endl;
                        }
                        break;
                    case 2:
                        //if player presses on, determines death occurence, updates alive status accordingly and prints message
                        death = eventOccured(70);
                        if (death == true)
                        {
                            partyMembers[diseasedMember - 1].setAlive(false);
                            cout << partyMembers[diseasedMember - 1].getName() << " has died." << endl;
                        }
                        else
                        {
                            cout << partyMembers[diseasedMember - 1].getName() << " has been cured of " << diseaseNames[diseaseCaught -1 ] << "!" << endl;
                        }
                        break;
                    default:
                        break;
                }
            }
            break;
        }
        case 2:{
            //if oxen dies, subtracts an oxen from the total oxen, prints message
            supplies.addOxen(-1);
            cout << "One of the oxen has died! You have " << supplies.getOxen() << " left." << endl;
            break;
        }
        case 3:{
            //array of possible part names
            string partNames[3] = {"wheels", "axles", "tongues"};
            //selects an integer of the broken part from 1 - 3
            int brokenPart = ((rand() % (3-1+1)) + 1);
            //prints out a message with the index of the part chosen in the array
            cout << "Oh no! One of your " << partNames[brokenPart-1] << " is broken!" << endl;
            //if the party has parts, prints a message
            if (supplies.getParts() > 0)
            {
                cout << endl << "You replace it with one of your spares and continue on the trail." << endl;
            }
            //Once the total amount of wagon parts reaches -1, the journey is over, because at this point the wagon is broken and there are no remaining parts to fix it with, so a part is subtracted whether they have any or not
            supplies.addParts(-1);
            break;
        }
        case 4:{
            //food found = random value between 75 and 5
            int foodFound = ((rand() % (75 - 5 + 1)) + 1);
            //bullets found is a random value between 2 and 35
            int bulletsFound = ((rand() % (35 - 2 + 1)) + 1);
            cout << "Your party finds an abandoned stage coach on the side of the trail. In the storage compartment you find " << foodFound << " pounds of food and " << bulletsFound << " bullets." << endl;
            //updates food and bullet totals accordingly
            if (foodFound + supplies.getFood() <= 1000)
            {
                supplies.addFood(foodFound);
            }
            else
            {
                cout << "Your wagon can only hold 1000 lbs of food, so you had to leave some behind." << endl;
                supplies.setFood(1000);
            }
            supplies.addBullets(bulletsFound);
            break;
        }
        case 5:{
            //if a man is found who needs help, if the player has meds, asks if they want to help
            cout << "You encounter a stranger and his young son on the side of the road. The stranger informs you that his son is gravely ill and asks if you have a medical kit to spare. He says he will make it worth your while." << endl;
            if (supplies.getMeds() < 1)
            {
                cout << "Unfortunately, you have no medical kits left yourself. With a heavy heart you tell the man you are unable to help." << endl;
            }
            else
            {
                cout << "You have " << supplies.getMeds() << " remaining. Do you want to give one to him? 1. Yes, 2. No" << endl;
                int medKitChoice;
                //takes input until valid
                cin >> medKitChoice;
                while (medKitChoice != 1 && medKitChoice != 2)
                {
                    cout << "That is not a valid choice. Please reenter a valid option." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> medKitChoice;
                }
                switch (medKitChoice) {
                    case 1:{
                        //if the player helps, gets to choose some supplies, updates totals accordingly
                        cout << "The man thanks you greatly for your generosity. He says you can take some food, bullets, or a wagon part from his provisions. What will you take?" << endl << "1. 50 lbs of food" << endl << "2. 15 bullets" << endl << "3. A wagon part" << endl;
                        int supplyChoice;
                        cin >> supplyChoice;
                        while (supplyChoice != 1 && supplyChoice != 2 && supplyChoice != 3)
                        {
                            cout << "That is not a valid choice. Please reenter a valid option" << endl;
                            cin.clear();
                            cin.ignore(100, '\n');
                            cin >> supplyChoice;
                        }
                        switch (supplyChoice) {
                            case 1:{
                                if (supplies.getFood() + 50 <= 1000)
                                {
                                    supplies.addFood(50);
                                }
                                else
                                {
                                    supplies.setFood(1000);
                                }
                                cout << "You take some food and continue on your way." << endl;
                                break;
                            }
                            case 2:
                            {
                                supplies.addBullets(15);
                                cout << "You take some bullets and continue on your way." << endl;
                                break;
                            }
                            case 3:{
                                supplies.addParts(1);
                                cout << "You take a wagon part and continue on your way." << endl;
                                break;
                            }
                            default:
                                break;
                        }
                        supplies.addMeds(-1);
                        break;
                    }
                    case 2:
                    {
                        cout << "You apologize to the man and say that you have no medical kits to spare. You wish him and his son luck and continue on your way." << endl;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        default:
            break;
    }
    }
}

/*
    Handles raider attacks
    1. asks player how to handle the attack
    2. if run: updates supplies as appropriate
    3. if attack: calls a puzzle, updates supplies according to pass or fail the puzzle
 4. if surrender: update the total money
 */
//THIS WILL BE CALLED AT THE END OF EVERY TURN, WILL DETERMINE WHETHER AN ATTACK OCCURS INSIDE THIS FUNCTION
void Game::raiderAttack()
{
    //int for miles travelled
    int mileage = gameMap.getMilesTravelled();
    //calculates probability of raider attack
    int raiderProbability = ((((pow(((mileage/100) - 4), 2) + 72) / (pow(((mileage/100) - 4), 2) + 12)) - 1)/10) * 100;
    //bool for whether or not the attack occurs
    bool attackOccured = eventOccured(raiderProbability);
    //if the attack occurs, asks player what they want to do
    if (attackOccured == true && gameMap.getMilesTravelled() != gameMap.getNextMilestoneMileage())
    {
        cout << "Raiders ahead! They look hostile!" << endl;
        cout << "Do you want to: " << endl << "1. Run" << endl << "2. Attack" << endl << "3. Surrender" << endl;
        int raidChoice;
        //takes input until valid
        cin >> raidChoice;
        while (raidChoice != 1 && raidChoice != 2 && raidChoice != 3)
        {
            cout << "That is not a valid option. Please reenter a valid choice." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            cin >> raidChoice;
        }
        switch (raidChoice) {
            case 1:{
                //if run, updates supplies and prints message
                cout << "Your party manages to escape in one piece, but in the all the commotion, you left behind an ox, 10 lbs of food, and a wagon part." << endl;
                supplies.addFood(-10);
                if (supplies.getParts() > 0)
                {
                  supplies.addParts(-1);  
                }
                supplies.addOxen(-1);
                break;
            }
            case 2:{
                //if attack, has to solve a puzzle, updates supply totals based on win or lose
                cout << "In order to successfully defeat the raiders, you must solve a puzzle." << endl;
                bool defeatRaiders = Game::puzzle();
                if (defeatRaiders == true)
                {
                    cout << "You successfully defeated the raiders! You loot their wagons and find 50 lbs of food and 50 bullets!" << endl;
                    supplies.addFood(50);
                    supplies.addBullets(50);
                }
                else
                {
                    cout << "You failed to fend off the raiders, and were robbed. You have lost 25% of your cash and 50 bullets." << endl;
                    if(supplies.getBullets() >= 50)
                    {
                        supplies.addBullets(-50);
                    }
                    else
                    {
                        supplies.setBullets(0);
                    }
                    supplies.setMoney(supplies.getMoney() * 0.75);
                }
                break;
            }
            case 3:{
                //updates money if surrender
                cout << "You surrender to the raiders, and they steal a quarter of your cash." << endl;
                supplies.setMoney(supplies.getMoney() * 0.75);
                break;
            }
            default:
                break;
        }
    }
}

//NEXT TWO FUNCTIONS HANDLE GRAPHICS FOR FORT SIGNS
/* end result looks like this, with the fort name being a string passed to the function
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 |                                      |
 |               Welcome                |
 |                                      |
 |                  To                  |
 |                                      |
 |             Fort Funston             |
 |                                      |
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 */
void printSignLine(string text)
{
   cout << "|";
    //if string passed is even in length
   if(text.length() % 2 == 0)
   {
       //prints spaces for half of the sign length - the string in the sign length
        for (int i = 0; i < (38 - text.length()) / 2; i++)
        {
            cout << " ";
        }
        cout << text;
       //prints rest of spaces
        for (int i = 0; i < (38 - text.length()) / 2; i++)
        { 
            cout << " ";
        }
        cout << "|" << endl;
   }
    //if string passed is odd in length
   else
   {
       //prints part of spaces on one side, rest on the other side of the string
       for (int i = 0; i < (38 - text.length()) / 2; i++)
        {
            cout << " ";
        }
        cout << text;
        for (int i = 0; i < (38 - text.length()) / 2 + 1; i++)
        { 
            cout << " ";
        }
        cout << "|" << endl; 
   }
}
//prints the lines of the sign in order
void Game::printFortSign() const
{
    cout << endl << endl << endl;
    for (int i = 0; i < 39; i++)
    {
        cout << "~";
    }
    cout << endl;
    printSignLine("");
    printSignLine("Welcome");
    printSignLine("");
    printSignLine("To");
    printSignLine("");
    //prints line with name of next milestone
    printSignLine(gameMap.getNextMilestoneName());
    printSignLine("");
    for (int i = 0; i < 40; i++)
    {
        cout << "~";
    }
    cout << endl;
}

/*
 Handles events that occur at milestones
 1. checks if current milestone is a fort or river
 2. if fort: lets player rest, visit store, or continue journey
 - calls store/rest/continue function as appropriate
 3. if river: lets player rest or cross river
 - if river deeper than 3 ft, requires ferry, takes $10 off total money
 - calls rest function as appropriate
 
 */
void Game::atMilestone()
{
    //if the player is at a milestone
    if (gameMap.getMilesTravelled() == gameMap.getNextMilestoneMileage())
    {
        //if the player is at a fort
        if (gameMap.getNextMilestoneFort() == true)
        {
            int fortChoice = 0;
            //prints the fort sign
            printFortSign();
            cout << "You have reached " << gameMap.getNextMilestoneName() << ". What do you want to do?" << endl << "1. Rest" << endl << "2. Visit the store" << endl << "3. Continue your journey" << endl;
            //asks player what they want to do, takes input until valid
            cin >> fortChoice;
            while (fortChoice != 1 && fortChoice != 2 && fortChoice != 3)
            {
                cout << "That is not a valid option. Please reenter a valid choice." << endl;
                cin.clear();
                cin.ignore(100, '\n');
                cin >> fortChoice;
            }
            //asks player what they want to do until they leave the fort, calls shop or rest action as appropriate
            while (fortChoice != 3)
            {
                switch (fortChoice) {
                    case 1:{
                        Game::restingAction();
                        break;
                    }
                    case 2:{
                        Game::storeAction();
                        break;
                    }
                    default:
                        break;
                }
                cout << "What would you like to do next?" << endl << "1. Rest" << endl << "2. Visit the store" << endl << "3. Continue your journey" << endl;
                cin >> fortChoice;
                while (fortChoice != 1 && fortChoice != 2 && fortChoice != 3)
                {
                    cout << "That is not a valid option. Please reenter a valid choice." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> fortChoice;
                }
            }
            //increases the store prices when the fort is left
            store.increasePrices();
        }
        //if the milestone is a river:
        else
        {
            //prints message that they've reached the river, asks what they want to do, takes input until valid
            cout << "You have reached the " << gameMap.getNextMilestoneName() << ". It is " << gameMap.getNextMilestoneDepth() << " feet deep. What do you want to do?" << endl << "1. Rest" << endl << "2. Cross the river" << endl;
            int riverChoice;
            cin >> riverChoice;
            while (riverChoice != 1 && riverChoice != 2)
            {
                cout << "That is not a valid option. Please reenter a valid choice." << endl;
                cin.clear();
                cin.ignore(100, '\n');
                cin >> riverChoice;
            }
            switch (riverChoice) {
                //if rest, calls resting action
                case 1:{
                    Game::restingAction();
                    break;
                }
                //if cross
                case 2:{
                    //if the depth is greater than 3, either takes the ferry if they have enough money, subtracts money accordingly, or crosses on foot, subtracts some food and bullets accordingly
                    if (gameMap.getNextMilestoneDepth() > 3)
                    {
                        if (supplies.getMoney() > (getMembersAlive() * 10))
                        {
                            cout << "You pay $10 per party member to take the ferry across." << endl;
                            supplies.addMoney(getMembersAlive() * -1 * 10);
                        }
                        else
                        {
                            cout << "The river is too deep to cross on foot, and you don't have enough money to take the ferry." << endl << "While crossing the river on foot, 50 lbs of your food and 2 cases of bullets are washed away by the current." << endl;
                            supplies.addFood(-50);
                            if (supplies.getBullets() > 40)
                            {
                                supplies.addBullets(-40);
                            }
                            else
                            {
                                supplies.setBullets(0);
                            }
                        }
                    }
                    //if it is 3 feet or less in depth, they can cross on foot without issue
                    else
                    {
                        cout << "You successfully cross the river on foot." << endl;
                    }
                }
                default:
                    break;
            }
        }
    }
}

//returns the alive status of the leader
bool Game::leaderAlive() const
{
    return partyMembers[0].getAlive();
}

//returns true if the party has food
bool Game::haveFood() const
{
    if (supplies.getFood() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//returns true if the party has 0 wagon parts or more, because if the wagon has broken down and the player has no parts to fix it, wagon parts will go negative
bool Game::wagonWorks() const
{
    if (supplies.getParts() >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//if the month is after november or the date is november 30th, returns false, as the deadline has been reached
bool Game::dateOk() const
{
    if (currentDate.getMonth() > 11 || (currentDate.getMonth() == 11 && currentDate.getDay() == 30))
    {
        return false;
    }
    else
    {
        return true;
    }
}

//if the goal has not been reached, returns false
bool Game::journeyComplete() const
{
    if (gameMap.getMilesTravelled() < 2040)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//if the party has at least 1 ox, returns true
bool Game::haveOxen() const
{
    if (supplies.getOxen() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//prints a status update with current supply totals
void Game::statusUpdate() const
{
    cout << "Current Date: " << currentDate.getMonth() << "/" << currentDate.getDay() << "/" << currentDate.getYear() << endl;
    cout << "Miles Travelled: " << gameMap.getMilesTravelled() << endl;
    cout << "Distance until next milestone: " << (gameMap.getNextMilestoneMileage() - gameMap.getMilesTravelled()) << endl;
    cout << "Food available: " << supplies.getFood() << " lbs" << endl;
    cout << "Bullets available: " << supplies.getBullets() << endl;
    cout << "Cash available: $" << supplies.getMoney() << endl;
}

//returns the distance from start of the next milestone
int Game::getNextMilestoneMileage() const
{
    return gameMap.getNextMilestoneMileage();
}

//returns miles travelled
int Game::getMilesTravelled() const
{
    return gameMap.getMilesTravelled();
}

//writes the game stats to a file and prints them on screen
int Game::writeGameStats() const
{
    ofstream gameData;
    gameData.open("results.txt");
    if (gameData.fail())
    {
        return -99;
    }
    cout << endl << "~~~~~~~~   GAME STATS   ~~~~~~~~" << endl;
    string leader = partyMembers[0].getName();
    int miles = gameMap.getMilesTravelled();
    int foodLeft = supplies.getFood();
    if (supplies.getFood() < 0)
    {
        foodLeft = 0;
    }
    int moneyLeft = supplies.getMoney();
    cout << endl << "Leader Name: " << leader << endl << "Miles travelled: " << miles << endl << "Food remaining: " << foodLeft << " lbs" << endl << "Money Remaining: $" << moneyLeft << endl;
    gameData << endl << "Leader Name: " << leader << endl << "Miles travelled: " << miles << endl << "Food remaining: " << foodLeft << " lbs" << endl << "Money Remaining: $" << moneyLeft << endl; 
    gameData.close();
    return 1;
}



//This is a current version of the file