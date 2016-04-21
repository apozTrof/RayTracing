//
//  Cube.h
//  RayTracer
//

#ifndef __RayTracer__Cube__
#define __RayTracer__Cube__

#include <iostream>

#include "GeometricObject.h"

class Cube : public GeometricObject {
    
public:
    
    Cube(const std::shared_ptr<GeometricTransform> a_pO2W,
         const std::shared_ptr<GeometricTransform> a_pW2O,
         double a_side);

	bool planeCubeX(const Ray& a_ray, double& a_t) const;
	bool planeCubeY(const Ray& a_ray, double& a_t) const;
	bool planeCubeZ(const Ray& a_ray, double& a_t) const;
    BoundingBox objectBound() const;
    
    bool intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const;
    double area() const;
    
private:
    
    double m_side;
	double half_side;
};

#endif /* defined(__RayTracer__Cube__) */
