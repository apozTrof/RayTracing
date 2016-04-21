//
//  Intersection.h
//  RayTracer
//

#ifndef __RayTracer__Intersection__
#define __RayTracer__Intersection__

#include <iostream>
#include <memory>

class World;
class GeometricObject;
class Material;

//#include "World.h"
#include "Point.h"
#include "Normal.h"
#include "RGBColor.h"
#include "Ray.h"

class Intersection {
    
public:
        
    Intersection(const std::shared_ptr<World> a_pWorld);
    Intersection(const Intersection& a_i);
    
    ~Intersection();
        
    std::shared_ptr<World> m_pWorld;
    bool m_hit;
    Point m_hitPoint;
    Normal m_normal;
    std::shared_ptr<const GeometricObject> m_object;
    RGBColor m_color;
    Ray m_ray;
    int m_depth;
    std::shared_ptr<Material> m_material;
    double m_u, m_v;
};

#endif /* defined(__RayTracer__Intersection__) */
