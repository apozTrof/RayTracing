//
//  Cylinder.h
//  RayTracer
//

#ifndef __RayTracer__Cylinder__
#define __RayTracer__Cylinder__

#include <iostream>

#include "GeometricObject.h"
#include "BoundingBox.h"
#include "GeometricTransform.h"

class Cylinder : public GeometricObject {
    
public:
    
    Cylinder(const std::shared_ptr<GeometricTransform> a_pO2W,
             const std::shared_ptr<GeometricTransform> a_pW2O,
             double a_rad, double a_yMin, double a_yMax);
    
    BoundingBox objectBound() const;
    
    bool intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const;
    double area() const;
    
private:
    
    double m_rad;
    double m_yMin;
    double m_yMax;
};

#endif /* defined(__RayTracer__Cylinder__) */
