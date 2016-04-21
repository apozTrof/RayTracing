//
//  Sphere.h
//  RayTracer
//

#ifndef __RayTracer__Sphere__
#define __RayTracer__Sphere__

#include <iostream>

#include "GeometricObject.h"
#include "BoundingBox.h"
#include "GeometricTransform.h"

class Sphere : public GeometricObject {
    
public:
    
    Sphere(const std::shared_ptr<GeometricTransform> a_pO2W,
           const std::shared_ptr<GeometricTransform> a_pW2O,
           double a_rad);
    
    BoundingBox objectBound() const;
        
    bool intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const;
    double area() const;
    
private:

    double m_rad;
    
    BoundingBox m_obb;
};

#endif /* defined(__RayTracer__Sphere__) */
