//
//  World.h
//  RayTracer
//

#ifndef __RayTracer__World__
#define __RayTracer__World__

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Material.h"
#include "ViewPlane.h"
#include "RGBColor.h"
#include "Tracer.h"
#include "GeometricObject.h"
#include "Light.h"
#include "Camera.h"
#include "Whitted.h"

class World : public std::enable_shared_from_this<World> {
    
public:
    
    World();
    
    ~World();
    
    void build();
    void addObject(const std::shared_ptr<GeometricObject> a_pObject);
    void addLight(const std::shared_ptr<Light> a_pLight);
    void setCamera(const std::shared_ptr<Camera> a_pCam);
    
    ViewPlane m_vp;
    RGBColor m_backgroundColor;
    std::vector <std::shared_ptr<GeometricObject>> m_objects;
    std::vector <std::shared_ptr<Light>> m_lights;
    std::shared_ptr<Tracer> m_pTracer;
    std::shared_ptr<Camera> m_pCamera;
};

inline void World::addObject(const std::shared_ptr<GeometricObject> a_pObject)
{
    m_objects.push_back(a_pObject);
}

inline void World::addLight(const std::shared_ptr<Light> a_pLight)
{
    m_lights.push_back(a_pLight);
}

inline void World::setCamera(const std::shared_ptr<Camera> a_pCam)
{
    m_pCamera = a_pCam;
}

#endif /* defined(__RayTracer__World__) */
