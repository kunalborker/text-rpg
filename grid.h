//grid.h

#ifndef _GRID_H_
#define _GRID_H_

#include <iostream>
#include <string>

using namespace std;

class Grid
{
    public:
        Grid(char avatar, string map);
        void printGrid();
        string getDesc();
        void moveUp();
        void moveLeft();
        void moveRight();
        void moveDown();
        char getAvatar();
        void teleportSpawn();
        char interactWhat();
        void printSign();
        void printChest();
        int interactMessage();
        int moves;
    private:
        int cr, cc, sr, sc, ir, ic;//Current row, current column of m_avatar
        //spawn row, spawn column
        //interacting row, interacting column
        char m_avatar;
        string m_map, m_desc;
        char m_iM[50][200];//member_variable_imported_Map
        char m_bS[29][59];//member_variable_bunny_Sign (Now Smugglers)
        char m_nS[29][59];//natives sign
        char m_vS[29][59];//venemous snakes sign
        char m_sS[29][59];//spiders sign
        void setCrCc(char);
        void loadEmpty(char);
        string m_unit_desc(char);
};

#endif
