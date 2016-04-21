//
//  Cone.h
//  RayTracer
//

#ifndef __RayTracer__Cone__
#define __RayTracer__Cone__

#include <iostream>

#include "GeometricObject.h"

class Cone : public GeometricObject {
    
public:
    
    Cone(const std::shared_ptr<GeometricTransform> a_pO2W,
         const std::shared_ptr<GeometricTransform> a_pW2O,
         double a_height, double a_rad);
    
    BoundingBox objectBound() const;
    
    bool intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const;
    double area() const;
   
	bool HitBottom(Ray objRay, double& t) const;
	bool HitSide(Ray objRay, double& t) const;

private:
    
    double m_rad;
    double m_height;
};

#endif /* defined(__RayTracer__Cone__) */
