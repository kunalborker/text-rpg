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
    m_key = false;
    m_controls = false;
    m_desc = false;
    m_abilities = false;
    m_inventory = false;
    m_events = true;
    for(int i=0; i<15; i++)
    {
        m_event[i] = " ";
    }
}

void Ui::displayUI(Guy g, Grid gr)
{
    if((!m_key) && (!m_controls) && (!m_desc) && (!m_abilities) && (!m_inventory) && (!m_events))
    {
        cout<<"\t1\t2\t3\t4\t5\t6"<<endl<<endl;
    }
    else if(m_inventory)
    {
        cout<<"\tGear\n";
        cout<<"\t----\n";
        g.displayGear();
        cout<<"\tGear Effects\n";
        cout<<"\t------------\n";
        g.displayEffects();
        cout<<"\tInventory\n";
        cout<<"\t---------\n";
        g.displayInventory();
        cout<<"\t[1]\t2\t3\t4\t5\t6"<<endl<<endl;
    }
    else if(m_abilities)
    {
        cout<<"\tAbilities\n";
        cout<<"\t---------\n";
        g.displayAbilities();
        cout<<"\t1\t[2]\t3\t4\t5\t6"<<endl<<endl;
    }
    else if(m_desc)
    {
        g.printStats();
        cout<<"\n\tSurroundings";
        cout<<"\n\t------------\n";
        cout<<gr.getDesc()<<endl<<endl;
        g.printCondition();
        cout<<endl<<endl;
        cout<<"\t1\t2\t[3]\t4\t5\t6"<<endl<<endl;
    }
    else if(m_controls)
    {
        cout<<"\t\tControls\n";
        cout<<"\t\t--------\n";
        displayControls();
        cout<<"\t1\t2\t3\t[4]\t5\t6"<<endl<<endl;
    }
    else if(m_key)
    {
        cout<<"\t\tKey\n";
        cout<<"\t\t---\n";
        displayKey(g, gr);
        cout<<"\t1\t2\t3\t4\t[5]\t6"<<endl<<endl;
    }
    else if(m_events)
    {
        cout<<"\tEvents\n";
        cout<<"\t------\n";
        displayEvents();
        cout<<"\t1\t2\t3\t4\t5\t[6]"<<endl<<endl;
    }
}
 
void Ui::displayKey(Guy g, Grid gr)
{
    cout<<"\t\tT\tTree"<<endl;
    cout<<"\t\tH\tHouse"<<endl;
    cout<<"\t\tM\tMonster"<<endl;
    cout<<"\t\tP\tPerson"<<endl;
    cout<<"\t\tC\tChest"<<endl;
    cout<<"\t\tS\tSign"<<endl;
    cout<<"\t\tD\tDungeon"<<endl;
    cout<<"\t\t"<<gr.getAvatar()<<"\t"<<g.getName()<<endl<<endl;
}

void Ui::displayControls()
{
    cout<<"\t\tWASD\tMove Up/Left/Down/Right"<<endl;
    cout<<"\t\tI\tInteract"<<endl<<endl;
    cout<<"\t\t1\tInventory"<<endl;
    cout<<"\t\t2\tAbilities"<<endl;
    cout<<"\t\t3\tInformation"<<endl;
    cout<<"\t\t4\tControls"<<endl;
    cout<<"\t\t5\tArea Key"<<endl;
    cout<<"\t\t6\tEvent Log"<<endl<<endl;
    cout<<"\t\tQ\tQuit Game"<<endl<<endl;
}

void Ui::checkDesc(Grid gr)
{
    if(m_desc)
    {
        cout<<gr.getDesc()<<endl<<endl;
    }
}

void Ui::toggle(int t)
{
    if(t==1)
    {
        if(m_inventory)
        {
            m_inventory = false;
        }
        else
        {
            m_inventory = true;
            m_key = false;
            m_controls = false;
            m_desc = false;
            m_abilities = false;
            m_events = false;
        }
    }
    else if(t==2)
    {
        if(m_abilities)
        {
            m_abilities = false;
        }
        else
        {
            m_abilities = true;
            m_inventory = false;
            m_key = false;
            m_controls = false;
            m_desc = false;
            m_events = false;
        }
    }
    else if(t==3)
    {
        if(m_desc)
        {
            m_desc = false;
        }
        else
        {
            m_desc = true;
            m_abilities = false;
            m_inventory = false;
            m_key = false;
            m_controls = false;
            m_events = false;
        }
    }
    else if(t==4)
    {
        if(m_controls)
        {
            m_controls = false;
        }
        else
        {
            m_controls = true;
            m_desc = false;
            m_abilities = false;
            m_inventory = false;
            m_key = false;
            m_events = false;
        }
    }
    else if(t==5)
    {
        if(m_key)
        {
            m_key = false;
        }
        else
        {
            m_key = true;
            m_controls = false;
            m_desc = false;
            m_abilities = false;
            m_inventory = false;
            m_events = false;
        }
    }
    else if(t==6)
    {
        if(m_events)
        {
            m_events = false;
        }
        else
        {
            m_events = true;
            m_key = false;
            m_desc = false;
            m_controls = false;
            m_inventory = false;
            m_abilities = false;
        }
    }
}

void Ui::updateEvent(string event)
{
    for(int i = 13; i>=0; i--)
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
    for(int i=14; i>=0; i--)
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
    for(int i=5; i>=0; i--)
    {
        if(m_event[i] != " ")
        {
            cout<<'\t'<<m_event[i]<<'\n';
        }
    }
    cout<<endl<<endl<<endl;//None House Monster Person Chest Sign Dungeon
}

