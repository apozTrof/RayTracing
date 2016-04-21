//
//  RayCast.h
//  RayTracer
//

#ifndef __RayTracer__RayCast__
#define __RayTracer__RayCast__

#include <iostream>

#include "Tracer.h"

class RayCast : public Tracer {
    
public:
    
    RayCast();
    RayCast(std::shared_ptr<World> a_pWorld);
    
    ~RayCast();
    
    RGBColor traceRay(const Ray& a_ray) const;
};

#endif /* defined(__RayTracer__RayCast__) */
