//File: guy.cpp

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
    if(m_currentThirst == 100)
    {
        m_currentHealth = m_currentHealth - 4;
        if(m_currentHealth <= 0)
        {
            m_currentHealth = 0;
        }
        return true;
    }
    else if(m_currentThirst >= 75)
    {
        m_currentHealth = m_currentHealth - 3;
        if(m_currentHealth <=0)
        {
            m_currentHealth = 0;
        }
        return true;
    }
    else if(m_currentThirst >= 50)
    {
        m_currentHealth = m_currentHealth - 2;
        if(m_currentHealth <= 0)
        {
            m_currentHealth = 0;
        }
        return true;
    }
    else if(m_currentThirst >= 25)
    {
        m_currentHealth = m_currentHealth - 1;
        if(m_currentHealth <= 0)
        {
            m_currentHealth = 0;
        }
        return true;
    } 
    return false;
}

bool Guy::starving()
{
    if(m_currentHunger == 100)
    {
        m_currentHealth = m_currentHealth - 4;
        if(m_currentHealth <= 0)
        {
            m_currentHealth = 0;
        }
        return true;
    }
    else if(m_currentHunger >= 75)
    {
        m_currentHealth = m_currentHealth - 3;
        if(m_currentHealth <= 0)
        {
            m_currentHealth = 0;
        }
        return true;
    }
    else if(m_currentHunger >= 50)
    {
        m_currentHealth = m_currentHealth - 2;
        if(m_currentHealth <= 0)
        {
            m_currentHealth = 0;
        }
        return true;
    }
    else if(m_currentHunger >= 25)
    {
        m_currentHealth = m_currentHealth - 1;
        if(m_currentHealth <= 0)
        {
            m_currentHealth = 0;
        }
        return true;
    }
    return false;
}

void Guy::modifyCondition(char HUT, int amount)//Health hUnger Thirst
{
    if(HUT == 'H')
    {
        if((amount + m_currentHealth) <= 0)
        {
            m_currentHealth = 0;
        }
        else if((amount + m_currentHealth) >= (m_maxHealth + calcHpBoost()))
        {
            m_currentHealth = m_maxHealth + calcHpBoost();
        }
        else
        {
            m_currentHealth = m_currentHealth + amount;
        }
    }
    else if(HUT == 'U')
    {
        if((amount + m_currentHunger) >= 100)
        {
            m_currentHunger = 100;
        }
        else if((amount + m_currentHunger) <= 0)
        {
            m_currentHunger = 0;
        }
        else
        {
            m_currentHunger = m_currentHunger + amount;
        }
    }
    else if(HUT == 'T')
    {
        if((amount + m_currentThirst) >= 100)
        {
            m_currentThirst = 100;
        }
        else if((amount + m_currentThirst) <= 0)
        {
            m_currentThirst = 0;
        }
        else
        {
            m_currentThirst = m_currentThirst + amount;
        }
    }
    else if(HUT == 'E')//exempt from limits
    {
        m_currentHealth = m_currentHealth + amount;
    }
}

void Guy::printStat(int x)
{
    cout<<m_stat_name[x]<<": "<<m_stat_level[x];
}

int Guy::getTypeInt()
{
    return m_type;
}

void Guy::displayInventory()
{
    char hotkeys[6];
    hotkeys[0] = 'F';
    hotkeys[1] = 'G';
    hotkeys[2] = 'H';
    hotkeys[3] = 'J';
    hotkeys[4] = 'K';
    hotkeys[5] = 'L';
    for(int h=0; h<6; h++)
    {
        cout<<'\t'<<hotkeys[h]<<"\t\t"<<m_inventory[h]<<'\n';
    }
    cout<<endl;
}

void Guy::displayGear()
{
    cout<<"\tHead\t\t"<<m_gear[0]<<'\n';
    cout<<"\tLeft-hand\t"<<m_gear[1]<<'\n';
    cout<<"\tRight-hand\t"<<m_gear[2]<<'\n';
    cout<<"\tTop\t\t"<<m_gear[3]<<'\n';
    cout<<"\tBottom\t\t"<<m_gear[4]<<'\n';
    cout<<"\tRing\t\t"<<m_gear[5]<<'\n';
    cout<<"\tAmulet\t\t"<<m_gear[6]<<'\n';
    cout<<"\tGloves\t\t"<<m_gear[7]<<'\n';
    cout<<"\tBoots\t\t"<<m_gear[8]<<'\n';
    cout<<"\tBack\t\t"<<m_gear[9]<<'\n';
    cout<<endl;
}

void Guy::displayEffects()
{
    cout<<'\t'<<m_stat_name[1]<<" Boost\t+"<<calcAttBoost()<<'\n';
    cout<<'\t'<<m_stat_name[2]<<" Boost\t+"<<calcDefBoost()<<'\n';
    cout<<'\t'<<m_stat_name[3]<<" Boost\t+"<<calcHpBoost()<<'\n';
    cout<<endl;
}

void Guy::displayAbilities()
{
    char hotkey[5];
    hotkey[0] = 'Z';
    hotkey[1] = 'X';
    hotkey[2] = 'C';
    hotkey[3] = 'V';
    hotkey[4] = 'B';
    for(int i = 0; i<5; i++)
    {
        cout<<'\t'<<hotkey[i]<<'\t'<<m_abilities[i]<<'\n';
    }
    cout<<endl;
}

void Guy::printStats()
{
    int i = 0;
    cout<<endl;
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
            cout<<"\tLevels\n";
            cout<<"\t------\n\t";
        }
        for(int collumn=1; collumn<=5; collumn++)
        {
            if(stat_count>0)
            {
            printStat(i);
            cout<<" ";
            i++;
            stat_count--;
            }
        }
        if(stat_count > 0)
        {
            cout<<endl;
        }
        if(stat_count == 0)
        {
            cout<<endl;
            break;
        }
    }
}

string Guy::getBars(int c, int m)//current, max
{
    int percent = ((double)c/m)*100;
    string bars;
    if(percent == 100)
    {
        return "[XXXXXXXXXX]";
    }
    else if(percent >= 90)
    {
        return "[XXXXXXXXX_]";
    }
    else if(percent >= 80)
    {
        return "[XXXXXXXX__]";
    }
    else if(percent >= 70)
    {
        return "[XXXXXXX___]";
    }
    else if(percent >= 60)
    {
        return "[XXXXXX____]";
    }
    else if(percent >= 50)
    {
        return "[XXXXX_____]";
    }
    else if(percent >= 40)
    {
        return "[XXXX______]";
    }
    else if(percent >= 30)
    {
        return "[XXX_______]";
    }
    else if(percent >= 20)
    {
        return "[XX________]";
    }
    else if(percent >= 10)
    {
        return "[X_________]";
    }
    //string percentresults = to_string(percent) + "%";
    return "[__________]";
}

void Guy::printCondition()
{
    cout<<"\tCondition\n";
    cout<<"\t---------\n";
    cout<<"\tHealth: "<<getBars(m_currentHealth, (m_maxHealth+calcHpBoost()))<<" "<<m_currentHealth<<"/"<<(m_maxHealth+calcHpBoost())<<endl;
    cout<<"\tHunger: "<<getBars(m_currentHunger, 100)<<" "<<m_currentHunger<<"%"<<endl;
    cout<<"\tThirst: "<<getBars(m_currentThirst, 100)<<" "<<m_currentThirst<<"%"<<endl;
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

string Guy::getName()
{
    return m_getName();
}

string Guy::getType()
{
    return m_getType();
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
    if(m_type==0)
    {
        setArcher();
    }
    else if(m_type==1)
    {
        setWarrior();
    }
    else if(m_type==2)
    {
        setAssassin();
    }
    else if(m_type==3)
    {
        setWizard();
    }
    else
    {
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

int Guy::calcHpBoost()
{
    int boost = 0;
    if(m_gear[5] == "Golden Ring")
    {
        boost = boost + 5;
    }
    return boost;
}

int Guy::calcDefBoost()
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

int Guy::calcAttBoost()//Attack Boost
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
    
string Guy::m_getName()
{
    return m_name;
}

string Guy::m_getType()
{
    return m_typename;
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
    if((in=='F')|(in=='f'))//1
    {
        ci = 0;
    }
    else if((in=='G')|(in=='g'))//2
    {
        ci = 1;
    }
    else if((in=='H')|(in=='h'))//3
    {
        ci = 2;
    }
    else if((in=='J')|(in=='j'))//4
    {
        ci = 3;
    }
    else if((in=='K')|(in=='k'))//5
    {
        ci = 4;
    }
    else if((in=='L')|(in=='l'))//6
    {
        ci = 5;
    }
    if(m_inventory[ci] == "Empty")
    {
        return false;
    }
    else if(m_inventory[ci] != "Empty")
    {
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
    return false;
}

void Guy::addPet(string pet)
{
    for(int i=0; i<10; i++)
    {
        if(m_pets[i] == "None")
        {
            m_pets[i] = pet;
        }
    }
}

bool Guy::checkPet(string check)
{
    for(int i=0; i<10; i++)
    {
        if(m_pets[i] == check)
        {
            return true;
        }
    }
    return false;
}

