#include "SoundHandler.h"
#include "Skybox.h"

irr::scene::ISceneNodeAnimatorCollisionResponse* anim;
irr::scene::ISceneNode* waterSurface;

SoundHandler soundHandler;
SkyboxManager skyboxManager;

int loadLevel(int level)
{
    // Music
    std::string filename = "audio/music/" + std::to_string(level) + ".ogg";
    soundHandler.playMusic(filename.c_str(), true);

    if(level == 1)
    {
        // Level 1
        // Sky & Clouds

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(-196, 110, -104));
        pb.player -> setRotation(irr::core::vector3df(0, 8, 0));
        pb.verticalCamRot = 40;


        // Skybox
        skyboxManager.setSkybox(skyboxManager.CLOUDS);

        // Walkway
        irr::scene::IMeshSceneNode* walkway;

        walkway = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl1/lvl1walkway.obj"));
        pb.scnmgr -> getMeshManipulator() -> makePlanarTextureMapping(walkway -> getMesh(), .05f);
        walkway -> setScale(irr::core::vector3df(200, 30, 200));
        walkway -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        walkway -> setMaterialTexture(0, pb.driver -> getTexture("img/sky/clouds.jpg"));

        pb.rootNode -> addChild(walkway);

        // Controls info board //
        irr::scene::IMeshSceneNode* board;
        board = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/board.obj"));
        board -> setScale(irr::core::vector3df(130, 130, 130));
        board -> setPosition(irr::core::vector3df(500, 270, 0));
        board -> setRotation(irr::core::vector3df(0, 270, 0));
        board -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        board -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/controls.jpg"));

        pb.rootNode -> addChild(board);

        // 'Welcome To PogoBijoux' //
        irr::scene::IBillboardSceneNode* welcome = pb.scnmgr -> addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(500, 500), irr::core::vector3df(0, 200, 0));
        welcome -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        welcome -> setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        welcome -> setPosition(irr::core::vector3df(-300, 300, 0));
        welcome -> setMaterialTexture(0, pb.driver -> getTexture("img/billboards/welcome.png"));

        pb.rootNode -> addChild(welcome);

        irr::scene::ITriangleSelector* ts = pb.scnmgr -> createTriangleSelector(pb.scnmgr -> getMesh("3d/lvl1/lvl1walkway.obj"), walkway);
        walkway -> setTriangleSelector(ts);

        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));

        ts -> drop();
        pb.player -> addAnimator(anim);
        anim -> drop();
    }

    if(level == 2)
    {
        // Level 2
        // Parking Lot
        pb.player -> setPosition(irr::core::vector3df(18440, 200, 17000));
        pb.player -> setRotation(irr::core::vector3df(0, -64, 0));

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();
        pb.scnmgr -> getRootSceneNode() -> setMaterialFlag(irr::video::EMF_FOG_ENABLE , true);
        pb.driver -> setFog(irr::video::SColor(0, 0, 0, 10), irr::video::EFT_FOG_LINEAR, 0x4000, 0x5000, .003f, true, false);

        // Night skybox //
        skyboxManager.setSkybox(skyboxManager.NIGHT);

        // Floor //
        irr::scene::IMeshSceneNode* floor;
        floor = pb.scnmgr -> addCubeSceneNode(irr::f32(1.0f), 0, -1, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0x2p20, 0, 0x2p20));
        floor -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        floor -> setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
        pb.rootNode -> addChild(floor);
        pb.scnmgr -> getMeshManipulator() -> makePlanarTextureMapping(floor -> getMesh(), 300.0f);
        floor -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/parking.jpg"));

        // Lamp posts //
        irr::scene::IMeshSceneNode* lamppost[401];
        irr::scene::ILightSceneNode* light;
        light = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(0, 20, 0), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 800000.0f);
        light -> setRotation(irr::core::vector3df(0, 20, 0));
        light -> setLightType(irr::video::ELT_DIRECTIONAL);

        int lamppostCounter = 0;

        for(int x = 0; x < 20; x++)
        {
            for(int z = 0; z < 20; z++)
            {
                lamppostCounter++;

                lamppost[lamppostCounter] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/lamppost.obj"));
                lamppost[lamppostCounter] -> setScale(irr::core::vector3df(50, 50, 50));
                lamppost[lamppostCounter] -> setPosition(irr::core::vector3df(0x900 * x, 0, 0x900 * z));
                lamppost[lamppostCounter] -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
                lamppost[lamppostCounter] -> setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
                lamppost[lamppostCounter] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/metal.jpg"));
                lamppost[lamppostCounter] -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/bump/voltagen.jpg"));
                pb.rootNode -> addChild(lamppost[lamppostCounter]);
                //lamppost[lamppostCounter] -> drop();
            }
        }


        // Exit door //
        irr::scene::IMeshSceneNode* door = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/door.obj"));
        door -> setScale(irr::core::vector3df(80, 80, 80));
        door -> setPosition(irr::core::vector3df(21481, 5, 20900));
        door -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        door -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/door1.jpg"));
        door -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/wood.jpg"));

        pb.rootNode -> addChild(door);
        //irr::scene::ITriangleSelector* ts = pb.scnmgr -> createTriangleSelector(lamppost[0] -> getMesh(), lamppost[0]);
        //lamppost[0] -> setTriangleSelector(ts);

        //anim = pb.scnmgr -> createCollisionResponseAnimator(ts, player, irr::core::vector3df(30, 130, 30), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 30, 0));

        pb.rootNode -> addChild(floor);


        //ts -> drop();
        //player -> addAnimator(anim);
        //anim -> drop();
    }



    else if(level == 4)
    {
        // Level 4
        // Facility

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(-196, 110, -104));
        pb.player -> setRotation(irr::core::vector3df(0, 12, 0));
        pb.verticalCamRot = 40;

        // Skydome //
        pb.scnmgr -> addSkyDomeSceneNode(pb.driver -> getTexture("img/sky/clouds_dome.jpg"), 16, 8, 1, 2, 1000, 0, -1);



        // Normal map textures //
        irr::video::ITexture* normalMap[2];
        normalMap[0] = pb.driver -> getTexture("img/bump/vinyln.jpg");
        normalMap[1] = pb.driver -> getTexture("img/bump/lime-walln.jpg");
        pb.driver -> makeNormalMapTexture(normalMap[0], 9.0f);
        pb.driver -> makeNormalMapTexture(normalMap[1], 9.0f);

        // Main facility model //

        irr::scene::IMesh* tangFacility = pb.scnmgr -> getMeshManipulator() -> createMeshWithTangents(pb.scnmgr -> getMesh("3d/lvl4/facility.obj"));

        irr::scene::IMeshSceneNode* facility = pb.scnmgr -> addMeshSceneNode(tangFacility);



        facility -> setMaterialFlag(irr::video::EMF_LIGHTING, true);
        facility -> setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);

        if(pb.enableBump)
        {
            facility -> setMaterialType(irr::video::EMT_PARALLAX_MAP_SOLID);
        }

        facility -> setScale(irr::core::vector3df(60, 60, 60));
        facility -> setPosition(irr::core::vector3df(0, 0, 0));
        facility -> getMaterial(1).MaterialTypeParam = 1.0f / 16.0f;
        facility -> getMaterial(1).Shininess = 0.0f;
        facility -> getMaterial(1).SpecularColor.set(0, 0, 0, 0);
        facility -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/vinyl.jpg"));
        facility -> getMaterial(0).setTexture(1, normalMap[0]);
        facility -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/lime-wall.jpg"));
        facility -> getMaterial(1).setTexture(1, normalMap[1]);
        facility -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/metal.jpg"));
        facility -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/door2.jpg"));
        facility -> getMaterial(4).setTexture(0, pb.driver -> getTexture("img/object_textures/white-wall.jpg"));


        // Lights //

        irr::scene::ILightSceneNode* light[1];
        light[0] = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-250, 140, 9), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 80000.0f);
        light[0] -> setRotation(irr::core::vector3df(140, 270, 0));
        light[0] -> setLightType(irr::video::ELT_SPOT);

        light[1] = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(634, 140, 50), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 80000.0f);
        light[1] -> setRotation(irr::core::vector3df(140, -189, 0));
        light[1] -> setLightType(irr::video::ELT_SPOT);


        irr::scene::ITriangleSelector* ts = pb.scnmgr -> createTriangleSelector(pb.scnmgr -> getMesh("3d/lvl4/facility.obj"), facility);
        facility -> setTriangleSelector(ts);

        pb.rootNode -> addChild(facility);

        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
        ts -> drop();
        pb.player -> addAnimator(anim);
        anim -> drop();
    }
/*
    else if(level == 5)
    {
        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        irr::scene::IMeshSceneNode* room = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl8/randomness.obj"));
        room -> setScale(irr::core::vector3df(400, 400, 400));
        room -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        room -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/room.jpg"));

        pb.rootNode -> addChild(room);
    }*/

    else if(level == 6)
    {
        // Level 6
        // Backyard

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(0, 200, 0));

        // Cloduy Skybox //
        skyboxManager.setSkybox(skyboxManager.CLOUDS);


        // Backyard model //
        irr::scene::IMeshSceneNode* backyard = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl6/backyard.obj"));
        backyard -> setScale(irr::core::vector3df(60, 60, 60));
        backyard -> setPosition(irr::core::vector3df(0, 0, 0));
        backyard -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        backyard -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/green-wall.jpg"));
        backyard -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/door1.jpg"));
        backyard -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/grass.jpg"));
        backyard -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/roof.jpg"));
        backyard -> getMaterial(4).setTexture(0, pb.driver -> getTexture("img/object_textures/fence.jpg"));

        // Other houses in the background //
        irr::scene::IMeshSceneNode* house[3];

        for(int i = 0; i < 3; i++)
        {
            house[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/house.obj"), 0, -1, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(100, 100, 100));
            house[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
            house[i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/door1.jpg"));
            house[i] -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/roof.jpg"));
            house[i] -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/white-wall.jpg"));
            house[i] -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/window1.png"));
            pb.rootNode -> addChild(house[i]);
        }
        house[0] -> setPosition(irr::core::vector3df(1000, -40, -800));
        house[1] -> setPosition(irr::core::vector3df(2000, -40, -1000));
        house[2] -> setPosition(irr::core::vector3df(-1000, -40, -1000));


        irr::scene::ITriangleSelector* ts = pb.scnmgr -> createTriangleSelector(backyard -> getMesh(), backyard);
        backyard -> setTriangleSelector(ts);

        pb.rootNode -> addChild(backyard);

        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
        ts -> drop();
        pb.player -> addAnimator(anim);
        anim -> drop();
    }

    else if(level == 7)
    {
        // Level 7
        // Ingul

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(-273, 80, -266));
        pb.player -> setRotation(irr::core::vector3df(0, -75, 0));


        pb.verticalCamRot = 30;

        // Night skybox //
        irr::scene::ISceneNode* skybox = pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"));



        // Main mesh //
        irr::scene::IMeshSceneNode* ingul = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl7/ingul.obj"));
        ingul -> setScale(irr::core::vector3df(50, 50, 50));

        ingul -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/door1.jpg"));
        ingul -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/pink-tiles.jpg"));
        ingul -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/green-tiles.jpg"));
        ingul -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/metal.jpg"));
        ingul -> getMaterial(4).setTexture(0, pb.driver -> getTexture("img/object_textures/green-wall.jpg"));
        ingul -> getMaterial(5).setTexture(0, pb.driver -> getTexture("img/object_textures/green-wall.jpg"));


        pb.rootNode -> addChild(ingul);

        // Windows
        irr::scene::IMeshSceneNode* windows = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl7/ingul-windows.obj"));
        windows -> setScale(irr::core::vector3df(50, 50, 50));
        windows -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/glass.png"));
        windows -> setMaterialTexture(1, pb.driver -> getTexture("img/object_textures/glass.png"));
        windows -> setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        windows -> setMaterialFlag(irr::video::EMF_LIGHTING, false);

        // Water spouts
        irr::scene::IMeshSceneNode* spout[2];
        for(int i = 0; i < 3; i++)
        {
            spout[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl7/water-pipe.obj"));
            spout[i] -> setScale(irr::core::vector3df(50, 50, 50));
            spout[i] -> setPosition(irr::core::vector3df(i * -100 + 100, 0, 0));
            spout[i] -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/baptpool.jpg"));
            pb.rootNode -> addChild(spout[i]);
        }


        // Water
        irr::scene::IAnimatedMesh* water = pb.scnmgr -> addHillPlaneMesh("water", irr::core::dimension2d<irr::f32>(6.7, 10), irr::core::dimension2d<irr::u32>(100, 100), 0, 0, irr::core::dimension2d<irr::f32>(0, 0), irr::core::dimension2d<irr::f32>(5, 5));
        waterSurface = pb.scnmgr -> addWaterSurfaceSceneNode(water -> getMesh(0), 1.0f, 500.0f, 60.0f);

        waterSurface -> setPosition(irr::core::vector3df(0, -10, 0));

        // Materials 'n' textures
        waterSurface -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/water.jpg"));
        waterSurface -> setMaterialTexture(1, pb.driver -> getTexture("img/object_textures/water.jpg"));
        waterSurface -> setMaterialType(irr::video::EMT_TRANSPARENT_REFLECTION_2_LAYER);


        pb.rootNode -> addChild(waterSurface);


        // Light
        irr::scene::ILightSceneNode* light = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-550, 60, 200), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 80000.0f);
        light -> setRotation(irr::core::vector3df(140, 270, 0));
        light -> setLightType(irr::video::ELT_SPOT);

        irr::scene::ILightSceneNode* light1 = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-550, 80, -300), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 80000.0f);
        light1 -> setRotation(irr::core::vector3df(160, 270, 0));
        light1 -> setLightType(irr::video::ELT_SPOT);

        irr::scene::ILightSceneNode* light2 = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-550, 100, -50), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 80000.0f);
        light2 -> setRotation(irr::core::vector3df(180, 270, -30));
        light2 -> setLightType(irr::video::ELT_SPOT);

        irr::scene::ILightSceneNode* flashlight = pb.scnmgr -> addLightSceneNode(pb.player, irr::core::vector3df(0, 0, 0), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 8000.0f);

        pb.rootNode -> addChild(light);
        pb.rootNode -> addChild(light1);
        pb.rootNode -> addChild(light2);
        pb.rootNode -> addChild(flashlight);

        // Triangle selector
        irr::scene::ITriangleSelector* tsMain = pb.scnmgr -> createOctreeTriangleSelector(ingul -> getMesh(), ingul, 64);
        ingul -> setTriangleSelector(tsMain);
        anim = pb.scnmgr -> createCollisionResponseAnimator(tsMain, pb.player, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
        pb.player -> addAnimator(anim);

        tsMain -> drop();
        anim -> drop();
    }



    else if(level == 9)
    {
        // Level 9
        // Winter Neighborhood @ Night

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(1000, 200, 9978));
        pb.player -> setRotation(irr::core::vector3df(0, 256, 0));
        pb.speed = 400;

        // Night skybox
        irr::scene::ISceneNode* skybox = pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"));


        irr::scene::IMeshSceneNode* road = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl21/road.obj"), 0, -1, irr::core::vector3df(8000, 0, 3000), irr::core::vector3df(0, 0, 0), irr::core::vector3df(100, 10, 100));
        road -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/roof-snow.jpg"));
        road -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/bump/asphaltn.jpg"));

        road -> setMaterialFlag(irr::video::EMF_LIGHTING, false);

        irr::scene::IMeshSceneNode* house[50];

        for(int i = 0; i <= 25; i += 25)
        {
            for(int j = 0; j < 25; j++)
            {
                house[j + i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/house.obj"), 0, -1, irr::core::vector3df(i * 100, 0, 1200 * j), irr::core::vector3df(0, i > 0 ? 180 : 0, 0), irr::core::vector3df(120, 120, 120));
                house[j + i] -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
                house[j + i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/door1.jpg"));
                house[j + i] -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/roof-snow.jpg"));
                house[j + i] -> getMaterial(2).setTexture(0, (j + i) % 2 ? pb.driver -> getTexture("img/object_textures/lime-wall.jpg") : pb.driver -> getTexture("img/object_textures/white-wall.jpg"));
                house[j + i] -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/window1.png"));
                pb.rootNode -> addChild(house[j + i]);
            }
        }

        irr::scene::IMeshSceneNode* door = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/door.obj"));
        door -> setScale(irr::core::vector3df(80, 80, 80));
        door -> setPosition(irr::core::vector3df(1681, 5, 27586));
        door -> setRotation(irr::core::vector3df(0, 270, 0));
        door -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        door -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/door1.jpg"));
        door -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/wood.jpg"));
        pb.rootNode -> addChild(door);
    }

    else if(level == 10)
    {
        // Level 10
        // Star

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(0, 200, 0));
        pb.player -> setRotation(irr::core::vector3df(0, 256, 0));


        // House //
        irr::scene::IMeshSceneNode* house;

        house = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/house.obj"), 0, -1, irr::core::vector3df(100, 0, 800), irr::core::vector3df(0, 0, 0), irr::core::vector3df(120, 120, 120));
        house -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        house -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/door1.jpg"));
        house -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/garage-door.jpg"));
        house -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/white-wall.jpg"));
        house -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/window1.png"));
        pb.rootNode -> addChild(house);


        // Star Billboard //
        irr::scene::IBillboardSceneNode* star = pb.scnmgr -> addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(256, 256), irr::core::vector3df(0, 0, 0));
        star -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        star -> setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        star -> setPosition(irr::core::vector3df(-300, 300, 0));
        star -> setMaterialTexture(0, pb.driver -> getTexture("img/billboards/star.png"));
        pb.rootNode -> addChild(star);

        // Exit door //
        irr::scene::IMeshSceneNode* door = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/door.obj"));
        door -> setScale(irr::core::vector3df(58, 58, 59));
        door -> setPosition(irr::core::vector3df(450, 0, 565));
        door -> setRotation(irr::core::vector3df(0, 180, 0));
        door -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        door -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/door1.jpg"));
        door -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/wood.jpg"));
        door -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/gui/bgimg.jpg"));

        pb.rootNode -> addChild(door);
    }

    else if(level == 11)
    {
        // Level 11
        // Office

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        // City skybox (temporary) //
        irr::scene::ISceneNode* skybox = pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/city1-5.jpg"), pb.driver -> getTexture("img/sky/city1-4.jpg"), pb.driver -> getTexture("img/sky/city1-1.jpg"), pb.driver -> getTexture("img/sky/city1-3.jpg"), pb.driver -> getTexture("img/sky/city1-0.jpg"), pb.driver -> getTexture("img/sky/city1-2.jpg"));


        pb.player -> setPosition(irr::core::vector3df(0, 200, 0));
        pb.player -> setRotation(irr::core::vector3df(0, 256, 0));


        irr::scene::IMeshSceneNode* chair[3];

        for(int i = 0; i < 3; i++)
        {
            chair[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/chair.obj"));
            chair[i] -> setScale(irr::core::vector3df(50, 50, 50));
            chair[i] -> setPosition(irr::core::vector3df(100 - i * 150, 0, 260));
            chair[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
            chair[i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/chair.jpg"));
            pb.rootNode -> addChild(chair[i]);
        }


        // Main office model //
        irr::scene::IMeshSceneNode* office = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl11/office.obj"));
        office -> setScale(irr::core::vector3df(50, 50, 50));
        office -> setPosition(irr::core::vector3df(35, 0, 0));
        office -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        office -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/dropped-ceiling.jpg"));
        office -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/wood.jpg"));
        office -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/blue-wall.jpg"));
        office -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/blue-wall.jpg"));
        office -> getMaterial(4).setTexture(0, pb.driver -> getTexture("img/object_textures/monitor.jpg"));
        office -> getMaterial(5).setTexture(0, pb.driver -> getTexture("img/object_textures/pc.jpg"));

        pb.rootNode -> addChild(office);

        irr::scene::ITriangleSelector* ts = pb.scnmgr -> createOctreeTriangleSelector(pb.scnmgr -> getMesh("3d/lvl11/office-collision.obj"), office, 512);
        office -> setTriangleSelector(ts);


        // Exit door //
        irr::scene::IMeshSceneNode* door = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/door.obj"));
        door -> setScale(irr::core::vector3df(40, 40, 40));
        door -> setRotation(irr::core::vector3df(0, 180, 0));
        door -> setPosition(irr::core::vector3df(-330, 0, -56));
        door -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        door -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/door1.jpg"));
        door -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/wood.jpg"));
        door -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/sky/clouds.jpg"));

        pb.rootNode -> addChild(door);

        // Create a collision response animator and add it to the player //
        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));

        ts -> drop();
        pb.player -> addAnimator(anim);
        anim -> drop();
    }

    else if(level == 12)
    {
        // Level 12
        // Night

        // Night skybox
        irr::scene::ISceneNode* skybox = pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"));


        pb.player -> setPosition(irr::core::vector3df(-800, 150, -65200));

        // Normal map textures
        irr::video::ITexture* normalMap[6];
        normalMap[0] = pb.driver -> getTexture("img/bump/asphaltn.jpg");
        normalMap[1] = pb.driver -> getTexture("img/bump/concreten.jpg");
        normalMap[2] = pb.driver -> getTexture("img/bump/fencen.jpg");
        normalMap[3] = pb.driver -> getTexture("img/bump/garage-doorn.jpg");
        normalMap[4] = pb.driver -> getTexture("img/bump/grassn.jpg");
        normalMap[5] = pb.driver -> getTexture("img/bump/voltagen.jpg");
        pb.driver -> makeNormalMapTexture(normalMap[0], 9.0f);
        pb.driver -> makeNormalMapTexture(normalMap[1], 9.0f);
        pb.driver -> makeNormalMapTexture(normalMap[2], 9.0f);
        pb.driver -> makeNormalMapTexture(normalMap[3], 9.0f);
        pb.driver -> makeNormalMapTexture(normalMap[4], 9.0f);
        pb.driver -> makeNormalMapTexture(normalMap[5], 9.0f);

        irr::scene::IMesh* tangEnvironment = pb.scnmgr -> getMeshManipulator() -> createMeshWithTangents(pb.scnmgr -> getMesh("3d/lvl12/night.obj"));
        irr::scene::IMeshSceneNode* environment = pb.scnmgr -> addMeshSceneNode(tangEnvironment);

        environment -> setScale(irr::core::vector3df(100, 100, 100));
        environment -> setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
        environment -> setMaterialType(irr::video::EMT_PARALLAX_MAP_SOLID);
        environment -> setMaterialFlag(irr::video::EMF_LIGHTING, true);
        environment -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/parking.jpg"));
        environment -> getMaterial(0).setTexture(1, normalMap[0]);

        environment -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/concrete.png"));
        environment -> getMaterial(1).setTexture(1, normalMap[1]);

        environment -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/fence.jpg"));
        environment -> getMaterial(2).setTexture(1, normalMap[2]);

        environment -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/garage-door.jpg"));
        environment -> getMaterial(3).setTexture(1, normalMap[3]);

        environment -> getMaterial(4).setTexture(0, pb.driver -> getTexture("img/object_textures/grass.jpg"));
        environment -> getMaterial(4).setTexture(1, normalMap[4]);

        environment -> getMaterial(4).MaterialTypeParam = 1.0F / 64.0F;

        environment -> getMaterial(5).setTexture(0, pb.driver -> getTexture("img/object_textures/voltage.jpg"));
        environment -> getMaterial(5).setTexture(1, normalMap[5]);


        // Light
        //irr::scene::ILightSceneNode* light1 = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(0, 10, 0), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 8000.0f);
        //light1 -> setLightType(irr::video::ELT_DIRECTIONAL);
/*

        irr::scene::ILightSceneNode* light = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-1300, 200, -65200), irr::video::SColorf(1.0f, 0.0f, 1.0f, 1.0f), 8000.0f);
        light -> setLightType(irr::video::ELT_SPOT);
        light -> setRotation(irr::core::vector3df(90, -90, 0));*/


        irr::scene::ILightSceneNode* light;
        light = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-100, 100, 1000), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 18000.0f);
        light -> setLightType(irr::video::ELT_DIRECTIONAL);

        irr::scene::ILightSceneNode* light1 = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-300, 1900, -65200), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 8000.0f);
        light1 -> setLightType(irr::video::ELT_SPOT);
        light1 -> setRotation(irr::core::vector3df(10, 180, 90));
        //pb.player -> addChild(light);

    }

    else if(level == 13)
    {
        // Level 13
        // Dashcon '14


        irr::scene::IMeshSceneNode* convention = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl13/convention.obj"));

        convention -> setScale(irr::core::vector3df(100, 100, 100));
        convention -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        pb.scnmgr -> getMeshManipulator() -> makePlanarTextureMapping(convention -> getMesh(), 0.1f);
        convention -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/baptpool.jpg"));
        convention -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/dropped-ceiling.jpg"));
        convention -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/metal.jpg"));

        irr::scene::IMeshSceneNode* ballpit = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl13/ballpit.obj"));

        ballpit -> getMaterial(4).setTexture(0, pb.driver -> getTexture("img/object_textures/chair.jpg"));
        ballpit -> setScale(irr::core::vector3df(100, 100, 100));
        ballpit -> setMaterialFlag(irr::video::EMF_LIGHTING, false);


    }

    else if(level == 14)
    {
        // Level 14
        // Poolroom

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();
        pb.player -> setPosition(irr::core::vector3df(-273, 80, -266));
        pb.player -> setRotation(irr::core::vector3df(0, -75, 0));
        pb.verticalCamRot = 30;



        // Main mesh
        irr::scene::IMeshSceneNode* poolroom = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl14/poolroom.obj"));
        poolroom -> setScale(irr::core::vector3df(40, 40, 40));

        poolroom -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/metal.jpg"));
        poolroom -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/blue-wall.jpg"));
        poolroom -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/blue-tiles.jpg"));
        pb.rootNode -> addChild(poolroom);

        // Water
        irr::scene::IAnimatedMesh* water = pb.scnmgr -> addHillPlaneMesh("water", irr::core::dimension2d<irr::f32>(6.7, 10), irr::core::dimension2d<irr::u32>(100, 100), 0, 0, irr::core::dimension2d<irr::f32>(0, 0), irr::core::dimension2d<irr::f32>(2, 2));
        waterSurface = pb.scnmgr -> addWaterSurfaceSceneNode(water -> getMesh(0), 1.0f, 500.0f, 60.0f);

        waterSurface -> setPosition(irr::core::vector3df(0, 280, 0));

        // Materials 'n' textures
        waterSurface -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/water.jpg"));
        waterSurface -> setMaterialTexture(1, pb.driver -> getTexture("img/object_textures/water.jpg"));
        waterSurface -> setMaterialType(irr::video::EMT_TRANSPARENT_REFLECTION_2_LAYER);
        //pb.rootNode -> addChild(water);
        pb.rootNode -> addChild(waterSurface);






        // Light
        irr::scene::ILightSceneNode* light = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(2, -300, 431), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 80000.0f);
        light -> setRotation(irr::core::vector3df(270, 90, 0));
        light -> setLightType(irr::video::ELT_SPOT);
        pb.rootNode -> addChild(light);




        // Triangle selector
        irr::scene::ITriangleSelector* ts = pb.scnmgr -> createOctreeTriangleSelector(poolroom -> getMesh(), poolroom, 64);
        poolroom -> setTriangleSelector(ts);
        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
        pb.player -> addAnimator(anim);

        ts -> drop();
        anim -> drop();

    }

    else if(level == 15)
    {
        // Level 15
        // Pink

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(-105, 154, -29));
        pb.player -> setRotation(irr::core::vector3df(0, 80, 0));
        pb.verticalCamRot = 30;



        irr::scene::IMeshSceneNode* backrooms = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl15/pinkpool.obj"));


        backrooms -> setScale(irr::core::vector3df(60, 60, 60));
        backrooms -> setPosition(irr::core::vector3df(0, 0, 0));
        backrooms -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        backrooms -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/metal.jpg"));
        backrooms -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/blue-tiles.jpg"));
        backrooms -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/parking.jpg"));



/*

        // Collision //
        irr::scene::ITriangleSelector* ts = pb.scnmgr -> createTriangleSelector(backrooms -> getMesh(), backrooms);
        backrooms -> setTriangleSelector(ts);
        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
        pb.player -> addAnimator(anim);

        ts -> drop();
        anim -> drop();*/
    }


    else if(level == 16)
    {
        // Level 16
        // Laundry Room @ 3 A.M.

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(-105, 154, -29));
        pb.player -> setRotation(irr::core::vector3df(0, 80, 0));
        pb.verticalCamRot = 30;



        // Night skybox
        irr::scene::ISceneNode* skybox = pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"), pb.driver -> getTexture("img/sky/night.jpg"));


        irr::scene::IMeshSceneNode* building = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl16/laundry.obj"));
        irr::scene::IMeshSceneNode* window = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl16/laundry-window.obj"));
        irr::scene::IMeshSceneNode* washingMachine[8];
        irr::scene::IMeshSceneNode* chair[2];

        building -> setScale(irr::core::vector3df(30, 30, 30));
        building -> setPosition(irr::core::vector3df(0, 35, 0));
        building -> setMaterialFlag(irr::video::EMF_LIGHTING, true);
        building -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/laundry.png"));

        window -> setScale(irr::core::vector3df(30, 30, 30));
        window -> setPosition(irr::core::vector3df(0, 35, 0));
        window -> setMaterialFlag(irr::video::EMF_LIGHTING, true);
        window -> setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        window -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/laundry-window.png"));

        for(int i = 0; i < 2; i++)
        {
            chair[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/modern-chair1.obj"));
            //chair[i] -> addShadowVolumeSceneNode(); // temporarily commented out due to extreme lag on slow hardware
            chair[i] -> setScale(irr::core::vector3df(35, 35, 35));
            chair[i] -> setPosition(irr::core::vector3df(160, 30, -80 - (i * 130)));
            chair[i] -> setRotation(irr::core::vector3df(0, 90, 0));
            chair[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, true);
            chair[i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/white-wall.jpg"));
            chair[i] -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/metal.jpg"));
        }


        for(int i = 0; i < 8; i++)
        {
            washingMachine[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/washing-machine.obj"));
            washingMachine[i] -> setScale(irr::core::vector3df(30, 30, 30));
            washingMachine[i] -> setPosition(irr::core::vector3df(0, 100, 0 - (60 * i)));
            washingMachine[i] -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/washing-machine.png"));
            washingMachine[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, true);

        }

        // Lights
        irr::scene::ILightSceneNode* light[1];
        light[0] = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-56, 200, -100), irr::video::SColorf(1.0f, 0.5f, 1.0f, 1.0f), 8000.0f);
        light[0] -> setLightType(irr::video::ELT_POINT);
        light[1] = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-300, 200, -726), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 10000.0f);
        light[1] -> setLightType(irr::video::ELT_SPOT);
        light[1] -> setRotation(irr::core::vector3df(0, 180, 45));


        // Collision
        irr::scene::ITriangleSelector* ts = pb.scnmgr -> createTriangleSelector(pb.scnmgr -> getMesh("3d/lvl16/laundry-collision.obj"), building);
        building -> setTriangleSelector(ts);
        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
        pb.player -> addAnimator(anim);

        ts -> drop();
        anim -> drop();
    }

    else if(level == 18)
    {
        // Level 18
        // The Backrooms

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(-105, 154, -29));
        pb.player -> setRotation(irr::core::vector3df(0, 80, 0));
        pb.verticalCamRot = 30;



        irr::scene::IMeshSceneNode* backrooms = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl18/backrooms.obj"));

        pb.scnmgr -> getMeshManipulator() -> makePlanarTextureMapping(backrooms -> getMesh(), 0.5f);

        backrooms -> setScale(irr::core::vector3df(60, 60, 60));
        backrooms -> setPosition(irr::core::vector3df(0, 100, 0));
        backrooms -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        //backrooms -> getMaterial(2).EmissiveColor.set(100, 255, 255, 200);
        //backrooms -> getMaterial(0).SpecularColor.set(100, 255, 255, 200);
        backrooms -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/dropped-ceiling.jpg"));
        backrooms -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/chair.jpg"));
        backrooms -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/backrooms-wall.png"));





        // Collision //
        irr::scene::ITriangleSelector* ts = pb.scnmgr -> createTriangleSelector(backrooms -> getMesh(), backrooms);
        backrooms -> setTriangleSelector(ts);
        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
        pb.player -> addAnimator(anim);

        ts -> drop();
        anim -> drop();
    }

    else if(level == 19)
    {
        // Level 19
        // The Boardwalk

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(1000, 200, 1500));
        pb.player -> setRotation(irr::core::vector3df(0, 80, 0));
        pb.verticalCamRot = 30;



        // Forest skybox //
        irr::scene::ISceneNode* skybox = pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/woods/woods_top.jpg"), pb.driver -> getTexture("img/sky/woods/woods-3.jpg"), pb.driver -> getTexture("img/sky/woods/woods-1.jpg"), pb.driver -> getTexture("img/sky/woods/woods-3.jpg"), pb.driver -> getTexture("img/sky/woods/woods-2.jpg"), pb.driver -> getTexture("img/sky/woods/woods-0.jpg"));

        // Light //
        irr::scene::ILightSceneNode* light;
        light = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-100, 100, 1000), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 18000.0f);
        light -> setLightType(irr::video::ELT_DIRECTIONAL);


        // Board Walk //
        irr::scene::IMeshSceneNode* boardwalk = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl19/boardwalk.obj"));

        // Scale, position, and materials
        boardwalk -> setScale(irr::core::vector3df(400, 400, 400));
        boardwalk -> setPosition(irr::core::vector3df(0, 0, 0));
        boardwalk -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        boardwalk -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/grass.jpg"));
        boardwalk -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/wood.jpg"));
        boardwalk -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/wood.jpg"));

        // Trees //
        irr::scene::IMesh* tangTree = pb.scnmgr -> getMeshManipulator() -> createMeshWithTangents(pb.scnmgr -> getMesh("3d/universal/tree.obj"));

        irr::scene::IMeshSceneNode* trees[8] = {0};

        // Create bump map texture
        irr::video::ITexture* normalMap = pb.driver -> getTexture("img/bump/barkn.jpg");
        pb.driver -> makeNormalMapTexture(normalMap, 9.0f);

        for(int i = 0; i < 8; i++)
        {
            trees[i] = pb.scnmgr -> addMeshSceneNode(tangTree);

            // Shadow scene node
            if(pb.enableShadows)
            {
                trees[i] -> addShadowVolumeSceneNode();
            }


            // Scale, position, and materials
            trees[i] -> setScale(irr::core::vector3df(100, 100, 100));
            trees[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, true);
            trees[i] -> setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
            trees[i] -> setMaterialType(irr::video::EMT_PARALLAX_MAP_SOLID);


            // Color
            trees[i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/leaves.png"));
            trees[i] -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/bark.jpg"));

            // Bump
            trees[i] -> getMaterial(1).MaterialTypeParam = 1.0f / 64.0f;

            if(pb.enableBump)
            {
                trees[i] -> getMaterial(1).setTexture(1, normalMap);
            }
        }

        trees[0] -> setPosition(irr::core::vector3df(50, 0, 0));
        trees[1] -> setPosition(irr::core::vector3df(-1900, 0, 420));
        trees[2] -> setPosition(irr::core::vector3df(-1400, 0, -300));
        trees[3] -> setPosition(irr::core::vector3df(-2200, 0, -1100));
        trees[4] -> setPosition(irr::core::vector3df(270, 0, 2400));
        trees[5] -> setPosition(irr::core::vector3df(1800, 0, 650));
        trees[6] -> setPosition(irr::core::vector3df(2000, 0, 500));
        trees[7] -> setPosition(irr::core::vector3df(800, 0, 160));

        // Water //
        irr::scene::IAnimatedMesh* water = pb.scnmgr -> addHillPlaneMesh("water", irr::core::dimension2d<irr::f32>(100, 100), irr::core::dimension2d<irr::u32>(100, 100), 0, 0, irr::core::dimension2d<irr::f32>(0, 0), irr::core::dimension2d<irr::f32>(5, 5));
        waterSurface = pb.scnmgr -> addWaterSurfaceSceneNode(water -> getMesh(0), 5.0f, 1000.0f, 5.0f);
        waterSurface -> setPosition(irr::core::vector3df(0, 10, 0));
        waterSurface -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/water.jpg"));
        waterSurface -> setMaterialTexture(1, pb.driver -> getTexture("img/sky/woods/woods_top.jpg"));
        waterSurface -> setMaterialType(irr::video::EMT_REFLECTION_2_LAYER);
        waterSurface -> setMaterialFlag(irr::video::EMF_LIGHTING, false);




        // Collision //
        irr::scene::ITriangleSelector* ts = pb.scnmgr -> createTriangleSelector(pb.scnmgr -> getMesh("3d/lvl19/boardwalk-collision.obj"), boardwalk);
        boardwalk -> setTriangleSelector(ts);
        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(20, 30, 20), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
        pb.player -> addAnimator(anim);

        tangTree -> drop();
        ts -> drop();
        anim -> drop();
    }

    else if(level == 20)
    {
        // Level 20
        // Ukraine

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();


        pb.player -> setPosition(irr::core::vector3df(2920, 0, 2780));
        pb.player -> setRotation(irr::core::vector3df(0, 90, 0));


        // City skybox //
        irr::scene::ISceneNode* skybox = pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/city1-5.jpg"), pb.driver -> getTexture("img/sky/city1-4.jpg"), pb.driver -> getTexture("img/sky/city1-1.jpg"), pb.driver -> getTexture("img/sky/city1-3.jpg"), pb.driver -> getTexture("img/sky/city1-0.jpg"), pb.driver -> getTexture("img/sky/city1-2.jpg"));


        // City //
        irr::scene::IMeshSceneNode* city = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl20/ukraine.obj"));
        city -> setScale(irr::core::vector3df(130, 130, 130));
        city -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        city -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/building.jpg"));
        city -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/building1.jpg"));
        city -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/building2.jpg"));
        city -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/building3.jpg"));
        city -> getMaterial(4).setTexture(0, pb.driver -> getTexture("img/object_textures/building4.jpg"));
        city -> getMaterial(5).setTexture(0, pb.driver -> getTexture("img/bump/asphaltn.jpg"));
        //city -> getMaterial(6).setTexture(0, pb.driver -> getTexture("img/object_textures/"));


        // Collision
        irr::scene::ITriangleSelector* ts = pb.scnmgr -> createTriangleSelector(city -> getMesh(), city);
        city -> setTriangleSelector(ts);

        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 20, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
        pb.player -> addAnimator(anim);
        ts -> drop();
        anim -> drop();
    }

    else if(level == 21)
    {
        // Level 21
        // Suburbs
        pb.player -> setPosition(irr::core::vector3df(0, 0, 0));
        pb.player -> setRotation(irr::core::vector3df(0, 50, 0));


        // Foggy skybox
        irr::scene::ISceneNode* skybox = pb.scnmgr -> addSkyBoxSceneNode(pb.driver -> getTexture("img/sky/city1-5.jpg"), pb.driver -> getTexture("img/sky/city1-5.jpg"), pb.driver -> getTexture("img/sky/city1-5.jpg"), pb.driver -> getTexture("img/sky/city1-5.jpg"), pb.driver -> getTexture("img/sky/city1-5.jpg"), pb.driver -> getTexture("img/sky/city1-5.jpg"));


        irr::scene::IMeshSceneNode* road = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl21/road.obj"), 0, -1, irr::core::vector3df(8000, 0, 3000), irr::core::vector3df(0, 0, 0), irr::core::vector3df(100, 10, 150));
        road -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/grass.jpg"));
        road -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/bump/asphaltn.jpg"));

        road -> setMaterialFlag(irr::video::EMF_LIGHTING, false);

        irr::scene::IMeshSceneNode* house[10];

        for(int i = 0; i < 10; i++)
        {
            house[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/house.obj"), 0, -1, irr::core::vector3df(i * i * 500, 0, 1000 * i), irr::core::vector3df(0, 40 + i * 20, 0), irr::core::vector3df(100, 100, 100));
            house[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
            house[i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/door.jpg"));
            house[i] -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/roof.jpg"));
            house[i] -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/blue-wall.jpg"));
            house[i] -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/door1.jpg"));
        }
    }

    else if(level == 22)
    {
        // Level 22
        // Waiting Room
        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(0, 115, 0));
        pb.player -> setRotation(irr::core::vector3df(0, 63, 0));
        pb.verticalCamRot = 30;



        // The chairs
        irr::scene::IMeshSceneNode* chair[4] = {0};

        for(int i = 0; i < 3; i++)
        {
            chair[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/chair.obj"));
            chair[i] -> setScale(irr::core::vector3df(50, 50, 50));
            chair[i] -> setPosition(irr::core::vector3df(100 - i * 110, 35, 260));
            chair[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
            chair[i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/chair.jpg"));
            pb.rootNode -> addChild(chair[i]);

        }


        chair[3] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/chair.obj"));
        chair[3] -> setScale(irr::core::vector3df(50, 50, 50));
        chair[3] -> setPosition(irr::core::vector3df(-280, 35, -95));
        chair[3] -> setRotation(irr::core::vector3df(0, 280, 0));
        chair[3] -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        chair[3] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/chair.jpg"));
        pb.rootNode -> addChild(chair[3]);


        // The waiting room
        irr::scene::IMeshSceneNode* waitingRoom = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl22/waiting-room.obj"));
        waitingRoom -> setScale(irr::core::vector3df(50, 50, 50));
        waitingRoom -> setPosition(irr::core::vector3df(0, 35, 0));
        waitingRoom -> setMaterialFlag(irr::video::EMF_LIGHTING, true);
        waitingRoom -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/tv.jpg"));
        waitingRoom -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/waiting-room.jpg"));
        waitingRoom -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/door.jpg"));
        waitingRoom -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/dropped-ceiling.jpg"));
        pb.rootNode -> addChild(waitingRoom);


        // Light
        irr::scene::ILightSceneNode* light[3];
        light[0] = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(164, 200, -20), irr::video::SColorf(0.7f, 0.7f, 0.7f, 1.0f), 80000.0f);
        light[0] -> setRotation(irr::core::vector3df(-10, 170, 0));
        light[0] -> setLightType(irr::video::ELT_SPOT);

        light[1] = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(134, 200, -222), irr::video::SColorf(0.1f, 0.15f, 0.15f, 1.0f), 80000.0f);
        light[1] -> setRotation(irr::core::vector3df(0, 360, 0));
        light[1] -> setLightType(irr::video::ELT_SPOT);

        light[2] = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(134, 200, -222), irr::video::SColorf(0.1f, 0.15f, 0.15f, 1.0f), 80000.0f);
        light[2] -> setRotation(irr::core::vector3df(0, 280, 0));
        light[2] -> setLightType(irr::video::ELT_SPOT);

        for(int i = 0; i < 3; i++)
        {
            pb.rootNode -> addChild(light[i]);
        }

        // Create the meta triangle selector which holds all of the other triangle selectors.
        irr::scene::IMetaTriangleSelector* ts = pb.scnmgr -> createMetaTriangleSelector();

        irr::scene::ITriangleSelector* tsWaitingRoom = pb.scnmgr -> createOctreeTriangleSelector(waitingRoom -> getMesh(), waitingRoom, 512);
        ts -> addTriangleSelector(tsWaitingRoom);
        waitingRoom -> setTriangleSelector(tsWaitingRoom);

        irr::scene::ITriangleSelector* tsChair[4];

        for(int i = 0; i < 4; i++)
        {
            chair[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, true);
            tsChair[i] = pb.scnmgr -> createOctreeTriangleSelector(chair[i] -> getMesh(), chair[i], 256);
            ts -> addTriangleSelector(tsChair[i]);
            chair[i] -> setTriangleSelector(tsChair[i]);
        }

        // Create a collision response animator and add it to the pb.player.
        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));

        for(int i = 0; i < 4; i++)
        {
            tsChair[i] -> drop();
        }
        tsWaitingRoom -> drop();
        ts -> drop();
        pb.player -> addAnimator(anim);
        anim -> drop();
    }

    else if(level == 23)
    {
        // Level 23
        // "Children's Game Park", a.k.a. Playground
        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(100, 100, 100));
        pb.player -> setRotation(irr::core::vector3df(0, 85, 0));

        irr::scene::IMeshSceneNode* slide[4] = {0};



        // Floor
        irr::scene::IMeshSceneNode* floor;
        floor = pb.scnmgr -> addCubeSceneNode(irr::f32(1.0f), 0, -1, irr::core::vector3df(0, -100, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0x2p20, 0, 0x2p20));
        floor -> setMaterialFlag(irr::video::EMF_LIGHTING, false);

        pb.scnmgr -> getMeshManipulator() -> makePlanarTextureMapping(floor -> getMesh(), 1200.0f);
        floor -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/grass.jpg"));

        pb.rootNode -> addChild(floor);

        // Slides
        for(int i = 0; i < 4; i++)
        {
            slide[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl23/slide.obj"));
            slide[i] -> setScale(irr::core::vector3df(100, 100, 100));
            slide[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
            slide[i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/garage-door.jpg"));
            slide[i] -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/metal.jpg"));
            slide[i] -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/garage-door.jpg"));
            pb.rootNode -> addChild(slide[i]);
        }

        slide[0] -> setPosition(irr::core::vector3df(100, 100, 100));
        slide[1] -> setPosition(irr::core::vector3df(1000, 100, 1000));
        slide[2] -> setPosition(irr::core::vector3df(800, 100, -1000));
        slide[3] -> setPosition(irr::core::vector3df(-500, 100, 1000));
    }

    else if(level == 24)
    {
        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(1000, 200, 1500));
        pb.player -> setRotation(irr::core::vector3df(0, 80, 0));
        pb.verticalCamRot = 30;



        // Foggy skybox //
        skyboxManager.setSkybox(skyboxManager.FOG);

        // Light //
        irr::scene::ILightSceneNode* light;
        light = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-100, 100, 1000), irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 18000.0f);
        light -> setLightType(irr::video::ELT_DIRECTIONAL);

        // Floor //
        irr::scene::IMeshSceneNode* floor;
        floor = pb.scnmgr -> addCubeSceneNode(irr::f32(1.0f), 0, -1, irr::core::vector3df(0, -400, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0x2p20, 0, 0x2p20));
        floor -> setMaterialFlag(irr::video::EMF_LIGHTING, false);

        pb.scnmgr -> getMeshManipulator() -> makePlanarTextureMapping(floor -> getMesh(), 1200.0f);
        floor -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/dirt.jpg"));

        pb.rootNode -> addChild(floor);

        // Rude Sign //
        irr::scene::IMeshSceneNode* rudeSign = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl24/shitday.obj"));

        // Scale, position, and materials
        rudeSign -> setScale(irr::core::vector3df(100, 100, 100));
        rudeSign -> setPosition(irr::core::vector3df(0, 0, 0));
        rudeSign -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        rudeSign -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/shitday.jpg"));
    }

    else if(level == 25)
    {
        // Level 25
        // 8800 Blue Lick Road
        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        pb.player -> setPosition(irr::core::vector3df(-180, 0, -668));
        pb.player -> setRotation(irr::core::vector3df(0, -70, 0));
        pb.verticalCamRot = 30;




        // The shelves
        irr::scene::IMeshSceneNode* shelf[4] = {0};


        for(int i = 0; i < 4; i++)
        {
            shelf[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/shelf.obj"));
            shelf[i] -> setScale(irr::core::vector3df(100, 100, 100));
            shelf[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, true);
            shelf[i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/wood.jpg"));
            shelf[i] -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/metal.jpg"));
            pb.rootNode -> addChild(shelf[i]);
        }

        // Shelf 0
        shelf[0] -> setPosition(irr::core::vector3df(-40, 40, 0));

        // Shelf 1
        shelf[1] -> setPosition(irr::core::vector3df(390, 40, -700));
        shelf[1] -> setRotation(irr::core::vector3df(0, 98, 0));

        // Shelf 2
        shelf[2] -> setPosition(irr::core::vector3df(100, 40, -250));

        // Shelf 3
        shelf[3] -> setPosition(irr::core::vector3df(180, 40, -650));
        shelf[3] -> setScale(irr::core::vector3df(70, 100, 100));
        shelf[3] -> setRotation(irr::core::vector3df(0, 97, 0));


        // Boxes
        irr::scene::IMeshSceneNode* smallBox[7] = {0};
        irr::scene::IMeshSceneNode* largeBox[5] = {0};

        // Seed for pseudo-random number generator so that the textures are always the same.
        srand(300);

        // Small box
        for(int i = 0; i < 7; i++)
        {
            smallBox[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl25/box1.obj"));
            smallBox[i] -> setScale(irr::core::vector3df(100, 100, 100));
            smallBox[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, true);

            std::string filename("img/object_textures/box-label");
            filename = filename + std::to_string(rand() % 2) + ".jpg";

            smallBox[i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/box.jpg"));
            smallBox[i] -> getMaterial(1).setTexture(0, pb.driver -> getTexture(filename.c_str()));
            pb.rootNode -> addChild(smallBox[i]);
        }

        // Large box
        for(int i = 0; i < 5; i++)
        {
            largeBox[i] = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl25/box.obj"));
            largeBox[i] -> setScale(irr::core::vector3df(100, 100, 100));
            largeBox[i] -> setMaterialFlag(irr::video::EMF_LIGHTING, true);

            std::string filename("img/object_textures/box-label");
            filename = filename + std::to_string(rand() % 3) + ".jpg";


            largeBox[i] -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/box.jpg"));
            largeBox[i] -> getMaterial(1).setTexture(0, pb.driver -> getTexture(filename.c_str()));

            pb.rootNode -> addChild(largeBox[i]);
        }

        // Boxes on shelf #0 //
        largeBox[0] -> setPosition(irr::core::vector3df(-40, 78, 0));

        largeBox[1] -> setPosition(irr::core::vector3df(-180, 119, 20));
        largeBox[1] -> setRotation(irr::core::vector3df(0, -20, 0));

        smallBox[0] -> setPosition(irr::core::vector3df(-30, 162, 0));

        // Boxes on shelf #1 //
        largeBox[2] -> setPosition(irr::core::vector3df(390, 78, -700));
        largeBox[2] -> setRotation(irr::core::vector3df(0, 98, 0));

        smallBox[1] -> setPosition(irr::core::vector3df(390, 119, -700));
        smallBox[1] -> setRotation(irr::core::vector3df(0, 98, 0));

        smallBox[2] -> setPosition(irr::core::vector3df(390, 162, -700));
        smallBox[2] -> setRotation(irr::core::vector3df(0, 98, 0));

        // Boxes on shelf #2 //
        smallBox[3] -> setPosition(irr::core::vector3df(-205, 78, -1050));
        smallBox[3] -> setRotation(irr::core::vector3df(0, 180, 0));

        smallBox[4] -> setPosition(irr::core::vector3df(-180, 119, -1050));
        smallBox[4] -> setRotation(irr::core::vector3df(0, 175, 0));

        largeBox[3] -> setPosition(irr::core::vector3df(-190, 162, -1050));
        largeBox[3] -> setRotation(irr::core::vector3df(0, 180, 0));

        // Boxes on shelf #3
        largeBox[4] -> setPosition(irr::core::vector3df(-595, 78, -330));
        largeBox[4] -> setRotation(irr::core::vector3df(0, 276, 0));

        smallBox[5] -> setPosition(irr::core::vector3df(-590, 119, -330));
        smallBox[5] -> setRotation(irr::core::vector3df(0, 272, 0));

        smallBox[6] -> setPosition(irr::core::vector3df(-590, 162, -330));
        smallBox[6] -> setRotation(irr::core::vector3df(0, 274, 0));


        // 8800 Blue Lick Road House
        irr::scene::IMeshSceneNode* bluelick = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/lvl25/bluelick.obj"));
        bluelick -> setScale(irr::core::vector3df(100, 100, 100));
        bluelick -> setPosition(irr::core::vector3df(0, 35, 0));
        bluelick -> setMaterialFlag(irr::video::EMF_LIGHTING, true);
        bluelick -> getMaterial(0).setTexture(0, pb.driver -> getTexture("img/object_textures/white-wall.jpg"));
        bluelick -> getMaterial(1).setTexture(0, pb.driver -> getTexture("img/object_textures/door.jpg"));
        bluelick -> getMaterial(2).setTexture(0, pb.driver -> getTexture("img/object_textures/baptpool.jpg"));
        bluelick -> getMaterial(3).setTexture(0, pb.driver -> getTexture("img/object_textures/wood.jpg"));
        bluelick -> getMaterial(4).setTexture(0, pb.driver -> getTexture("img/object_textures/chair.jpg"));
        bluelick -> getMaterial(5).EmissiveColor.set(255, 255, 255, 255);
        bluelick -> getMaterial(6).setTexture(0, pb.driver -> getTexture("img/object_textures/metal.jpg"));
        pb.rootNode -> addChild(bluelick);


        // Light
        irr::scene::ILightSceneNode* light;
        light = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(0, 100, 0), irr::video::SColorf(0.7f, 0.7f, 0.7f, 1.0f), 50000.0f);
        light -> setLightType(irr::video::ELT_POINT);

        irr::scene::ILightSceneNode* light1;
        light1 = pb.scnmgr -> addLightSceneNode(0, irr::core::vector3df(-100, 100, -600), irr::video::SColorf(0.7f, 0.7f, 0.7f, 1.0f), 30000.0f);
        light1 -> setLightType(irr::video::ELT_POINT);


        // Create the meta triangle selector which holds all of the other triangle selectors.
        irr::scene::IMetaTriangleSelector* ts = pb.scnmgr -> createMetaTriangleSelector();

        irr::scene::ITriangleSelector* tsWalls = pb.scnmgr -> createOctreeTriangleSelector(bluelick -> getMesh(), bluelick, 512);
        ts -> addTriangleSelector(tsWalls);
        //ts -> addTriangleSelector(tsShelf);
        bluelick -> setTriangleSelector(tsWalls);

        // Create a collision response animator and add it to the player.
        anim = pb.scnmgr -> createCollisionResponseAnimator(ts, pb.player, irr::core::vector3df(30, 100, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));

        tsWalls -> drop();
        ts -> drop();
        pb.player -> addAnimator(anim);
        anim -> drop();
    }
    // WIP Level
    else if(level != 1)
    {
        pb.player -> setPosition(irr::core::vector3df(20, 200, 20));
        pb.player -> setRotation(irr::core::vector3df(0, 0, 0));

        pb.rootNode = pb.scnmgr -> addEmptySceneNode();

        irr::scene::IMeshSceneNode* board;
        board = pb.scnmgr -> addMeshSceneNode(pb.scnmgr -> getMesh("3d/universal/board.obj"));
        board -> setScale(irr::core::vector3df(130, 130, 130));
        board -> setPosition(irr::core::vector3df(500, 260, 0));
        board -> setRotation(irr::core::vector3df(0, 270, 0));
        board -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        board -> setMaterialTexture(0, pb.driver -> getTexture("img/object_textures/wip.jpg"));
        pb.rootNode -> addChild(board);
    }

    return level;
}

/*
1: Sky & Clouds
2: Night Parking Lot
3: City
4: Vinyl Flooring
5: Room
6: Backyard
7: Ingul
8: Randomness
9: Winter Neighborhood @ Night
10: Star
11: Office
12: Night
13: Dashcon 2014
14: Poolroom
15: Pink
16: Laundry Room at 3am
17: Holidays
18: Backrooms
19: Boardwalk
20: Ukraine
21: Suburb
22: Waiting Room
23: Playground
24: Rainy Day
25: 8800 Blue Lick Road
*/
