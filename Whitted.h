//
//  Whitted.h
//  RayTracer
//

#ifndef __RayTracer__Whitted__
#define __RayTracer__Whitted__

#include <iostream>

#include "Tracer.h"

class Whitted : public Tracer {
    
public:
    
    Whitted();
    Whitted(std::shared_ptr<World> a_pWorld);
    
    ~Whitted();
    
    RGBColor traceRay(const Ray& a_ray) const;
    
    RGBColor traceRay(const Ray& a_ray, int a_depth) const;
};

#endif /* defined(__RayTracer__Whitted__) */
