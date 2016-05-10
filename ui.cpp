/*
 * Originally written by Shane MacBride.
 * Released as Open Source through the MIT License.
 * Copyright Shane MacBride 2016.
 * https://github.com/shanemacbride/TextRealm
 *
*/

#include <iostream>
#include <string>
#include "ui.h"
#include "grid.h"
#include "guy.h"

using namespace std;

Ui::Ui()
{
    m_choice = MenuChoice::m_none;
    for(int i=0; i<15; ++i)
    {
        m_event[i] = " ";
    }
}

void Ui::displayUI(const Guy &g, Grid &gr)
{
    switch(m_choice)
    {
    case MenuChoice::m_none:
        cout<<"\t1\t2\t3\t4\t5\t6\n"<<endl;
        break;
    case MenuChoice::m_key:
        cout<<"\t\tKey\n";
        cout<<"\t\t---\n";
        displayKey(g, gr);
        cout<<"\t1\t2\t3\t4\t[5]\t6\n"<<endl;
        break;
    case MenuChoice::m_controls:
        cout<<"\t\tControls\n";
        cout<<"\t\t--------\n";
        displayControls();
        cout<<"\t1\t2\t3\t[4]\t5\t6\n"<<endl;
        break;
    case MenuChoice::m_desc:
        g.printStats();
        cout<<"\n\tSurroundings";
        cout<<"\n\t------------\n";
        cout<<gr.getDesc()<<endl<<endl;
        g.printCondition();
        cout<<endl<<endl;
        cout<<"\t1\t2\t[3]\t4\t5\t6\n"<<endl;
        break;
    case MenuChoice::m_abilities:
        cout<<"\tAbilities\n";
        cout<<"\t---------\n";
        g.displayAbilities();
        cout<<"\t1\t[2]\t3\t4\t5\t6\n"<<endl;
        break;
    case MenuChoice::m_inventory:
        cout<<"\tGear\n";
        cout<<"\t----\n";
        g.displayGear();
        cout<<"\tGear Effects\n";
        cout<<"\t------------\n";
        g.displayEffects();
        cout<<"\tInventory\n";
        cout<<"\t---------\n";
        g.displayInventory();
        cout<<"\t[1]\t2\t3\t4\t5\t6\n"<<endl;
        break;
    case MenuChoice::m_events:
        cout<<"\tEvents\n";
        cout<<"\t------\n";
        displayEvents();
        cout<<"\t1\t2\t3\t4\t5\t[6]\n"<<endl;
        break;
    default:
        break;
    }
}

void Ui::displayKey(const Guy &g, const Grid &gr)
{
    cout<<"\t\tT\tTree\n";
    cout<<"\t\tH\tHouse\n";
    cout<<"\t\tM\tMonster\n";
    cout<<"\t\tP\tPerson\n";
    cout<<"\t\tC\tChest\n";
    cout<<"\t\tS\tSign\n";
    cout<<"\t\tD\tDungeon\n";
    cout<<"\t\t"<<gr.getAvatar()<<"\t"<<g.getName()<<endl<<endl;
}

void Ui::displayControls()
{
    cout<<"\t\tWASD\tMove Up/Left/Down/Right\n";
    cout<<"\t\tI\tInteract\n\n";
    cout<<"\t\t1\tInventory\n";
    cout<<"\t\t2\tAbilities\n";
    cout<<"\t\t3\tInformation\n";
    cout<<"\t\t4\tControls\n";
    cout<<"\t\t5\tArea Key\n";
    cout<<"\t\t6\tEvent Log\n\n";
    cout<<"\t\tQ\tQuit Game\n"<<endl;
}

void Ui::checkDesc(Grid &gr)
{
    if(m_choice == MenuChoice::m_desc)
    {
        cout<<gr.getDesc()<<endl<<endl;
    }
}

void Ui::toggle(int t)
{
    m_choice = MenuChoice((m_choice == t) ? 0 : t);
}

void Ui::updateEvent(const string &event)
{
    for(int i = 13; i>=0; --i)
    {
        m_event[i + 1] = m_event[i];
    }
    int seconds_since_start = difftime(time(0), start);
    string currenttime = to_string(seconds_since_start);
    string eventtobeadded = "(" + currenttime + ") " + event;
    m_event[0] = eventtobeadded;
}

void Ui::displayEvents()
{
    for(int i=14; i>=0; --i)
    {
        if(m_event[i] != " ")
        {
            cout<<'\t'<<m_event[i]<<'\n';
        }
    }
    cout<<'\n';
}

void Ui::displayEngagedEvents()
{
    for(int i=5; i>=0; --i)
    {
        if(m_event[i] != " ")
        {
            cout<<'\t'<<m_event[i]<<'\n';
        }
    }
    cout<<"\n\n"<<endl;//None House Monster Person Chest Sign Dungeon
}

