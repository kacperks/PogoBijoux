#include "Levels.h"




class LevelSwitcher
{
    public:
        int currentLevel;
        void nextLevel(bool calledFromConsensualLevel)
        {
            currentLevel++;

            pb.player -> removeAnimators();
            pb.scnmgr -> addToDeletionQueue(pb.rootNode);

            currentLevel = loadLevel(currentLevel);
            pb.showLoadingOverlay = false;
            pb.showNextLevelOverlay = false;
        }

        void proceedWithLevelSwitch()
        {
            if(flag)
            {
                flag = false;
                nextLevel(true);
            }
        }

        void playerCanProgress(bool calledFromConsensualLevel)
        {
            if(calledFromConsensualLevel)
            {
                pb.showNextLevelOverlay = true;
            }

            if((calledFromConsensualLevel && pb.er.isKeyDown(irr::KEY_RETURN)) || !calledFromConsensualLevel)
            {
                pb.showLoadingOverlay = true;
                flag = true;
            }
        }

        void checkIfPlayerShouldGoToNextLevel()
        {

            if(currentLevel == 1)
            {
                if(pb.player -> getAbsolutePosition().Y < -400)
                {
                    playerCanProgress(false);
                }
            }

            else if(currentLevel == 2)
            {
                irr::core::aabbox3d<irr::f32> aabb = irr::core::aabbox3d<irr::f32>(irr::core::vector3df(21481, 5, 20900), irr::core::vector3df(21481, 400, 21000));
                if(pb.isPlayerCollidingWithAABB(aabb))
                {
                    playerCanProgress(true);
                }

                else
                {
                    pb.showNextLevelOverlay = false;
                }
            }


            else if(currentLevel == 4)
            {
                if(pb.player -> getAbsolutePosition().Z < -232)
                {
                    playerCanProgress(true);
                }

                else
                {
                    pb.showNextLevelOverlay = false;
                }
            }


            else if(currentLevel == 6)
            {
                if(pb.player -> getAbsolutePosition().X < -310)
                {
                    playerCanProgress(true);
                }

                else
                {
                    pb.showNextLevelOverlay = false;
                }
            }

            else if(currentLevel == 7)
            {
                if(pb.player -> getAbsolutePosition().Z > 270)
                {
                    playerCanProgress(true);
                }

                else
                {
                    pb.showNextLevelOverlay = false;
                }
            }


            else if(currentLevel == 9)
            {
                irr::core::aabbox3d<irr::f32> aabb = irr::core::aabbox3d<irr::f32>(irr::core::vector3df(1587, 0, 27510), irr::core::vector3df(1768, 400, 27625));
                if(pb.isPlayerCollidingWithAABB(aabb))
                {
                    playerCanProgress(true);
                }

                else
                {
                    pb.showNextLevelOverlay = false;
                }
            }

            else if(currentLevel == 10)
            {

            }

            else if(currentLevel == 11)
            {

            }

            else if(currentLevel == 12)
            {

            }

            else if(currentLevel == 13)
            {

            }

            else if(currentLevel == 14)
            {
                if(pb.player -> getAbsolutePosition().Y < -400)
                {
                    playerCanProgress(false);
                }
            }

            else if(currentLevel == 15)
            {
                irr::core::aabbox3d<irr::f32> aabb = irr::core::aabbox3d<irr::f32>(irr::core::vector3df(-778, 0, -20), irr::core::vector3df(-817, 400, 215));
                if(pb.isPlayerCollidingWithAABB(aabb))
                {
                    playerCanProgress(true);
                }

                else
                {
                    pb.showNextLevelOverlay = false;
                }
            }

            else if(currentLevel == 16)
            {

            }

            else if(currentLevel == 17)
            {

            }

            else if(currentLevel == 18)
            {

            }

            else if(currentLevel == 19)
            {

            }

            else if(currentLevel == 20)
            {

            }

            else if(currentLevel == 21)
            {

            }

            else if(currentLevel == 22)
            {
                irr::core::aabbox3d<irr::f32> aabb = irr::core::aabbox3d<irr::f32>(irr::core::vector3df(-390, 80, -200), irr::core::vector3df(-390, 130, -166));
                if(pb.isPlayerCollidingWithAABB(aabb))
                {
                    playerCanProgress(true);
                }

                else
                {
                    pb.showNextLevelOverlay = false;
                }
            }

            else if(currentLevel == 23)
            {

            }

            else if(currentLevel == 24)
            {

            }

            else if(currentLevel == 25)
            {
                if(pb.player -> getAbsolutePosition().Z > 1780)
                {
                    pb.player -> removeAnimators();
                    pb.scnmgr -> addToDeletionQueue(pb.rootNode);
                    showCredits();
                    pb.device -> closeDevice();
                }
            }

            else
            {
                irr::core::aabbox3d<irr::f32> aabb = irr::core::aabbox3d<irr::f32>(irr::core::vector3df(432, 0, -300), irr::core::vector3df(500, 300, 466));
                if(pb.isPlayerCollidingWithAABB(aabb))
                {
                    playerCanProgress(false);
                }
            }
        }

    private:
        bool flag = false;
};

