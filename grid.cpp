/*
 * Originally written by Shane MacBride.
 * Released as Open Source through the MIT License.
 * Copyright Shane MacBride 2016.
 * https://github.com/shanemacbride/TextRealm
 *
*/

#include <iostream>
#include <string>
#include "grid.h"
#include <fstream>

using namespace std;

Grid::Grid(char avatar, string map)
     : m_avatar(avatar), m_map(map)
{
    ifstream myfile (m_map);
    int row, column;
    for (row = 0; row < 50; row++)
    {
        for (column = 0; column < 200; column++)
        {
            myfile>>m_iM[row][column];
        }
    }
    m_desc = "\tDefault description";
    cr = 15;
    cc = 30;
    ir = 0;
    ic = 0;
    moves = 0;
    setCrCc('Z');
    ifstream smugglerz ("./txt/signs/smugglers.txt");
    ifstream spiderz ("./txt/signs/spiders.txt");
    ifstream nativez ("./txt/signs/natives.txt");
    ifstream snakez ("./txt/signs/snakes.txt");
    for (row = 0; row<29; row++)
    {
        for(column = 0; column<59; column++)
        {
            smugglerz>>m_bS[row][column];
            spiderz>>m_sS[row][column];
            nativez>>m_nS[row][column];
            snakez>>m_vS[row][column];
        }
    }

    m_interactables.emplace_back(1, 3, 13);    // Top Left Sign
    m_interactables.emplace_back(2, 3, 176);   // Top Right Sign
    m_interactables.emplace_back(3, 45, 178);  // Bottom Right Sign
    m_interactables.emplace_back(4, 43, 14);   // Bottom Left Sign
    m_interactables.emplace_back(5, 7, 176);   // Top Right Dungeon
    m_interactables.emplace_back(6, 40, 176);  // Bottom Right Dungeon
    m_interactables.emplace_back(7, 38, 20);   // Bottom Left Dungeon
    m_interactables.emplace_back(8, 8, 20);    // Top Left Dungeon
    m_interactables.emplace_back(9, 2, 100);   // Top Dungeon
    m_interactables.emplace_back(10, 46, 98);  // Bottom Dungeon
    m_interactables.emplace_back(11, 23, 104); // Starter chest
    m_interactables.emplace_back(12, 34, 48);  // BL C in Trees
    m_interactables.emplace_back(13, 18, 160); // TR C in Trees
    m_interactables.emplace_back(14, 13, 78);  // Person Top in Trees
    m_interactables.emplace_back(15, 9, 33);   // TL H
    m_interactables.emplace_back(16, 32, 32);  // BL H
    m_interactables.emplace_back(17, 36, 188); // BR H
    m_interactables.emplace_back(18, 4, 160);  // TR H

    m_unit_desc['T'] = "Tree";
    m_unit_desc['H'] = "House";
    m_unit_desc['M'] = "Monster";
    m_unit_desc['P'] = "Person";
    m_unit_desc['C'] = "Chest";
    m_unit_desc['S'] = "Sign";
    m_unit_desc['D'] = "Dungeon";
}

int Grid::interactMessage()
{
    for (const Interactable& element : m_interactables)
    {
        if (ir == element.row && ic == element.column)
        {
            return element.id;
        }
    }
    return 0;
}

const string Grid::printSign()
{
    string printOut;

    /** This approach repeats a bit of code but it isn't good having unnecessary
        branching( if, switch, etc ) inside long loops.                          */

    switch (interactMessage())
    {
    case 1: //smugglers TL
        for(int row = 0; row < 29; row++) {
            printOut += string(m_bS[row], m_bS[row] + 60) + "\n";
        }
    break;
    case 2: //spiders TR
        for(int row = 0; row < 29; row++) {
            printOut += string(m_sS[row], m_sS[row] + 60) + "\n";
        }
    break;
    case 3: //BR natives
        for(int row = 0; row < 29; row++) {
            printOut += string(m_nS[row], m_nS[row] + 60) + "\n";
        }
    break;
    case 4: //BL snakes
        for(int row = 0; row < 29; row++) {
            printOut += string(m_vS[row], m_vS[row] + 60) + "\n";
        }
    break;
    }

    return printOut;
}

void Grid::teleportSpawn()
{
    m_iM[cr][cc] = '_';
    cr = sr;
    cc = sc;
}

void Grid::setCrCc(char startingposition)
{
    for(int row = 0; row < 50; row++)
    {
        for(int column = 0; column < 200; column++)
        {
            if(m_iM[row][column] == startingposition)
            {
                cr = row;
                cc = column;
                m_iM[cr][cc] = m_avatar;
                sr = row;
                sc = column;
                return;
            }
        }
    }
}

const string Grid::printGrid()
{
    string printOut;

    int row, column;
    m_iM[cr][cc] = m_avatar;

    /** Same here as in printSign(), I remove unnecessary branching by splitting
        the loop into multiple parts.                                            */

    row = cr - 15;

    // Prints empty rows above grid
    if (row < 0) {
        printOut += string(abs(row), '\n');
        row = 0;
    }

    int maxRow = min(50, cr + 14);
    for (; row < maxRow; row++)
    {
        column = cc - 30;

        // Prints empty columns left of grid
        if (column < 0) {
            printOut += string(abs(column), ' ');
            column = 0;
        }

        int maxColumn = min(200, cc + 29);
        for (; column < maxColumn; column++)
        {
            printOut += m_iM[row][column];
        }
        printOut += '\n';
    }

    // Prints empty rows below grid
    if (row < cr + 14) {
        printOut += string(cr + 14 - row, '\n');
    }

    return printOut;
}

void Grid::moveUp()
{//currentrow = 15 currentcolumn = 30
    if(m_iM[cr - 1][cc] != '_')//Is something blocking the path? 14,30
    {
        return;
    }
    m_iM[cr][cc] = '_';//The space currently in is now _
    cr--;//Move the current location to the row above (same column)
    moves++;
}

void Grid::moveLeft()
{//cr = 15, cc = 30
    if(m_iM[cr][cc - 1] != '_')//15, 29
    {
        return;
    }
    m_iM[cr][cc] = '_';
    cc--;
    moves++;
}

void Grid::moveRight()
{//cr = 15, cc = 30
    if(m_iM[cr][cc + 1] != '_')//15, 31
    {
        return;
    }
    m_iM[cr][cc] = '_';
    cc++;
    moves++;
}

void Grid::moveDown()
{//cr = 15, cc = 30
    if(m_iM[cr + 1][cc] != '_')//16, 30
    {
        return;
    }
    m_iM[cr][cc] = '_';
    cr++;
    moves++;
}

char Grid::getAvatar() const
{
    return m_avatar;
}

string Grid::getDesc() // why does this function mutate as well as access?
{//cr = 15, cc = 30
    string up, down, left, right;
    up = unit_desc(m_iM[cr - 1][cc]);
    left = unit_desc(m_iM[cr][cc - 1]);
    right = unit_desc(m_iM[cr][cc + 1]);
    down = unit_desc(m_iM[cr + 1][cc]);
    m_desc = "Above: " + up + "\tLeft: " + left + "\nBelow: " + down + "\tRight: " + right;
    //cout<<"IC:"<<ic<<"IR:"<<ir<<endl; //interacted-last shortcut viewing
    return m_desc;
}

char Grid::interactWhat()
{
    char position[4];
    position[0] = m_iM[cr - 1][cc];//up
    position[1] = m_iM[cr][cc - 1];//left
    position[2] = m_iM[cr][cc + 1];//right
    position[3] = m_iM[cr + 1][cc];//down

    for(int i=0; i<4; i++)
    {
        if(position[i] == 'H' || position[i] == 'M' || position[i] == 'P' ||
           position[i] == 'C' || position[i] == 'S' || position[i] == 'D')
        {
            switch (i)
            {
            case 0:
                ir = cr -1;
                ic = cc;
            break;
            case 1:
                ir = cr;
                ic = cc - 1;
            break;
            case 2:
                ir = cr;
                ic = cc + 1;
            break;
            case 3:
                ir = cr + 1;
                ic = cc;
            break;
            }
            return position[i];
        }
    }
    return 'N';
}

string Grid::unit_desc(char unit)
{
    string desc;

    auto iter = m_unit_desc.find(unit);
    if (iter != m_unit_desc.end())
    {
        desc = iter->second;
    }
    else
    {
        desc = "None";
    }

    return desc;
}

const string Grid::printChest()
{//interactMessage() == 11 (starter) 12 (snakes) 13 (spiders)
    string printOut;

    printOut += "\n\n\n\n\n\n\n";
    switch (interactMessage())
    {
    case 11: //Starter Chest
        printOut += "            A hidden golden chest.\n";
    break;
    case 12: //Snake Boss
        printOut += "                A slimy chest.\n";
    break;
    case 13: //Spider Boss
        printOut += "             A cobweb-covered chest.\n";
    break;
    }
    printOut += "\n\n\n\n\n\n";

    printOut += "          _,---.-.---------------.-.---,_          \n"; //15 lines
    printOut += "     _.-'`====/o/=================/o/====`'-._     \n";
    printOut += "   .'========/o/===================/o/========'.   \n";
    printOut += "  |---------)~(---------------------)~(---------|  \n";
    printOut += "   /________/o/________.---.________/o/________/   \n";
    printOut += "    |=======/o/========) ? (========/o/=======|    \n";
    printOut += "    |       | |       (  '  )       | |       |    \n";
    printOut += "    |=======|o|========'---'========|o|=======|    \n";
    printOut += "    |       | |         ____        | |       |    \n";
    printOut += "    |=======|o|========)X| /(=======|o|=======|    \n";
    printOut += "    |       | |       |XX|/ /|      | |       |    \n";
    printOut += "    |=======|o|=======/--/ / /======|o|=======|    \n";
    printOut += "    |       | |        '/_/.'       | |       |    \n";
    printOut += "    lc======|o|=====================|o|=======|    \n";
    printOut += "    '-------'-'---------------------'-'-------'    \n";

    return printOut;
}
void Grid::loadEmpty(char a)
{
    int row, column;
    for (row = 0; row < 29; row ++)
    {
        for (column = 0; column < 59; column++)
        {
            m_iM[row][column] = '_';
        }
    }
    m_iM[15][31] = 'R';
    m_iM[15][29] = 'L';
    m_iM[14][30] = 'U';
    m_iM[16][30] = 'D';
    m_iM[15][30] = a;
    m_iM[10][12] = 'B';
    m_iM[23][26] = 'C';
}
