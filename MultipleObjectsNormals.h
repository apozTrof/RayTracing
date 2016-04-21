//
//  MultipleObjectsNormals.h
//  RayTracer
//

#ifndef __RayTracer__MultipleObjectsNormals__
#define __RayTracer__MultipleObjectsNormals__

#include <iostream>

#include "Tracer.h"

class MultipleObjectsNormals : public Tracer {
    
public:
    
    MultipleObjectsNormals();
    MultipleObjectsNormals(std::shared_ptr<World> a_pWorld);
    
    ~MultipleObjectsNormals();
    
    RGBColor traceRay(const Ray& a_ray) const;
};

#endif /* defined(__RayTracer__MultipleObjectsNormals__) */
