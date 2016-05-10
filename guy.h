/*
 * Originally written by Shane MacBride.
 * Released as Open Source through the MIT License.
 * Copyright Shane MacBride 2016.
 * https://github.com/shanemacbride/TextRealm
 *
*/

#ifndef _GUY_H_
#define _GUY_H_
#include <iostream>
#include <string>

using namespace std;

class Guy
{
    public:
        Guy(string name, int type);
        void printStat(int) const;//Prints stat #int
        void printStats() const;//Prints all stats
        void addStat(string);//Adds a statistic
        void advanceLevel(string);
        string getName() const;
        string getType() const;
        int getTypeInt();
        void displayAbilities() const;
        void displayInventory() const;
        void displayGear() const;
        void displayEffects() const;//Gear Effects
        bool addItem(string);
        bool useItem(char);
        void printCondition() const;
        void modifyCondition(char, int);//Health/Hunger/Thirst
        bool starving();
        bool dehydrating();
        int calcAttBoost() const;
        int calcDefBoost() const;
        int calcHpBoost() const;
        void addPet(const string &);
        bool checkPet(const string &);
    private:
        string m_name, m_typename;
        string m_abilities[5];
        string m_inventory[6];
        string m_pets[10];
        string m_gear[10];//Head LH RH Top Bottom Ring Ammy Gloves Boots Back
        //Basic/Rusty
        int m_type, m_maxHealth, m_currentHealth, m_currentThirst, m_currentHunger;
        string m_stat_name[50];
        int m_stat_level[50];
        bool spiderv, snakev;//is_vaccinated?
        int getStatNumber(string);
        void checkClass();
        void setArcher();//m_type == 0
        void setWarrior();//m_type == 1
        void setAssassin();//m_type == 2
        void setWizard();//m_type == 3
        string m_getName();
        string m_getType();
        void errorCode(int);
        string getBars(int, int) const;
};

#endif
