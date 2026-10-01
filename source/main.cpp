// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: NightFox & Co., 2009-2011
//
// NightFox's Lib Template
// http://www.nightfoxandco.com

#include <iostream>
#include <nds.h>

#include <nf_lib.h>

#include "engine/game.h"

int main(int argc, char **argv)
{
    gameInit();
    while (true)
    {
        // Wait for the screen refresh
        gameLogic();
        scanKeys();
        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);

        // Wait for the screen refresh
        swiWaitForVBlank();

        // Update OAM
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }

    // If this is reached, the program will return to the loader if the loader
    // supports it.
    return 0;
}
