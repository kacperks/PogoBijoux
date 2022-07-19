#ifndef TITLEMENU_H
#define TITLEMENU_H

#include <irrlicht/irrlicht.h>
#include "Base.h"
#include "Credits.h"

extern "C"
{
    #include "Sound.h"
}


int currentlySelected = 0;
irr::u32 oldTime;

void switchSelectedItem(bool item, bool delay)
{
    // Delay to prevent issues when a key is being held down for too long
    if(delay)
    {
        const irr::u32 currentTime = pb.device -> getTimer() -> getTime();
        const irr::u32 interval = (irr::f32)(currentTime - oldTime);
        oldTime = currentTime;
        if(interval < 150)
        {
            return;
        }
    }
    currentlySelected = item ? 1 : 0;
}

bool showTitleScreen()
{
    pb.guiSkin = pb.guiEnv -> getSkin();
    pb.guiEnv -> setSkin(pb.guiSkin);

    irr::video::ITexture* bgimg = pb.driver -> getTexture("img/gui/bgimg.jpg");
    irr::video::ITexture* bijouxLogo = pb.driver -> getTexture("img/gui/bijoux.png");

    irr::video::ITexture* startButton = pb.driver -> getTexture("img/gui/start.jpg");
    irr::video::ITexture* startButtonHighlighted = pb.driver -> getTexture("img/gui/starthlt.jpg");


    irr::video::ITexture* creditsButton = pb.driver -> getTexture("img/gui/credits.jpg");
    irr::video::ITexture* creditsButtonHighlighted = pb.driver -> getTexture("img/gui/creditshlt.jpg");

    irr::video::ITexture* info = pb.driver -> getTexture("img/gui/info.png");

    irr::gui::IGUIFont* font = pb.guiEnv -> getFont("img/gui/font.png");

    pb.guiSkin -> setFont(font);

    int buttonX = pb.screenWidth / 2 - 600 / 2;
    int startButtonY = pb.screenHeight / 2 - 360 / 2;
    int creditsButtonY = pb.screenHeight / 2 + 100 / 2;


    ALuint music = loadSound("audio/music/title.ogg");
    playSound(0, 1, music);



    while(pb.device -> run() && !pb.er.isKeyDown(irr::KEY_RETURN))
    {
        if(pb.er.isKeyDown(irr::KEY_ESCAPE))
        {
            pb.driver -> endScene();
            return false;
        }

        if(pb.er.isKeyDown(irr::KEY_UP) || pb.er.isKeyDown(irr::KEY_DOWN) || pb.er.isKeyDown(irr::KEY_TAB))
        {

            switchSelectedItem(currentlySelected != 0 ? false : true, true);
        }

        int cursorX = pb.device -> getCursorControl() -> getPosition().X;
        int cursorY = pb.device -> getCursorControl() -> getPosition().Y;

        if(cursorX >= buttonX && cursorY >= startButtonY && cursorX <= buttonX + 600 && cursorY <= startButtonY + 200)
        {
            switchSelectedItem(false, false);
        }

        else if(cursorX >= buttonX && cursorY >= creditsButtonY && cursorX <= buttonX + 600 && cursorY <= creditsButtonY + 200)
        {
            switchSelectedItem(true, false);
        }



        if(pb.er.isMouseDown())
        {
            if(!(cursorX >= buttonX && cursorY >= creditsButtonY && cursorX <= buttonX + 600 && cursorY <= creditsButtonY + 200) && !(cursorX >= buttonX && cursorY >= startButtonY && cursorX <= buttonX + 600 && cursorY <= startButtonY + 200))
            {
                currentlySelected = -1;
            }

            else
            {
                pb.guiEnv -> clear();
                pb.driver -> endScene();
            }

            if(currentlySelected == 1)
            {
                showCredits();
                //return;
            }

            if(currentlySelected == 0)
            {
                return true;
            }
        }

        pb.driver -> beginScene(true, true, irr::video::SColor(255, 113, 113, 133));
        pb.driver -> draw2DImage(bgimg, irr::core::rect<irr::s32>(0, 0, pb.screenWidth, pb.screenHeight), irr::core::rect<irr::s32>(0, 0, pb.screenWidth, pb.screenHeight));
        font -> draw(L"Copyright (c) 2020-2022 MCL Software.", irr::core::rect<irr::s32>(0, 0, pb.screenWidth, pb.screenHeight), irr::video::SColor(255, 0, 0, 0));

        pb.guiEnv -> addImage(bijouxLogo, irr::core::position2d<irr::s32>(pb.screenWidth / 2 - 458 / 2, pb.screenHeight / 2 - 620 / 2));
        pb.guiEnv -> addImage(currentlySelected == 0 ? startButtonHighlighted : startButton, irr::core::position2d<irr::s32>(buttonX, startButtonY));
        pb.guiEnv -> addImage(currentlySelected == 1 ? creditsButtonHighlighted : creditsButton, irr::core::position2d<irr::s32>(buttonX, creditsButtonY));
        pb.guiEnv -> addImage(info, irr::core::position2d<irr::s32>(pb.screenWidth / 2 - 100 / 2, pb.screenHeight / 2 + 540 / 2));

        pb.guiEnv -> drawAll();
        pb.guiEnv -> clear();
        pb.driver -> endScene();
    }
    pb.guiEnv -> clear();
    return true;
}

#endif
