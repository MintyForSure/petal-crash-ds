//
// Created by tailofhell on 9/30/26.
//

#include "puzzle.h"

#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <random>

static s8 bgX;
static s8 bgY;
static int tics;
static int buttonHeldLength;
static bool usingButtons=false;
int buttonsX=0;
int buttonsY=0;
using namespace std;
static int grid[8][8]={
    {1,2,3,4,5,0,0,0},
    {5,4,3,2,1,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
};

void playfieldInit(const int screen) {
    //consoleDemoInit();
    NF_LoadSpriteGfx("sprite/petalRed",0,16,16);
    NF_LoadSpritePal("sprite/petalRed",0);
    NF_LoadSpriteGfx("sprite/petalBlue",1,16,16);
    NF_LoadSpritePal("sprite/petalBlue",1);
    NF_LoadSpriteGfx("sprite/petalGreen",2,16,16);
    NF_LoadSpritePal("sprite/petalGreen",2);
    NF_LoadSpriteGfx("sprite/petalViolet",3,16,16);
    NF_LoadSpritePal("sprite/petalViolet",3);
    NF_LoadSpriteGfx("sprite/petalYellow",4,16,16);
    NF_LoadSpritePal("sprite/petalYellow",4);

    NF_LoadSpriteGfx("sprite/cursor",5,16,16);
    NF_LoadSpritePal("sprite/cursor",5);

    NF_VramSpriteGfx(screen,0,0,true);
    NF_VramSpritePal(screen,0,0);
    NF_VramSpriteGfx(screen,1,1,true);
    NF_VramSpritePal(screen,1,1);
    NF_VramSpriteGfx(screen,2,2,true);
    NF_VramSpritePal(screen,2,2);
    NF_VramSpriteGfx(screen,3,3,true);
    NF_VramSpritePal(screen,3,3);
    NF_VramSpriteGfx(screen,4,4,true);
    NF_VramSpritePal(screen,4,4);

    NF_VramSpriteGfx(screen,5,5,true);
    NF_VramSpritePal(screen,5,5);

    NF_LoadTiledBg("bg/background","background",256,256);
    NF_CreateTiledBg(0,3,"background");
    NF_CreateTiledBg(1,3,"background");
    NF_LoadTiledBg("bg/board","board",256,256);
    NF_CreateTiledBg(0,2,"board");
    NF_CreateTiledBg(1,2,"board");

    NF_CreateSprite(1,5,5,5,-32,-32);

    populateBoard(true);
}

static void backgroundScroll() {
    tics++;
    if (tics%2==0) {
        bgX++;
        bgY++;
    }
    NF_ScrollBg(1,3,bgX,bgY);
    NF_ScrollBg(0,3,bgX+64,bgY);
}

void populateBoard(bool init) {
    if (init==true) {
        for (int i=0;i<8;i++) {
            for (int j=0;j<8;j++) {
                int x = rand() % 7;
                int y = rand() % 7;
                grid[i][j]=x;
                grid[i][j]=y;
                if (grid[i][j]==1) {
                    NF_CreateSprite(1,i+8,0,0,(j*16)+64,(i*16)+32);
                }
                else if (grid[i][j]==2) {
                    NF_CreateSprite(1,i+6+20,1,1,(j*16)+64,(i*16)+32);
                }
                else if (grid[i][j]==3) {
                    NF_CreateSprite(1,i+6+40,2,2,(j*16)+64,(i*16)+32);
                }
                else if (grid[i][j]==4) {
                    NF_CreateSprite(1,i+6+60,3,3,(j*16)+64,(i*16)+32);
                }
                else if (grid[i][j]==5) {
                    NF_CreateSprite(1,i+6+80,4,4,(j*16)+64,(i*16)+32);
                }
            }
        }
    }
}

void cursorDraw() {
    u16 keys = keysHeld();
    touchPosition touchscreen;
    touchRead(&touchscreen);

    if (tics>=29) {
        NF_SpriteFrame(1,5,1);
    }
    else {
        NF_SpriteFrame(1,5,0);
    }

    if (keys & KEY_TOUCH) {
        const int x = touchscreen.px;
        const int y = touchscreen.py;
        if (x>64+8 and x<176+16 and y>40 and y<159) {
            NF_MoveSprite(1,5,((x/8)*8-8),(y/8)*8-8); //through some sorcery i got this to work
        }
    }
    else if (keysUp() & KEY_TOUCH) {
        NF_MoveSprite(1,5,-32,-32);
    }
    // else if (usingButtons==true) {
    //     if (keysDown()&KEY_DOWN) {
    //         buttonHeldLength++;
    //         buttonsY+=16;
    //         if (buttonHeldLength%1==0) {
    //
    //
    //             NF_MoveSprite(1,5,buttonsX,buttonsY);
    //         }
    //     }
    // }
}

void playfieldProcess() {
    if (tics==59) {
        tics=0;
    }
    backgroundScroll();
    cursorDraw();
    if (keysHeld() & KEY_A or keysHeld() & KEY_B or keysHeld() & KEY_X or keysHeld() & KEY_Y or keysHeld() & KEY_UP or
        keysHeld() & KEY_DOWN or keysHeld() & KEY_RIGHT or keysHeld() & KEY_LEFT) {
        usingButtons=true;
    }
    else if (keysHeld()&KEY_TOUCH) {
        usingButtons=false;
    }
}