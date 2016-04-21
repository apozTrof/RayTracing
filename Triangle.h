//
//  Triangle.h
//  RayTracer
//

#ifndef __RayTracer__Triangle__
#define __RayTracer__Triangle__

#include <iostream>

#include "GeometricObject.h"
#include "Point.h"

class Triangle : public GeometricObject {
    
public:
    
    Triangle(const std::shared_ptr<GeometricTransform> a_pO2W,
             const std::shared_ptr<GeometricTransform> a_pW2O,
             const Point& a_p1, const Point& a_p2, const Point& a_p3);
    
    BoundingBox objectBound() const;
    BoundingBox worldBound() const;
    
    bool intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const;
    double area() const;
    
private:
    
    Point m_p1;
    Point m_p2;
    Point m_p3;
    Normal m_n;
};

#endif /* defined(__RayTracer__Triangle__) */
