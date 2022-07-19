#ifndef SKYBOX_H
#define CREDITS_H

#include "Base.h"
#include <irrlicht/irrlicht.h>


class SkyboxManager
{
    public:
        enum Skybox
        {
            CLOUDS,
            NIGHT,
            WOODS,
            CITY,
            FOG,
            SUNSET
        };

        void setSkybox(Skybox skybox)
        {
            if(skybox == CLOUDS)
            {
                pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/clouds_top.jpg"), pb.driver -> getTexture("img/sky/clouds.jpg"), pb.driver -> getTexture("img/sky/clouds.jpg"), pb.driver -> getTexture("img/sky/clouds.jpg"), pb.driver -> getTexture("img/sky/clouds.jpg"), pb.driver -> getTexture("img/sky/clouds.jpg"));
                return;
            }

            if(skybox == NIGHT)
            {
                pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"));
                return;
            }

            if(skybox == FOG)
            {
                pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/fog/fog.jpg"), pb.driver -> getTexture("img/sky/fog/fog.jpg"), pb.driver -> getTexture("img/sky/fog/fog_bottom.jpg"), pb.driver -> getTexture("img/sky/fog/fog_top.jpg"), pb.driver -> getTexture("img/sky/fog/fog_right.jpg"), pb.driver -> getTexture("img/sky/fog/fog_left.jpg"));
                return;
            }

            if(skybox == SUNSET)
            {
                pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/sunset/sunset_top.jpg"), pb.driver -> getTexture("img/sky/sunset/sunset.jpg"), pb.driver -> getTexture("img/sky/sunset/sunset_sun.jpg"), pb.driver -> getTexture("img/sky/sunset/sunset.jpg"), pb.driver -> getTexture("img/sky/sunset/sunset.jpg"), pb.driver -> getTexture("img/sky/sunset/sunset.jpg"));
                return;
            }
        }
};



#endif
