/*
 * Originally written by Shane MacBride.
 * Released as Open Source through the MIT License.
 * Copyright Shane MacBride 2016.
 * https://github.com/shanemacbride/TextRealm
 *
*/

#ifndef _GRID_H_
#define _GRID_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Grid
{
    public:
        Grid(char avatar, std::string map);

        std::string getDesc();
        void moveUp();
        void moveLeft();
        void moveRight();
        void moveDown();
        char getAvatar() const;
        void teleportSpawn();
        char interactWhat();

        int interactMessage();
        int moves;

        const std::string printGrid();
        const std::string printSign();
        const std::string printChest();
    private:
        int cr, cc, sr, sc, ir, ic;//Current row, current column of m_avatar
        //spawn row, spawn column
        //interacting row, interacting column
        char m_avatar;
        std::string m_map, m_desc;
        char m_iM[50][200];//member_variable_imported_Map
        char m_bS[29][59];//member_variable_bunny_Sign (Now Smugglers)
        char m_nS[29][59];//natives sign
        char m_vS[29][59];//venemous snakes sign
        char m_sS[29][59];//spiders sign
        void setCrCc(char);
        void loadEmpty(char);
        std::string unit_desc(char);

        struct Interactable
        {
            Interactable(int _id, int r, int c)
            : id(_id), row(r), column(c)
            {}

            int id;
            int row;
            int column;
        };
        std::vector<Interactable> m_interactables;
        std::map<char, std::string> m_unit_desc;
};

#endif
