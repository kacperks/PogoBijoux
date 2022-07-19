#include "Base.h"
#include <irrlicht/irrlicht.h>


class RayCastHandler
{
    public:
        bool isPlayerLookingAtAABB(irr::core::aabbox3d<irr::f32> aabb)
        {
            irr::core::line3d<irr::f32> ray;
            ray.start = pb.player -> getPosition();
            ray.end = ray.start + (pb.camera -> getTarget() - ray.start).normalize() * 1000.0F;
            return true;
        }
};
