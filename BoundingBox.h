//
//  BoundingBox.h
//  RayTracer
//

#ifndef __RayTracer__BoundingBox__
#define __RayTracer__BoundingBox__

#include <iostream>

#include "Point.h"
#include "Ray.h"

class BoundingBox {
    
public:
    
    BoundingBox();
    BoundingBox(const Point& a_p);
    BoundingBox(const Point& a_p1, const Point& a_p2);
    
    bool overlaps(const BoundingBox& a_bb) const;
    bool contains(const Point& a_p) const;
    
    bool intersect(const Ray& a_r, double& a_t0, double& a_t1) const;
	bool boxPlaneX(const Ray& a_ray, double& a_t) const;
	bool boxPlaneY(const Ray& a_ray, double& a_t) const;
	bool boxPlaneZ(const Ray& a_ray, double& a_t) const;
    
    friend BoundingBox combine(const BoundingBox& a_bb, const Point& a_p);
    friend BoundingBox combine(const BoundingBox& a_bb1, const BoundingBox& a_bb2);
    
    Point m_pMin;
    Point m_pMax;
};

#endif /* defined(__RayTracer__BoundingBox__) */
