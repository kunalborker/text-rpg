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
    ifstream smugglerz ("smugglers.txt");
    ifstream spiderz ("spiders.txt");
    ifstream nativez ("natives.txt");
    ifstream snakez ("snakes.txt");
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
}

int Grid::interactMessage()
{
    if(ir == 3 && ic == 13)//Top Left Sign
    {
        return 1;
    }
    else if(ir == 3 && ic == 176)//Top Right Sign
    {
        return 2;
    }
    else if(ir == 45 && ic == 178)//Bottom Right Sign
    {
        return 3;
    }
    else if(ir == 43 && ic == 14)//Bottom Left Sign
    {
        return 4;
    }
    else if(ir == 7 && ic == 176)//Top Right Dugeon
    {
        return 5;
    }
    else if(ir == 40 && ic == 176)//Bottom Right Dungeon
    {
        return 6;
    }
    else if(ir == 38 && ic == 20)//Bottom Left Dungeon
    {
        return 7;
    }
    else if(ir == 8 && ic == 20)//Top Left Dungeon
    {
        return 8;
    }
    else if(ir == 2 && ic == 100)//Top Dungeon
    {
        return 9;
    }
    else if(ir == 46 && ic == 98)//Bottom Dungeon
    {
        return 10;
    }
    else if(ir == 23 && ic == 104)//Starter chest
    {
        return 11;
    }
    else if(ir == 34 && ic == 48)//BL C in Trees
    {
        return 12;
    }
    else if(ir == 18 && ic == 160)//TR C in Trees
    {
        return 13;
    }
    else if(ir == 13 && ic == 78)//Person Top in Trees
    {
        return 14;
    }
    else if(ir == 9 && ic == 33)//TL H
    {
        return 15;
    }
    else if(ir == 32 && ic == 32)//BL H
    {
        return 16;
    }
    else if(ir == 36 && ic == 188)//BR H
    {
        return 17;
    }
    else if(ir == 4 && ic == 160)//TR H
    {
        return 18;
    }
    return 0;
}

void Grid::printSign()
{
    for(int row = 0; row < 29; row++)
    {
        for(int column = 0; column < 59; column++)
        {
            if(interactMessage() == 1)//smugglers TL
            {
                cout<<m_bS[row][column];
            }
            else if(interactMessage() == 2)
            {
                cout<<m_sS[row][column];//spiders TR
            }
            else if(interactMessage() == 3)
            {
                cout<<m_nS[row][column];//BR natives
            }
            else
            {
                cout<<m_vS[row][column];//BL snakes
            }
        }
        cout<<endl;
    }
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

void Grid::printGrid()
{
    int row, column;
    m_iM[cr][cc] = m_avatar;
    for (row = cr - 15; row < cr + 14; row++)//[0, 29]
    {
        for (column = cc - 30; column < cc + 29; column++)//[0, 59]
        {
            if( (row < 0) || (column < 0) || (row > 49) || (column > 199))
            {
                cout<<' ';
            }
            else
            {
                cout<<m_iM[row][column];
            }
        }
        cout<<endl;
    }
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

char Grid::getAvatar()
{
    return m_avatar;
}

string Grid::getDesc()
{//cr = 15, cc = 30
    string up, down, left, right;
    up = m_unit_desc(m_iM[cr - 1][cc]);
    left = m_unit_desc(m_iM[cr][cc - 1]);
    right = m_unit_desc(m_iM[cr][cc + 1]);
    down = m_unit_desc(m_iM[cr + 1][cc]);
    m_desc = "\tAbove: " + up + "\tLeft: " + left + "\n\tBelow: " + down + "\tRight: " + right;
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
        if((position[i] == 'H')|(position[i]=='M')|(position[i]=='P')|(position[i]=='C')|(position[i]=='S')|(position[i]=='D'))
        {
            if(i==0)
            {
                ir = cr -1;
                ic = cc;
            }
            else if(i==1)
            {
                ir = cr;
                ic = cc - 1;
            }
            else if(i==2)
            {
                ir = cr;
                ic = cc + 1;
            }
            else if(i==3)
            {
                ir = cr + 1;
                ic = cc;
            }
            return position[i];
        }
    }
    return 'N';
}

string Grid::m_unit_desc(char unit)
{
    if(unit == 'T')
    {
        return "Tree";
    }
    else if(unit == 'H')
    {
        return "House";
    }
    else if(unit == 'M')
    {
        return "Monster";
    }
    else if(unit == 'P')
    {
        return "Person";
    }
    else if(unit == 'C')
    {
        return "Chest";
    }
    else if(unit == 'S')
    {
        return "Sign";
    }
    else if(unit == 'D')
    {
        return "Dungeon";
    }
    return "None";
}

void Grid::printChest()
{//interactMessage() == 11 (starter) 12 (snakes) 13 (spiders)
    for(int a = 1; a < 15; a++)
    {
        if(a != 7)
        {
            cout<<endl;
        }
        else
        {
            if(interactMessage() == 11)//Starter Chest
            {
                cout<<"            A hidden golden chest."<<endl;
            }
            else if(interactMessage() == 12)//Snake Boss
            {
                cout<<"                A slimy chest."<<endl;
            }
            else if(interactMessage() == 13)//Spider Boss
            {
                cout<<"             A cobweb-covered chest."<<endl;
            }
        }
    }
    cout<<"          _,---.-.---------------.-.---,_"<<endl;//15 lines
    cout<<"     _.-'`====/o/=================/o/====`'-._"<<endl;
    cout<<"   .'========/o/===================/o/========'."<<endl;
    cout<<"  |---------)~(---------------------)~(---------|"<<endl;
    cout<<"   /________/o/________.---.________/o/________/"<<endl;
    cout<<"    |=======/o/========) ? (========/o/=======|"<<endl;
    cout<<"    |       | |       (  '  )       | |       |"<<endl;
    cout<<"    |=======|o|========'---'========|o|=======|"<<endl;
    cout<<"    |       | |         ____        | |       |"<<endl;
    cout<<"    |=======|o|========)X| /(=======|o|=======|"<<endl;
    cout<<"    |       | |       |XX|/ /|      | |       |"<<endl;
    cout<<"    |=======|o|=======/--/ / /======|o|=======|"<<endl;
    cout<<"    |       | |        '/_/.'       | |       |"<<endl;
    cout<<"    lc======|o|=====================|o|=======|"<<endl;
    cout<<"    '-------'-'---------------------'-'-------'"<<endl;
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
