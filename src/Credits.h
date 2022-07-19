#ifndef CREDITS_H
#define CREDITS_H

#include <irrlicht/irrlicht.h>
#include "Base.h"

PogoBijoux pb;

extern "C"
{
    #include "Sound.h"
}


irr::u32 then;


void showCredits()
{
    irr::video::ITexture* bgimg = pb.driver -> getTexture("img/sky/night.jpg");
    irr::video::ITexture* bijouxLogo = pb.driver -> getTexture("img/gui/bijoux.png");

    irr::video::ITexture* info = pb.driver -> getTexture("img/gui/info.png");

    irr::gui::IGUIFont* font = pb.guiEnv -> getFont("img/gui/font.png");

    pb.guiSkin -> setFont(font);
    pb.guiSkin -> setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 255, 255, 255));

    ALuint music = loadSound("audio/music/credits.ogg");
    playSound(0, 0, music);

    float verticalOffset = 0;
    then = pb.device -> getTimer() -> getTime();

    while(pb.device -> run() && !pb.er.isKeyDown(irr::KEY_ESCAPE))
    {
        // Compute frame delta time and then use it to animate the elements.
		const irr::u32 now = pb.device -> getTimer() -> getTime();
		const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 32.0F;
		then = now;

        verticalOffset -= 2 * frameDeltaTime;

        pb.driver -> beginScene(true, true, irr::video::SColor(255, 113, 113, 133));
        pb.driver -> draw2DImage(bgimg, irr::core::rect<irr::s32>(0, 0, pb.screenWidth, pb.screenHeight), irr::core::rect<irr::s32>(0, 0, pb.screenWidth, pb.screenHeight));

        pb.guiEnv -> addImage(bijouxLogo, irr::core::position2d<irr::s32>(pb.screenWidth / 2 - 458 / 2, pb.screenHeight / 2 + (400 + verticalOffset) / 2));
        pb.guiEnv -> addImage(info, irr::core::position2d<irr::s32>(pb.screenWidth / 2 - 100 / 2, pb.screenHeight / 2 + (600 + verticalOffset) / 2));
        irr::gui::IGUIStaticText* credits = pb.guiEnv -> addStaticText(L"Programming:\nMCL\n\nTextures:\nMCL & Looki2000\n\n3-D Models:\nMCL & Looki2000\n\nBeta testing:\nKacper K., Michal K., and Tuncay Y. Buyukadali\n\nFont:\nNoto Sans, licensed under the Open Font License.\n\n\nMusic:\nTitle: Looki2000 & MCL - MenuBijoux\n01. Looki2000 - PogoBijoux\n02. Looki2000 - Spoon of Cinnamon\n03. MCL - Try\n04. MCL - Bijouex\n05. Looki2000 - Electric\n06. MCL - Nine Eleven\n07. MCL - Ingul\n08. MCL - Liminal\n09. MCL - Winter Colors\n10. MCL - Star\n11. Looki2000 - Electronic\n12. semajD - voc-night\n13. MCL - Unfulfilled Expectations\n14. MCL - Life\n15. MCL - FotoBijoux\n16. MCL - Space Above\n17. -\n18. MCL - Hyperspeed\n19. Looki2000 & MCL - Relaxing Bijoux\n20. MCL - Berries\n21. MCL - Weasel\n22. MCL - Waiting\n23. MCL - Alouette\n24. -\n25. Looki2000 - End\nCredits: Looki2000 - After Bijoux\n\nSpecial thanks to:\nBoaty Boat, for making the video that was my first contact with the concept of liminal spaces\n/r/LiminalSpace users, for inspiration\nThomas G., for level ideas.\n\nThank you for playing PogoBijoux!\nDon't forget to rate the game on Itch!\nPRESS 'ESCAPE' TO EXIT", irr::core::rect<irr::s32>(pb.screenWidth / 2 - 312 / 2, pb.screenHeight / 2 + (800 + verticalOffset) / 2, pb.screenWidth, pb.screenHeight));
        credits -> setAlignment(irr::gui::EGUIA_UPPERLEFT, irr::gui::EGUIA_UPPERLEFT, irr::gui::EGUIA_LOWERRIGHT, irr::gui::EGUIA_LOWERRIGHT);

        pb.guiEnv -> drawAll();
        pb.guiEnv -> clear();
        pb.driver -> endScene();
    }
    pb.guiEnv -> clear();

}

#endif
