//
//  Tracer.h
//  RayTracer
//

#ifndef __RayTracer__Tracer__
#define __RayTracer__Tracer__

#include <iostream>
#include <memory>

#include "RGBColor.h"
#include "Ray.h"

class World;

class Tracer {
    
public:
        
    Tracer();
    Tracer(const std::shared_ptr<World> a_pWorld);
    
    virtual ~Tracer();
    
    virtual RGBColor traceRay(const Ray& a_ray) const;
    
    virtual RGBColor traceRay(const Ray& a_ray, int a_depth) const;
    
protected:
        
    std::shared_ptr<World> m_pWorld;
};

#endif /* defined(__RayTracer__Tracer__) */
