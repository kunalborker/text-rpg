/*
 * Originally written by Shane MacBride.
 * Released as Open Source through the MIT License.
 * Copyright Shane MacBride 2016.
 * https://github.com/shanemacbride/TextRealm
 *
*/

#ifndef _UI_H_
#define _UI_H_

#include <iostream>
#include <string>
#include "grid.h"
#include "guy.h"
#include <time.h>

using namespace std;

enum MenuChoice
{
    m_none      = 0,
    m_key       = 1,
    m_controls  = 2,
    m_desc      = 3,
    m_abilities = 4,
    m_inventory = 5,
    m_events    = 6
};

class Ui
{
    public:
        Ui();
        time_t start = time(0);
        void displayKey(const Guy &g, const Grid &gr);
        void displayControls();
        void checkDesc(Grid &);//Description
        void toggle(int);
        void displayUI(const Guy &g, Grid &gr);
        void updateEvent(const string &);
        void displayEngagedEvents();
        //shows events for current engagement
    private:
        MenuChoice m_choice;
        string m_event[15];
        void displayEvents();
};

#endif
