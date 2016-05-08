//ui.h

#ifndef _UI_H_
#define _UI_H_

#include <iostream>
#include <string>
#include "grid.h"
#include "guy.h"
#include <time.h>

using namespace std;

class Ui
{
    public:
        Ui();
        time_t start = time(0);
        void displayKey(Guy g, Grid gr);
        void displayControls();
        void checkDesc(Grid);//Description
        void toggle(int);
        void displayUI(Guy g, Grid gr);
        void updateEvent(string);
        void displayEngagedEvents();
        //shows events for current engagement
    private:
        bool m_key, m_controls, m_desc, m_abilities, m_inventory, m_events;
        string m_event[15];
        void displayEvents();
};

#endif
