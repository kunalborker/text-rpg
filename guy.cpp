/*
 * Originally written by Shane MacBride.
 * Released as Open Source through the MIT License.
 * Copyright Shane MacBride 2016.
 * https://github.com/shanemacbride/TextRealm
 *
*/

#include <iostream>
#include <string>
#include "guy.h"

using namespace std;

Guy::Guy(string name, int type)
    : m_name(name), m_type(type)
{
    for(int i=0; i<50; i++)
    {
        m_stat_name[i] = "Locked";
        m_stat_level[i] = 1;
    }
    m_abilities[0] = "Special Move";
    m_abilities[1] = "Meditate";
    m_abilities[2] = "Teleport to Spawn";
    m_abilities[3] = "Teleport to Home";
    m_abilities[4] = "Teleport to Pet Yard";
    for(int z=0; z<6; z++)
    {
        m_inventory[z] = "Empty";
    }
    m_maxHealth = 10;
    m_currentHealth = 10;
    m_currentThirst = 0;
    m_currentHunger = 0;
    spiderv = false;
    snakev = false;
    for(int x=0; x<10; x++)
    {
        m_gear[x] = "None";
        m_pets[x] = "None";
    }
    checkClass();
}

bool Guy::dehydrating()
{
    int dehydrate = m_currentThirst/25;

    if(dehydrate != 0)
    {
        m_currentHealth -= dehydrate;
        if(m_currentHealth < 0)
        {
            m_currentHealth = 0;
        }
        return true;
    }

    return false;
}

bool Guy::starving()
{
    int starve = m_currentHunger/25;

    if(starve != 0)
    {
        m_currentHealth -= starve;
        if(m_currentHealth < 0)
        {
            m_currentHealth = 0;
        }
        return true;
    }

    return false;
}

void Guy::modifyCondition(char HUT, int amount)//Health hUnger Thirst
{
    switch (HUT)
    {
    case 'H':
        m_currentHealth += amount;
        if (m_currentHealth < 0)
        {
            m_currentHealth = 0;
        }
        else if (m_currentHealth > m_maxHealth + calcHpBoost())
        {
            m_currentHealth = m_maxHealth + calcHpBoost();
        }
    break;
    case 'U':
        m_currentHunger += amount;
        if (m_currentHunger < 0)
        {
            m_currentHunger = 0;
        }
        else if (m_currentHunger > 100)
        {
            m_currentHunger = 100;
        }
    break;
    case 'T':
        m_currentThirst += amount;
        if (m_currentThirst < 0)
        {
            m_currentThirst = 0;
        }
        else if (m_currentThirst > 100)
        {
            m_currentThirst = 100;
        }
    break;
    case 'E'://exempt from limits
        m_currentHealth = m_currentHealth + amount;
    break;
    }
}

const string Guy::printStat(int x) const
{
    return string(m_stat_name[x]) + ": " + to_string(m_stat_level[x]);
}

int Guy::getTypeInt()
{
    return m_type;
}

const string Guy::printInventory() const
{
    string printOut;

    char hotkeys[6];
    hotkeys[0] = 'F';
    hotkeys[1] = 'G';
    hotkeys[2] = 'H';
    hotkeys[3] = 'J';
    hotkeys[4] = 'K';
    hotkeys[5] = 'L';
    for(int h=0; h<6; h++)
    {
        printOut += string(1, hotkeys[h]) + "\t\t" + m_inventory[h] + "\n";
    }

    return printOut;
}

const string Guy::printGear() const
{
    string printOut;

    printOut += "Head\t\t" + m_gear[0] + "\n";
    printOut += "Left-hand\t" + m_gear[1] + "\n";
    printOut += "Right-hand\t" + m_gear[2] + "\n";
    printOut += "Top\t\t" + m_gear[3] + "\n";
    printOut += "Bottom\t\t" + m_gear[4] + "\n";
    printOut += "Ring\t\t" + m_gear[5] + "\n";
    printOut += "Amulet\t\t" + m_gear[6] + "\n";
    printOut += "Gloves\t\t" + m_gear[7] + "\n";
    printOut += "Boots\t\t" + m_gear[8] + "\n";
    printOut += "Back\t\t" + m_gear[9] + "\n";

    return printOut;
}

const string Guy::printEffects() const
{
    string printOut;

    printOut += m_stat_name[1] + " Boost\t+" + to_string(calcAttBoost()) + "\n";
    printOut += m_stat_name[2] + " Boost\t+" + to_string(calcDefBoost()) + "\n";
    printOut += m_stat_name[3] + " Boost\t+" + to_string(calcHpBoost()) + "\n";

    return printOut;
}

const string Guy::printAbilities() const
{
    string printOut;

    char hotkey[5];
    hotkey[0] = 'Z';
    hotkey[1] = 'X';
    hotkey[2] = 'C';
    hotkey[3] = 'V';
    hotkey[4] = 'B';
    for(int i = 0; i<5; i++)
    {
        printOut += string(1, hotkey[i]) + "\t" + m_abilities[i] + "\n";
    }

    return printOut;
}

const string Guy::printStats() const
{
    string printOut;

    int i = 0;
    int stat_count = 0;
    for(int c=0; c<50; c++)
    {
        if(m_stat_name[c] != "Locked")
        {
            stat_count++;
        }
    }
    for(int row=1; row<=10; row++)
    {
        if(stat_count>0)
        {
            printOut += "Levels\n";
            printOut += "------\n";
        }
        for(int collumn=1; collumn<=5; collumn++)
        {
            if(stat_count>0)
            {
            printOut += printStat(i);
            printOut += " ";
            i++;
            stat_count--;
            }
        }
        if(stat_count > 0)
        {
            printOut +=  "\n";
        }
        if(stat_count == 0)
        {
            printOut += "\n";
            break;
        }
    }

    return printOut;
}

string Guy::getBars(int c, int m) const//current, max
{
    int percent = ((double)c/m)*100;

    return "[" + string(percent/10, 'X') + string(10 - percent/10, '_') + "]";
}

const string Guy::printCondition() const
{
    string printOut;

    printOut += "Condition\n";
    printOut += "---------\n";
    printOut += "Health: " + getBars(m_currentHealth, (m_maxHealth+calcHpBoost())) + " " + to_string(m_currentHealth) + "/" + to_string(m_maxHealth+calcHpBoost()) + "\n";
    printOut += "Hunger: " + getBars(m_currentHunger, 100) + " " + to_string(m_currentHunger) + "%\n";
    printOut += "Thirst: " + getBars(m_currentThirst, 100) + " " + to_string(m_currentThirst) + "%\n";

    return printOut;
}

void Guy::addStat(string name)
{
    for(int i=0; i<50; i++)
    {
        if(m_stat_name[i] == "Locked")
        {
            m_stat_name[i] = name;
            i = i + 50;
        }
    }
}

void Guy::advanceLevel(string stat_name)
{
    m_stat_level[getStatNumber(stat_name)]++;
    //cout<<endl;
    //cout<<"You just advanced a level in "<<stat_name<<"!"<<endl;
}

string Guy::getName() const
{
    return m_name;
}

string Guy::getType() const
{
    return m_typename;
}

int Guy::getStatNumber(string stat_name)
{
    for(int i = 0; i<50; i++)
    {
        if(stat_name == m_stat_name[i])
        {
            return i;
        }
    }
    return 0;
}

void Guy::checkClass()
{
    switch (m_type)
    {
    case 0:
        setArcher();
    break;
    case 1:
        setWarrior();
    break;
    case 2:
        setAssassin();
    break;
    case 3:
        setWizard();
    break;
    default:
        errorCode(1);
    }
}

void Guy::setArcher()
{
    m_typename = "Archer";
    addStat("Prestige");//Prestige max level: 99
    addStat("Archery");
    addStat("Defense");
    addStat("Health");
    m_abilities[0] = "Archer Ability";
    m_gear[0] = "Basic Hood";//Defense++
    m_gear[1] = "Basic Bow";//Attack++
    m_gear[2] = "/";
    m_gear[3] = "Shirt";//Defense++
    m_gear[4] = "Shorts";//Defense++
    m_gear[9] = "Basic Quiver";//Attack++
}

void Guy::setWarrior()
{
    m_typename = "Warrior";
    addStat("Prestige");
    addStat("Strength");
    addStat("Defense");
    addStat("Health");
    m_abilities[0] = "Warrior Ability";
    m_gear[0] = "Rusty Helmet";//Defense + 2
    m_gear[1] = "Rusty Sword";//Attack++
    m_gear[2] = "Wooden Shield";//Defense + 2
    m_gear[3] = "Shirt";//Defense++
    m_gear[4] = "Shorts";//Defense++
}

void Guy::setAssassin()
{
    m_typename = "Assassin";
    addStat("Prestige");
    addStat("Stealth");
    addStat("Defense");
    addStat("Health");
    m_abilities[0] = "Assassin Ability";
    m_gear[0] = "Basic Hood";//Defense++
    m_gear[1] = "Rusty Knife";//Attack++
    m_gear[3] = "Shirt";//Defense++
    m_gear[4] = "Shorts";//Defense++
    m_gear[9] = "Basic Camouflaged Cloak";//Attack++
}

void Guy::setWizard()
{
    m_typename = "Wizard";
    addStat("Prestige");
    addStat("Magic");
    addStat("Defense");
    addStat("Health");
    m_abilities[0] = "Wizard Ability";
    m_gear[0] = "Basic Hood";//Defense++
    m_gear[1] = "Basic Staff";//Attack++
    m_gear[3] = "Shirt";//Defense++
    m_gear[4] = "Shorts";//Defense++
    m_gear[2] = "Basic Spellbook";//Attack++
}

int Guy::calcHpBoost() const
{
    int boost = 0;
    if(m_gear[5] == "Golden Ring")
    {
        boost = boost + 5;
    }
    return boost;
}

int Guy::calcDefBoost() const
{
    int boost = 0;
    //Helmet
    if(m_gear[0] == "Basic Hood")
    {
        boost++;
    }
    else if(m_gear[0] == "Rusty Helmet")
    {
        boost = boost + 2;
    }
    //Off hand
    if(m_gear[2] == "Wooden Shield")
    {
        boost = boost + 2;
    }
    //Top
    if(m_gear[3] == "Shirt")
    {
        boost++;
    }
    else if(m_gear[3] == "Kevlar Vest")
    {
        boost = boost + 10;
    }
    //Bottom
    if(m_gear[4] == "Shorts")
    {
        boost++;
    }
    //Neck
    if(m_gear[6] == "Amulet of the Snake")
    {
        boost = boost + 4;
    }
    //Gloves
    if(m_gear[7] == "Kevlar Gloves")
    {
        boost = boost + 5;
    }
    //Boots
    if(m_gear[8] == "Snakeskin Boots")
    {
        boost = boost + 4;
    }
    return boost;
}

int Guy::calcAttBoost() const//Attack Boost
{
    int boost = 0;
    //Weapon
    if((m_gear[1] == "Basic Bow") || (m_gear[1] == "Rusty Sword") || (m_gear[1] == "Rusty Knife") || (m_gear[1] == "Basic Staff"))
    {
        boost++;
    }
    //Off-hand
    if((m_gear[2] == "Basic Spellbook"))
    {
        boost++;
    }
    //Amulet
    if(m_gear[8] == "Amulet of the Snake")
    {
        boost = boost + 4;
    }
    //Boots
    if(m_gear[8] == "Snakeskin Boots")
    {
        boost = boost + 4;
    }
    //Cape
    if((m_gear[9] == "Basic Quiver") || (m_gear[9] == "Basic Camouflaged Cloak"))
    {
        boost++;
    }
    return boost;
}

void Guy::errorCode(int code)
{
    cout<<endl<<"Error code <"<<code<<">."<<endl;
/*
    1   Invalid m_type.
*/
}

bool Guy::addItem(string item)
{
    for(int i=0; i<6; i++)
    {
        if(m_inventory[i] == "Empty")
        {
            m_inventory[i] = item;
            return true;//item added
        }
    }
    return false;//Item failed to add
}

bool Guy::useItem(char in)//item number
{
    int ci = 0;//current item slot

    // 'in' is always lowercase
    switch (in)
    {
    case 'f':
        ci = 0;
    break;
    case 'g':
        ci = 1;
    break;
    case 'h':
        ci = 2;
    break;
    case 'j':
        ci = 3;
    break;
    case 'k':
        ci = 4;
    break;
    case 'l':
        ci = 5;
    break;
    }

    if(m_inventory[ci] == "Empty")
    {
        return false;
    }

    if(m_inventory[ci] == "Apple")
    {
        m_inventory[ci] = "Empty";
        modifyCondition('H', 10);
        //myui.updateEvent("The apple tastes great! +10HP");
    }
    else if(m_inventory[ci] == "Chameleon Egg")
    {
        m_inventory[ci] = "Empty";
        addPet("Chameleon");
        //myui.updateEvent("The Chameleon Egg has hatched!");
        //myui.updateEvent("The chameleon runs off to your Pet Yard.");
    }
    else if(m_inventory[ci] == "Golden Ring")
    {
        if(m_gear[5] == "None")
        {
            m_inventory[ci] = "Empty";
        }
        else
        {
            m_inventory[ci] = m_gear[5];
        }
        m_gear[5] = "Golden Ring";
        modifyCondition('E', 5);
        //myui.updateEvent("As you equip the Golden Ring,");
        //myui.updateEvent("your health appears to improve...");
    }
    else if(m_inventory[ci] == "Kevlar Gloves")
    {
        if(m_gear[7] == "None")
        {
            m_inventory[ci] = "Empty";
        }
        else
        {
            m_inventory[ci] = m_gear[7];
        }
        m_gear[7] = "Kevlar Gloves";
    }
    else if(m_inventory[ci] == "Kevlar Vest")
    {
        if(m_gear[3] == "None")
        {
            m_inventory[ci] = "Empty";
        }
        else
        {
            m_inventory[ci] = m_gear[3];
        }
        m_gear[3] = "Kevlar Vest";
    }
    else if(m_inventory[ci] == "Desert Spider Venom Vaccine")
    {
        m_inventory[ci] = "Empty";
        spiderv = true;
    }
    else if(m_inventory[ci] == "Snakeskin Boots")
    {
        if(m_gear[8] == "None")
        {
            m_inventory[ci] = "Empty";
        }
        else
        {
            m_inventory[ci] = m_gear[8];
        }
        m_gear[8] = "Snakeskin Boots";
    }
    else if(m_inventory[ci] == "Amulet of the Snake")
    {
        if(m_gear[6] == "None")
        {
            m_inventory[ci] = "Empty";
        }
        else
        {
            m_inventory[ci] = m_gear[6];
        }
        m_gear[6] = "Amulet of the Snake";
    }
    else if(m_inventory[ci] == "Desert Snake Venom Vaccine")
    {
        m_inventory[ci] = "Empty";
        snakev = true;
    }//To be added below... all default items..

    return true;
}

void Guy::addPet(const string &pet)
{
    for(int i=0; i<10; ++i)
    {
        if(m_pets[i] == "None")
        {
            m_pets[i] = pet;
            //do we want to fill ALL open pet slots with the new pet??
            //return;
        }
    }
    //add a check in case all pet slots are full?
}

bool Guy::checkPet(const string &check)
{
    for(int i=0; i<10; ++i)
    {
        if(m_pets[i] == check)
        {
            return true;
        }
    }
    return false;
}

