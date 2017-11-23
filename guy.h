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

class Guy
{
    public:
        Guy(std::string name, int type);

        void addStat(std::string);//Adds a statistic
        void advanceLevel(std::string);
        std::string getName() const;
        std::string getType() const;
        int getTypeInt();

        bool addItem(std::string);
        bool useItem(char);

        void modifyCondition(char, int);//Health/Hunger/Thirst
        bool starving();
        bool dehydrating();
        int calcAttBoost() const;
        int calcDefBoost() const;
        int calcHpBoost() const;
        void addPet(const std::string &);
        bool checkPet(const std::string &);

        const std::string printStat(int) const;//Prints stat #int
        const std::string printStats() const;//Prints all stats

        const std::string printAbilities() const;
        const std::string printInventory() const;
        const std::string printGear() const;
        const std::string printEffects() const;//Gear Effects

        const std::string printCondition() const;
    private:
        std::string m_name, m_typename;
        std::string m_abilities[5];
        std::string m_inventory[6];
        std::string m_pets[10];
        std::string m_gear[10];//Head LH RH Top Bottom Ring Ammy Gloves Boots Back
        //Basic/Rusty
        int m_type, m_maxHealth, m_currentHealth, m_currentThirst, m_currentHunger;
        std::string m_stat_name[50];
        int m_stat_level[50];
        bool spiderv, snakev;//is_vaccinated?
        int getStatNumber(std::string);
        void checkClass();
        void setArcher();//m_type == 0
        void setWarrior();//m_type == 1
        void setAssassin();//m_type == 2
        void setWizard();//m_type == 3
        std::string m_getName();
        std::string m_getType();
        void errorCode(int);
        std::string getBars(int, int) const;
};

#endif
