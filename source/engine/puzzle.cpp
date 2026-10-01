//
// Created by tailofhell on 9/30/26.
//

#include "puzzle.h"

#include <iostream>
#include <nf_lib.h>
static s8 bgX;
static s8 bgY;
static s8 tics;
using namespace std;

void playfieldInit(const int screen) {
    NF_LoadSpriteGfx("sprite/board",18,16,16);
    NF_LoadSpritePal("sprite/board",18);
    NF_LoadSpriteGfx("sprite/petalRed",0,16,16);
    NF_LoadSpritePal("sprite/petalRed",0);
    NF_LoadSpriteGfx("sprite/petalBlue",1,16,16);
    NF_LoadSpritePal("sprite/petalBlue",1);

    NF_VramSpriteGfx(screen,0,0,true);
    NF_VramSpritePal(screen,0,0);
    NF_VramSpriteGfx(screen,1,1,true);
    NF_VramSpritePal(screen,1,1);
    NF_VramSpriteGfx(screen,18,18,false);
    NF_VramSpritePal(screen,18,15);

    NF_LoadTiledBg("bg/background","background",256,256);
    NF_CreateTiledBg(0,3,"background");
    NF_CreateTiledBg(1,3,"background");

    NF_CreateSprite(screen,18,18,15,32,16);
    NF_CreateSprite(screen,18,18,15,32,16);
    for (int i=0;i<(8*16)+2;i++) {

    }
}

void backgroundScroll() {
    tics++;
    if (tics%2==0) {
        bgX++;
        bgY++;
    }
    NF_ScrollBg(1,3,bgX,bgY);
    NF_ScrollBg(0,3,bgX+64,bgY);
}

void playfieldDraw() {
    backgroundScroll();
    NF_SpriteFrame(1,18,5);
    NF_SpriteFrame(1,18,4);
}