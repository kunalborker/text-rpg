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

const string Ui::printUImenu(UiAlignment align) const
{
    string printOut;

    switch (align)
    {
    case ALIGN_VERTICAL:
        for (int i = 1; i <= 6; ++i) {
            if (m_choice == i) {
                printOut += "\t[" + to_string(i) + "]";
            } else {
                printOut += "\t" + to_string(i);
            }
        }
        printOut += "\n";
    break;
    case ALIGN_HORIZONTAL:
        for (int i = 1; i <= 6; ++i) {
            if (m_choice == i) {
                printOut += "[" + to_string(i) + "]\n\n\n\n\n";
            } else {
                printOut += to_string(i) + "\n\n\n\n\n";
            }
        }
        printOut += "\n";
    break;
    }

    return printOut;
}

const string Ui::printUI(const Guy &g, Grid &gr)
{
    string printOut;

    switch(m_choice)
    {
    case MenuChoice::m_none:
    break;
    case MenuChoice::m_key:
        printOut += "Key\n";
        printOut += "---\n";
        printOut += printKey(g, gr) + "\n";
    break;
    case MenuChoice::m_controls:
        printOut += "Controls\n";
        printOut += "--------\n";
        printOut += printControls() + "\n";
    break;
    case MenuChoice::m_desc:
        printOut += g.printStats() + "\n";
        printOut += "Surroundings\n";
        printOut += "------------\n";
        printOut += gr.getDesc() + "\n\n";
        printOut += g.printCondition() + "\n";
    break;
    case MenuChoice::m_abilities:
        printOut += "Abilities\n";
        printOut += "---------\n";
        printOut += g.printAbilities() + "\n";
    break;
    case MenuChoice::m_inventory:
        printOut += "Gear\n";
        printOut += "----\n";
        printOut += g.printGear() + "\n";
        printOut += "Gear Effects\n";
        printOut += "------------\n";
        printOut += g.printEffects() + "\n";
        printOut += "Inventory\n";
        printOut += "---------\n";
        printOut += g.printInventory() + "\n";
    break;
    case MenuChoice::m_events:
        printOut += "Events\n";
        printOut += "------\n";
        printOut += printEvents() + "\n";
    break;
    }

    return printOut;
}

const std::string Ui::printKey(const Guy &g, const Grid &gr)
{
    string printOut;

    printOut += "T\tTree\n";
    printOut += "H\tHouse\n";
    printOut += "M\tMonster\n";
    printOut += "P\tPerson\n";
    printOut += "C\tChest\n";
    printOut += "S\tSign\n";
    printOut += "D\tDungeon\n";
    printOut += string(1, gr.getAvatar()) + "\t" + g.getName() + "\n";

    return printOut;
}

const std::string Ui::printControls()
{
    string printOut;

    printOut += "WASD\tMove Up/Left/Down/Right\n";
    printOut += "I\tInteract\n\n";
    printOut += "1\tInventory\n";
    printOut += "2\tAbilities\n";
    printOut += "3\tInformation\n";
    printOut += "4\tControls\n";
    printOut += "5\tArea Key\n";
    printOut += "6\tEvent Log\n\n";
    printOut += "Q\tQuit Game\n";

    return printOut;
}

const std::string Ui::printEvents()
{
    string printOut;

    for(int i=14; i>=0; --i)
    {
        if(m_event[i] != " ")
        {
            printOut += m_event[i] + "\n";
        }
    }

    return printOut;
}

const std::string Ui::printEngagedEvents()
{
    string printOut;

    for(int i=5; i>=0; --i)
    {
        if(m_event[i] != " ")
        {
            printOut += m_event[i] + "\n";
        }
    }

    return printOut;
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
