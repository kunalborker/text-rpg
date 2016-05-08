//main.cpp

#include "guy.h"
#include "grid.h"
#include "ui.h"

#include <iostream>
#include <string>
#include <ctime>//clock
#include <time.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void clearScreen();
void gameLoop();
void mainMenu();
void breakTime(int seconds);

//time_t start = time(0);

void gameLoop(Grid gr, Guy g)
{
    bool game_running = true;
    Ui myui;
    char c;//command
    string coa, cob, coc;//Chest Option A,B,C
    myui.updateEvent("Welcome, " + g.getName() + "! Press [4] to see Controls.");
    int gamecounter = 0;
    char engaged = 'N';//None House Monster Person Chest Sign Dungeon
    while(game_running)
    {
        //int s_since_start = difftime(time(0), myui.start);
        //if((s_since_start % 30 == 0)&&(gamecounter >= displacement))
        if((gr.moves % 100 == 0) && (gr.moves > 0))
        {//Every _ moves (After starting)
            //displacement = gamecounter + 30;
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
        gamecounter++;
        clearScreen();
        //int seconds_since_start = difftime(time(0), start);
        //string currenttime = to_string(seconds_since_start);
        //myui.updateEvent(currenttime);
        if(engaged == 'N')//not engaged
        {
            myui.displayUI(g, gr);
        }
        else//engaged
        {
            myui.displayEngagedEvents();
        }
        if(engaged == 'N')
        {
            gr.printGrid();
        }
        else if(engaged == 'H')
        {
        }
        else if(engaged == 'M')
        {
        }
        else if(engaged == 'P')
        {
        }
        else if(engaged == 'C')
        {//11 Starter C -- 12 BL C in Trees -- 13 TR C in Trees
            gr.printChest();//15 out of 30 lines to be printed
            if(gr.interactMessage() == 11)//coa,cob,coc Chest Option A,B,C
            {//Print chest options
            }
            else if(gr.interactMessage() == 12)
            {
            }
            else if(gr.interactMessage() == 13)
            {
            }
        }
        else if(engaged == 'S')
        {
            gr.printSign();
        }
        else if(engaged == 'D')
        {
        }
        cout<<endl;
        system("stty raw");//Set terminal to raw mode
        c=getchar();
        if(engaged == 'N')//not engaged
        {
            if((c=='w')|(c=='W'))//Move Up
            {
                gr.moveUp();
                //g.modifyCondition('H', -1);
                //g.modifyCondition('U', 1);
                //g.modifyCondition('T', 1);
            }
            else if((c=='a')|(c=='A'))//Move Left
            {
                gr.moveLeft();
            }
            else if((c=='s')|(c=='S'))//Move Down
            {
                gr.moveDown();
            }
            else if((c=='d')|(c=='D'))//Move Right
            {
                gr.moveRight();
            }
            else if((c=='i')|(c=='I'))//Interact
            { 
                //string message(1, gr.interactWhat());
                char x = gr.interactWhat();
                engaged = gr.interactWhat();
                if(x == 'N')
                {
                    myui.updateEvent("There is nothing around to interact with.");
                }
                else if(x == 'H')
                {
                    myui.updateEvent("You attempt to enter the house...");
                    if(gr.interactMessage() == 15)//TL H
                    {
                        myui.updateEvent("");
                    }
                    else if(gr.interactMessage() == 16)//BL H
                    {
                        myui.updateEvent("");
                    }
                    else if(gr.interactMessage() == 17)//BR H
                    {
                        myui.updateEvent("");
                    }
                    else if(gr.interactMessage() == 18)//TR H
                    {
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
                    if(gr.interactMessage() == 11)//Starter Chest
                    {
                        myui.updateEvent("...it opens!");
                        myui.updateEvent("Press <F> to finish looting.");
                        coa = "Golden Ring";//5 HP + 5
                        cob = "Apple";//Heal 10
                        coc = "Chameleon Egg";
                    }
                    else if(gr.interactMessage() == 12)//BL C in Trees (snakes)
                    {
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
                    }
                    else if(gr.interactMessage() == 13)//TR C in Trees (spiders)
                    {
                        myui.updateEvent("...it's covered in spider webs.");
                        myui.updateEvent("The chest opens after clearing the webs!");
                        myui.updateEvent("Press <F> to finish looting.");
                        coa = "Kevlar Gloves";//7 Defense + 5
                        cob = "Kevlar Vest";//3 Defense + 10
                        coc = "Desert Spider Venom Vaccine";//Quest item
                    }//All of the above equippables have been added
                     //to calc_Boost() Functions in guy.cpp... Apple, Eggs, Quests not done yet
                }
                else if(x == 'S')
                {
                    myui.updateEvent("You attempt to read the sign...");
                    if(gr.interactMessage() == 1)//TL
                    {
                        myui.updateEvent("...it appears to say something about smugglers.");
                        myui.updateEvent("Press <F> to finish reading.");
                    }
                    else if(gr.interactMessage() == 2)//TR
                    {
                        myui.updateEvent("...it appears to say something about spiders.");
                        myui.updateEvent("Press <F> to finish reading.");
                    }
                    else if(gr.interactMessage() == 3)//BR
                    {
                        myui.updateEvent("...it appears to say something about natives.");
                        myui.updateEvent("Press <F> to finish reading.");
                    }
                    else if(gr.interactMessage() == 4)//BL
                    {
                        myui.updateEvent("...it appears to say something about snakes.");
                        myui.updateEvent("Press <F> to finish reading.");
                    }
                }
                else if(x == 'D')
                {
                    myui.updateEvent("You attempt to enter the dungeon...");
                    if(gr.interactMessage() == 5)//TR
                    {
                    }
                    else if(gr.interactMessage() == 6)//BR
                    {
                    }
                    else if(gr.interactMessage() == 7)//BL
                    {
                    }
                    else if(gr.interactMessage() == 8)//TL
                    {
                    }
                    else if(gr.interactMessage() == 9)//T
                    {
                    }
                    else if(gr.interactMessage() == 10)//B
                    {
                    }
                }
            }
            else if((c=='F')|(c=='f')|(c=='G')|(c=='g')|(c=='H')|(c=='h')|(c=='J')|(c=='j')|(c=='K')|(c=='k')|(c=='L')|(c=='l'))//Inventory
            {
                if(g.useItem(c))
                {
                }
                else
                {
                    myui.updateEvent("You don't have an item in that inventory slot.");
                }
            }
            else if((c=='Z')|(c=='z')|(c=='X')|(c=='x')|(c=='C')|(c=='c')|(c=='V')|(c=='v')|(c=='B')|(c=='b'))//abilities
            {
                if((c=='C')|(c=='c'))
                {
                    gr.teleportSpawn();
                    myui.updateEvent("Teleported to Spawn.");
                }
            }
            else if(c=='1')//Display Inventory
            {
                myui.toggle(1);
            }
            else if(c=='2')//Display Abilities
            {
                myui.toggle(2);
            }
            else if(c=='3')//Display Area Description & Levels
            {
                myui.toggle(3);
            }
            else if(c=='4')//Display Controls
            {
                myui.toggle(4);
            }
            else if(c=='5')//Display Key
            {
                myui.toggle(5);
            }
            else if(c=='6')//Display Log
            {
                myui.toggle(6);
            }
            else if((c=='q')|(c=='Q'))
            {
                myui.updateEvent("Game quitting.");
                game_running = false;
            }
            else//Update latest message
            {
                myui.updateEvent("Invalid command. Press [4] to display Controls.");
            }
        }
        else if(engaged == 'H')
        {
            if((c=='q')|(c=='Q'))
            {
                myui.updateEvent("Game quitting.");
                game_running = false;
            }
            engaged = 'N';
        }
        else if(engaged == 'M')
        {
            if((c=='q')|(c=='Q'))
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
            if((c=='f')|(c=='F'))//Finished Looting
            {
                g.addItem(coa);
                g.addItem(cob);
                g.addItem(coc);
                engaged = 'N';
            }//11 starter 12 snakes 13 spiders
        }
        else if(engaged == 'S')//Sign
        {
            if((c=='f')|(c=='F'))//Finished Reading
            {
                engaged = 'N';
            }
        }
        else if(engaged == 'D')
        {
            engaged = 'N';
        }
        system("stty cooked");//reset terminal to cooked mode
    }
}

void clearScreen()
{
    cout<<string(100,'\n');
}

void mainMenu()
{
    char t = '\t';
    cout<<">Choices: [N]ew Game [L]oad Game [H]elp [Q]uit"<<endl<<endl;
    string choice;
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
            char choicechar;
            strcpy(&choicechar, choice.c_str());
            Grid gr(choicechar, "defaultmap.txt");
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
            gameLoop(gr, g); 
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

int main()
{
    cout<<endl<<'\t'<<"Welcome! Please input a choice."<<endl<<endl;
    mainMenu();
    return 0;
}
