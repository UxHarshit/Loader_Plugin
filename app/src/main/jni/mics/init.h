//
// Created by UxHurricane on 27-07-2021.
//

#ifndef GLPLUGIN_INIT_H
#define GLPLUGIN_INIT_H

int gSW = 0;
int gSH = 0;
bool bFPS = false;
const char *cFPS = "Team UxH";
std::string mFps;
char mEntity[90] = ">> 선수 : 00 * 봇 : 00 <<";


bool sHD = true;
bool sFOV = false;
bool sEntity = false;
int radiusFOV = 110;
int fpsW = gSW/35;
int fpsH = gSH/35;
struct screen
{
    int x = 0,y = 0;
};
struct gameInf
{
    int playerCount = 0;
};
#endif //GLPLUGIN_INIT_H
