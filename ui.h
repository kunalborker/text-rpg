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

enum MenuChoice
{
    m_none      = 0,
    m_key       = 5,
    m_controls  = 4,
    m_desc      = 3,
    m_abilities = 2,
    m_inventory = 1,
    m_events    = 6
};

enum UiAlignment
{
    ALIGN_VERTICAL,
    ALIGN_HORIZONTAL
};

class Ui
{
    public:
        Ui();
        time_t start = time(0);
        void toggle(int);

        const std::string printUImenu(UiAlignment align) const;
        const std::string printUI(const Guy &g, Grid &gr);

        const std::string printKey(const Guy &g, const Grid &gr);
        const std::string printControls();

        const std::string printEvents();
        const std::string printEngagedEvents();
        //shows events for current engagement

        void updateEvent(const std::string &);

    private:
        MenuChoice m_choice;
        std::string m_event[15];
};

#endif
