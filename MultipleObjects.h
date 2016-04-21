//
//  MultipleObjects.h
//  RayTracer
//

#ifndef __RayTracer__MultipleObjects__
#define __RayTracer__MultipleObjects__

#include <iostream>

#include "Tracer.h"

class MultipleObjects : public Tracer {
    
public:
    
    MultipleObjects();
    MultipleObjects(std::shared_ptr<World> a_pWorld);
    
    ~MultipleObjects();
    
    RGBColor traceRay(const Ray& a_ray) const;
};

#endif /* defined(__RayTracer__MultipleObjects__) */
