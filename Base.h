#ifndef BASE_H
#define BASE_H

#include <irrlicht.h>
#include "EventReceiver.h"
class PogoBijoux
{
    public:
        EventReceiver er;
        bool enableBump = true;
        bool enableShadows = true;
        bool showWaterOverlay = false;
        bool showLoadingOverlay = false;
        bool showNextLevelOverlay = false;
        int speed = 400;
        int screenWidth = 800;
        int screenHeight = 600;
        irr::scene::ISceneNode* rootNode;
        irr::IrrlichtDevice* device;
        float verticalCamRot = 50;
        irr::scene::ISceneNode* player;
        irr::scene::ICameraSceneNode* camera;
        irr::video::IVideoDriver* driver;
        irr::scene::ISceneManager* scnmgr;
        irr::gui::IGUIEnvironment* guiEnv;
        irr::gui::IGUISkin* guiSkin;

        bool isPlayerCollidingWithAABB(irr::core::aabbox3d<irr::f32> aabb)
        {
            irr::core::aabbox3d<irr::f32> playerAABB = player -> getTransformedBoundingBox();
            return playerAABB.intersectsWithBox(aabb);
        }

        void drawIngameHUD()
        {
            if(showWaterOverlay)
            {
                driver -> draw2DRectangle(irr::video::SColor(119, 5, 107, 200), irr::core::rect<irr::s32>(0, 0, screenWidth, screenHeight));
            }

            if(showLoadingOverlay)
            {
                guiEnv -> addImage(driver -> getTexture("img/gui/loading.png"), irr::core::position2d<irr::s32>(screenWidth / 2 - 600 / 2, screenHeight / 2 - 200 / 2));
            }

            if(showNextLevelOverlay)
            {
                guiEnv -> addStaticText(L"Would like to go through the door (and go to the next level)?", irr::core::rect<irr::s32>(0, screenHeight / 2 + 600 / 2, screenWidth, screenHeight));
            }
        }
};

#endif
