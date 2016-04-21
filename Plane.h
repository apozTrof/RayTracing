//
//  Plane.h
//  RayTracer
//

#ifndef __RayTracer__Plane__
#define __RayTracer__Plane__

#include <iostream>

#include "GeometricObject.h"
#include "BoundingBox.h"

class Plane : public GeometricObject {
    
public:
    
    Plane(const std::shared_ptr<GeometricTransform> a_pO2W,
          const std::shared_ptr<GeometricTransform> a_pW2O,
          double a_xMin, double a_xMax,
          double a_zMin, double a_zMax);
    
    BoundingBox objectBound() const;
    
    bool intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const;
    double area() const;
    
    Point sample() const;
    double pdf() const;
    Normal getNormal(const Point& a_p) const;
    
private:
    
    double m_xMin;
    double m_xMax;
    double m_zMin;
    double m_zMax;
};

#endif /* defined(__RayTracer__Plane__) */
