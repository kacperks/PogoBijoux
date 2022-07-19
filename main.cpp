#include <irrlicht.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "TitleMenu.h"
#include "LevelSwitcher.h"
#include "Base.h"
#include "RayCastHandler.h"


LevelSwitcher levelSwitcher;
RayCastHandler rayCastHandler;



int main()
{
    irr::u32 then;
    printf("Welcome to PogoBijoux!\n\n\n You can close the game at any time by pressing ESC.\n\nEnter the # of the level you want to go to: ");
    scanf("%i", &levelSwitcher.currentLevel);


    float leftRightVel;
    float angularVel;
    float rotVel;


    pb.screenWidth = 1000;
    pb.screenHeight = 700;


    pb.device = createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(pb.screenWidth, pb.screenHeight), 16, false, true, false, &pb.er);
    pb.driver = pb.device -> getVideoDriver();
    pb.scnmgr = pb.device -> getSceneManager();
    pb.guiEnv = pb.device -> getGUIEnvironment();

    // Frame title //
    pb.device -> setWindowCaption(L"PogoBijoux by MCL Software | Rate us on Itch.io!!!");

    // Initialize audio engine //
    initAudioEngine();

    // Main menu //
    if(!showTitleScreen())
    {
        return 0;
    }


      ////////////
     // Player //
    ////////////

    pb.player = pb.scnmgr -> addCubeSceneNode(100);

    pb.camera = pb.scnmgr -> addCameraSceneNode(pb.player, irr::core::vector3df(0, 0, 0), pb.player -> getAbsolutePosition(), true);
    pb.camera -> setPosition(irr::core::vector3df(-20, 30, 0));
    pb.camera -> setFarValue(100000.0F);

    // Set shadow color //
    pb.scnmgr -> setShadowColor(irr::video::SColor(150, 0, 0, 0));

    // Store textures in 32-bits; this is needed for parallax mapping //
    pb.driver -> setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);

    loadLevel(levelSwitcher.currentLevel);

    //device -> getCursorControl() -> setVisible(false); // Hide the cursor, currently commented out, as the game currently doesn't use the mouse for controls.


    while(pb.device -> run())
	{
	    pb.driver -> beginScene(true, true, irr::video::SColor(255, 113, 113, 133));


		// Compute frame delta time //
		const irr::u32 now = pb.device -> getTimer() -> getTime();
		const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.0F;
		then = now;


		if(pb.er.isKeyDown(irr::KEY_ESCAPE))
        {
            pb.device -> closeDevice();
        }

        if(pb.er.isKeyDown(irr::KEY_KEY_W))
        {
            angularVel = -pb.speed * frameDeltaTime;
        }

        else if(pb.er.isKeyDown(irr::KEY_KEY_S))
        {
            angularVel = pb.speed * frameDeltaTime;
        }

        else
        {
            angularVel = 0;
        }

        if(pb.er.isKeyDown(irr::KEY_KEY_A))
        {
            leftRightVel = -90;
        }

        else if(pb.er.isKeyDown(irr::KEY_KEY_D))
        {
            leftRightVel = 90;
        }

        else
        {
            leftRightVel = 0;
        }

        if(pb.er.isKeyDown(irr::KEY_F2))
        {
            // Display position and rotation //
            printf("\nCoordinates: %f, %f, %f\nRotation: %f\n\n", pb.player -> getAbsolutePosition().X, pb.player -> getAbsolutePosition().Y, pb.player -> getAbsolutePosition().Z, pb.player -> getRotation().Y);
        }

        if(pb.er.isKeyDown(irr::KEY_F1))
        {
            // Get camera target and print it to output //
            rayCastHandler.isPlayerLookingAtAABB(irr::core::aabbox3d<irr::f32>(irr::core::vector3df(432, 0, -300), irr::core::vector3df(500, 300, 466)));
        }

          /////////////////////
         // Camera rotation //
        /////////////////////

        // Up / Down //
        if(pb.er.isKeyDown(irr::KEY_UP) && pb.verticalCamRot < 100)
        {
            if(pb.verticalCamRot < -10)
                pb.verticalCamRot -= (2 * pb.verticalCamRot / 10) * frameDeltaTime;

            else
                pb.verticalCamRot += 56 * frameDeltaTime;
        }

        else if(pb.er.isKeyDown(irr::KEY_DOWN) && pb.verticalCamRot > -120)
        {
            if(pb.verticalCamRot < -10)
                pb.verticalCamRot += (2 * pb.verticalCamRot / 10) * frameDeltaTime;

            else
                pb.verticalCamRot -= 56 * frameDeltaTime;
        }



        // Left / Right //
        if(pb.er.isKeyDown(irr::KEY_LEFT))
            rotVel = -300 * frameDeltaTime;

        else if(pb.er.isKeyDown(irr::KEY_RIGHT))
            rotVel = 300 * frameDeltaTime;

        else
            rotVel = 0;


        irr::core::vector3df playerRot = pb.player -> getRotation();
        irr::core::vector3df playerPos = pb.player -> getAbsolutePosition();

        pb.camera -> setTarget(irr::core::vector3df(playerPos.X - cos(irr::core::degToRad(playerRot.Y + leftRightVel)) * angularVel, playerPos.Y + pb.verticalCamRot, playerPos.Z + sin(irr::core::degToRad(playerRot.Y + leftRightVel)) * angularVel));

        pb.player -> setRotation(irr::core::vector3df(playerRot.X, playerRot.Y + rotVel, playerRot.Z));
        pb.player -> setPosition(irr::core::vector3df(playerPos.X - cos(irr::core::degToRad(playerRot.Y + leftRightVel)) * angularVel, playerPos.Y, playerPos.Z + sin(irr::core::degToRad(playerRot.Y + leftRightVel)) * angularVel));
        pb.player -> updateAbsolutePosition();

        // Water on Level 7 //
        if(levelSwitcher.currentLevel == 7)
        {
            if(pb.player -> getAbsolutePosition().Y < -80)
            {
                waterSurface -> setRotation(irr::core::vector3df(0, 0, 180));
                pb.showWaterOverlay = true;
            }

            else
            {
                waterSurface -> setRotation(irr::core::vector3df(0, 0, 0));
                pb.showWaterOverlay = false;
            }
        }

        levelSwitcher.checkIfPlayerShouldGoToNextLevel();



		pb.scnmgr -> drawAll();
		pb.drawIngameHUD();
		pb.guiEnv -> drawAll();
		pb.driver -> endScene();
        pb.guiEnv -> clear();
        levelSwitcher.proceedWithLevelSwitch();
    }
    stopAudioEngine();
    pb.device -> drop();
	return 0;
}
