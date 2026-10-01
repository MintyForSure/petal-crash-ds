//
// Created by tailofhell on 9/30/26.
//

#include "game.h"

#include <nf_lib.h>
#include <nds.h>
#include <filesystem.h>
#include "puzzle.h"

void gameInit() {
    gameState=1;
    NF_Set2D(0,0);
    NF_Set2D(1,0);
    nitroFSInit(NULL);
    NF_SetRootFolder("NITROFS");
    // Initialize tiled backgrounds system
    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(0);
    NF_InitTiledBgSys(1);

    // Initialize sprite system
    NF_InitSpriteBuffers();
    NF_InitSpriteSys(0);
    NF_InitSpriteSys(1);

    playfieldInit(1);
    //playfieldInit(1);
}

void gameLogic() {
    switch (gameState) {
        case 0: //menus
            break;
        case 1: //actively in game
            playfieldProcess();
            break;
    }
}