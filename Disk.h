//
//  Disk.h
//  RayTracer
//

#ifndef __RayTracer__Disk__
#define __RayTracer__Disk__

#include <iostream>

#include "GeometricObject.h"

class Disk : public GeometricObject {
    
public:
    
    Disk(const std::shared_ptr<GeometricTransform> a_pO2W,
         const std::shared_ptr<GeometricTransform> a_pW2O,
         double a_height, double a_innerRad, double a_outerRad);
    
    BoundingBox objectBound() const;
    
    bool intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const;
    double area() const;
    
private:
    
    double m_height;
    double m_iRad;
    double m_oRad;
};

#endif /* defined(__RayTracer__Disk__) */
