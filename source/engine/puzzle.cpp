//
// Created by tailofhell on 9/30/26.
//

#include "puzzle.h"

#include <iostream>
#include <nds.h>
#include <nf_lib.h>
static s8 bgX;
static s8 bgY;
static s8 tics;
using namespace std;

void playfieldInit(const int screen) {
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

    NF_VramSpriteGfx(screen,0,0,true);
    NF_VramSpritePal(screen,0,0);
    NF_VramSpriteGfx(screen,1,1,true);
    NF_VramSpritePal(screen,1,1);

    NF_LoadTiledBg("bg/background","background",256,256);
    NF_CreateTiledBg(0,3,"background");
    NF_CreateTiledBg(1,3,"background");
    NF_LoadTiledBg("bg/board","board",256,256);
    NF_CreateTiledBg(0,2,"board");
    NF_CreateTiledBg(1,2,"board");
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

void cursorDraw() {

}

void playfieldDraw() {
    backgroundScroll();
}