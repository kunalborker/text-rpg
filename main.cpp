/*
 * Originally written by Shane MacBride.
 * Released as Open Source through the MIT License.
 * Copyright Shane MacBride 2016.
 * https://github.com/shanemacbride/TextRealm
 *
*/

#include "guy.h"
#include "grid.h"
#include "ui.h"

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>//clock
#include <time.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void clearScreen();
void mainMenu();
void breakTime(int seconds);

void displayEverything(UiAlignment align, const string& gridText, const string& uiMenuText, const string& uiText);

void gameLoop(Grid gr, Guy g, UiAlignment align)
{
    bool game_running = true;
    Ui myui;
    char c, x;//command
    string coa, cob, coc;//Chest Option A,B,C
    myui.updateEvent("Welcome, " + g.getName() + "! Press [4] to see Controls.");
    int gamecounter = 0;
    char engaged = 'N';//None House Monster Person Chest Sign Dungeon

    while(game_running)
    {
        if((gr.moves % 100 == 0) && (gr.moves > 0))
        {//Every _ moves (After starting)
            g.modifyCondition('T', 1);//Thirst goes up _%
            g.modifyCondition('U', 1);//Hunger goes up _%
            if(g.starving())//Adjust Health accordingly
            {
                myui.updateEvent("You lose health due to lack of nourishment.");
            }
            if(g.dehydrating())//Adjust Health accordingly
            {
                myui.updateEvent("You lose health due to dehydration.");
            }
        }
        ++gamecounter;
        clearScreen();

        if(engaged == 'N')//not engaged
        {
            displayEverything(align, gr.printGrid(), myui.printUImenu(align), myui.printUI(g, gr));
        }
        else//engaged
        {
            switch (engaged)
            {
            case 'H':
                displayEverything(align, "", "", myui.printEngagedEvents());
            break;
            case 'M':
                displayEverything(align, "", "", myui.printEngagedEvents());
            break;
            case 'P':
                displayEverything(align, "", "", myui.printEngagedEvents());
            break;
            case 'C': //11 Starter C -- 12 BL C in Trees -- 13 TR C in Trees
                displayEverything(align, gr.printChest(), "", myui.printEngagedEvents());

                switch (gr.interactMessage()) //coa,cob,coc Chest Option A,B,C
                {
                case 11: //Print chest options
                break;
                case 12:
                break;
                case 13:
                break;
                }
            break;
            case 'S':
                displayEverything(align, gr.printSign(), "", myui.printEngagedEvents());
            break;
            case 'D':
                displayEverything(align, "", "", myui.printEngagedEvents());
            break;
            }
        }

        cout<<endl;

        system("stty raw");//Set terminal to raw mode
        c = tolower(getchar());
        system("stty cooked");//reset terminal to cooked mode

        if(engaged == 'N')//not engaged
        {
            switch(c)//tbh at this point we might as well use an array of function pointers
            {
            //Directional movement
            case 'w':
                gr.moveUp();
                break;
            case 'a':
                gr.moveLeft();
                break;
            case 's':
                gr.moveDown();
                break;
            case 'd':
                gr.moveRight();
                break;

            //Interact
            case 'i': // THIS IS WAY TOO LONG!!
                //string message(1, gr.interactWhat());
                x = gr.interactWhat();
                engaged = gr.interactWhat();
                if(x == 'N')
                {
                    myui.updateEvent("There is nothing around to interact with.");
                }
                else if(x == 'H')
                {
                    myui.updateEvent("You attempt to enter the house...");
                    switch(gr.interactMessage())
                    {
                    case 15://TL H
                        myui.updateEvent("");
                        break;
                    case 16://BL H
                        myui.updateEvent("");
                        break;
                    case 17://BR H
                        myui.updateEvent("");
                        break;
                    case 18://TR H
                        myui.updateEvent("");
                        break;
                    default:
                        myui.updateEvent("");
                    }
                }
                else if(x == 'M')
                {
                    myui.updateEvent("You attempt to attack the monster...");
                }
                else if(x == 'P')
                {
                    myui.updateEvent("You greet the person...");
                    if(gr.interactMessage() == 14)//Person Top in trees
                    {
                        myui.updateEvent("");
                    }
                }
                else if(x == 'C')
                {
                    myui.updateEvent("You attempt to open the chest...");
                    switch (gr.interactMessage())
                    {
                    case 11: //Starter Chest
                        myui.updateEvent("...it opens!");
                        myui.updateEvent("Press <F> to finish looting.");
                        coa = "Golden Ring";//5 HP + 5
                        cob = "Apple";//Heal 10
                        coc = "Chameleon Egg";
                    break;
                    case 12: //BL C in Trees (snakes)
                        myui.updateEvent("...there's a small snake guarding it.");
                        myui.updateEvent("The snake bites you as it runs away!");
                        myui.updateEvent("-1 Health Point");
                        g.modifyCondition('H', -1);
                        myui.updateEvent("Press <F> to finish looting.");
                        coa = "Snakeskin Boots";//8 Defense + 4 Attack + 4
                        cob = "Amulet of the Snake";//Snake Egg rewarded
                        //upon completion of Snake Dungeon
                        //6 Defense + 4 Attack + 4
                        coc = "Desert Snake Venom Vaccine";//Quest Item
                    break;
                    case 13: //TR C in Trees (spiders)
                        myui.updateEvent("...it's covered in spider webs.");
                        myui.updateEvent("The chest opens after clearing the webs!");
                        myui.updateEvent("Press <F> to finish looting.");
                        coa = "Kevlar Gloves";//7 Defense + 5
                        cob = "Kevlar Vest";//3 Defense + 10
                        coc = "Desert Spider Venom Vaccine";//Quest item
                    break;
                    }//All of the above equippables have been added
                     //to calc_Boost() Functions in guy.cpp... Apple, Eggs, Quests not done yet
                }
                else if(x == 'S')
                {
                    myui.updateEvent("You attempt to read the sign...");
                    switch (gr.interactMessage())
                    {
                    case 1: //TL
                        myui.updateEvent("...it appears to say something about smugglers.");
                        myui.updateEvent("Press <F> to finish reading.");
                    break;
                    case 2: //TR
                        myui.updateEvent("...it appears to say something about spiders.");
                        myui.updateEvent("Press <F> to finish reading.");
                    break;
                    case 3: //BR
                        myui.updateEvent("...it appears to say something about natives.");
                        myui.updateEvent("Press <F> to finish reading.");
                    break;
                    case 4: //BL
                        myui.updateEvent("...it appears to say something about snakes.");
                        myui.updateEvent("Press <F> to finish reading.");
                    break;
                    }
                }
                else if(x == 'D')
                {
                    myui.updateEvent("You attempt to enter the dungeon...");
                    switch (gr.interactMessage())
                    {
                    case 5: //TR
                    break;
                    case 6: //BR
                    break;
                    case 7: //BL
                    break;
                    case 8: //TL
                    break;
                    case 9: //T
                    break;
                    case 10: //B
                    break;
                    }
                }
                break;

            //Items
            case 'f':
            case 'g':
            case 'h':
            case 'j':
            case 'k':
            case 'l':
                if(g.useItem(c))
                {
                }
                else
                {
                    myui.updateEvent("You don't have an item in that inventory slot.");
                }
                break;

            //Abilities
            case 'z':
                break;
            case 'x':
                break;
            case 'c':
                gr.teleportSpawn();
                myui.updateEvent("Teleported to Spawn.");
                break;
            case 'v':
                break;
            case 'b':
                break;

            //UI Toggle
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
                myui.toggle(c-'0');
                break;
            case 'q':
                myui.updateEvent("Game quitting.");
                //we probably want player to confirm that they want to quit...
                game_running = false;
                break;
            default:
                myui.updateEvent("Invalid command. Press [4] to display Controls.");
            }
        }
        else if(engaged == 'H')
        {
            if(c == 'q')
            {
                myui.updateEvent("Game quitting.");
                game_running = false;
            }
            engaged = 'N';
        }
        else if(engaged == 'M')
        {
            if(c == 'q')
            {
                myui.updateEvent("Game quitting.");
                game_running = false;
            }
            engaged = 'N';
        }
        else if(engaged == 'P')
        {
            engaged = 'N';
        }
        else if(engaged == 'C')//Chest
        {//11 Starter C -- 12 BL C in Trees -- 13 TR C in Trees
            if(c == 'f')//Finished Looting
            {
                g.addItem(coa);
                g.addItem(cob);
                g.addItem(coc);
                engaged = 'N';
            }//11 starter 12 snakes 13 spiders
        }
        else if(engaged == 'S')//Sign
        {
            if(c=='f')//Finished Reading
            {
                engaged = 'N';
            }
        }
        else if(engaged == 'D')
        {
            engaged = 'N';
        }
    }
}

void clearScreen()
{
    cout<<string(100,'\n');
}

void mainMenu()
{
    string choice;
    UiAlignment align;

    cout << "The game can be played in two modes, [V]ertical and [H]orizontal\nWhich one do you want? ";
    cin >> choice;
    choice[0] = tolower(choice[0]);

    switch (choice[0])
    {
    case 'v':
        align = ALIGN_VERTICAL;
    break;
    case 'h':
        align = ALIGN_HORIZONTAL;
    break;
    default:
        cout << "Couldn't understand choice, defaulting to Vertical." << endl;
        align = ALIGN_VERTICAL;
    }

    cin.ignore(100, '\n');
    switch (align)
    {
    case ALIGN_VERTICAL:
        cout << "Your terminal should be at least 80x64 characters in size.\n" << endl;
    break;
    case ALIGN_HORIZONTAL:
        cout << "Your terminal should be at least 140x32 characters in size.\n" << endl;
    break;
    }
    cout << "Press enter when ready to continue." << endl;
    cin.get();

    char t = '\t';

    cout<<endl<<'\t'<<"Welcome! Please input a choice."<<endl<<endl;
    cout<<">Choices: [N]ew Game [L]oad Game [H]elp [Q]uit\n"<<endl;

    while(cin>>choice)
    {
        if((choice=="N")||(choice=="n"))
        {
            int type = 0;
            string options = "Choose your class: [A]rcher [W]arrior A[s]sassin Wi[z]ard";
            cout<<endl<<t<<options<<endl<<endl;
            while(cin>>choice)
            {
                if((choice=="A")||(choice=="a"))
                {
                    type = 0;
                    break;
                }
                else if((choice=="W")||(choice=="w"))
                {
                    type = 1;
                    break;
                }
                else if((choice=="S")||(choice=="s"))
                {
                    type = 2;
                    break;
                }
                else if((choice=="Z")||(choice=="z"))
                {
                    type = 3;
                    break;
                }
                else if((choice=="H")||(choice=="h"))
                {
                    cout<<endl<<t<<options<<endl<<endl;
                }
                else
                {
                    cout<<endl<<"Sorry, <"<<choice<<"> is invalid.  Press [H] for help."<<endl<<endl;
                }
            }
            char choicechar = choice[0];
            Grid gr(choicechar, "./txt/maps/defaultmap.txt");
            options = "Choose the name of your character.";
            cout<<endl<<t<<options<<endl<<endl;
            cin.ignore();//ignores leading whitespace
            getline(cin, choice);
            Guy g(choice, type);
            cout<<endl<<t<<"Character created!"<<endl<<endl;
            cout<<endl<<t<<"Name: "<<g.getName()<<endl;
            cout<<t<<"Type: "<<g.getType()<<endl<<endl;
            cout<<t<<"Prepare for your adventure..."<<endl;
            breakTime(3);
            gameLoop(gr, g, align);
            break;
        }
        else if((choice=="L")||(choice=="l"))
        {
            cout<<endl<<t<<"Game Saves:"<<endl<<endl;
            cout<<"Empty"<<endl<<endl;
        }
        else if((choice=="H")||(choice=="h"))
        {
            cout<<endl;
            mainMenu();
            break;
        }
        else if((choice=="Q")||(choice=="q"))
        {
            break;
        }
        else
        {
            cout<<endl<<"Sorry, <"<<choice<<"> is invalid. Press [H] for help."<<endl<<endl;
        }
    }
}

void breakTime(int seconds)
{
    clock_t temp;
    temp = clock() + seconds * CLOCKS_PER_SEC;
    while(clock() < temp)
    {
    }
}

int countLines(const string& str)
{
    int counter = 0;
    for (char c : str) {
        if (c == '\n') {
            ++counter;
        }
    }
    return counter + 1;
}

void displayEverything(UiAlignment align, const string& gridText, const string& uiMenuText, const string& uiText)
{
    stringstream gridStream(gridText);
    stringstream uiMenuStream(uiMenuText);
    stringstream uiStream(uiText);

    string grid, uiMenu, ui;

    switch (align)
    {
    case ALIGN_VERTICAL:
        while (getline(uiStream, ui)) {
            cout << '\t' << ui << endl;
        }
        while (getline(uiMenuStream, uiMenu)) {
            cout << uiMenu << endl;
        }
        cout << endl;
        while (getline(gridStream, grid)) {
            cout << grid << endl;
        }
    break;
    case ALIGN_HORIZONTAL:
    {
        int uiLines = countLines(uiText);
        int gridLines = countLines(gridText);

        if (uiLines > gridLines) {
            for (int i = 0; i < uiLines - gridLines; ++i) {
                getline(uiStream, ui);
                cout << string(64, ' ') << ui << endl;
            }
        }

        while (getline(gridStream, grid)) {
            uiMenu.clear();
            ui.clear();
            getline(uiMenuStream, uiMenu);
            getline(uiStream, ui);

            cout << grid;
            if (grid.length() < 80) {
                cout << string(80 - grid.length(), ' ');
            }
            cout << uiMenu;
            if (uiMenu.length() < 8) {
                cout << string(8 - uiMenu.length(), ' ');
            }
            cout << ui << endl;
        }
    }
    break;
    }
}

int main()
{
    mainMenu();

    return 0;
}
