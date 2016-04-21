//
//  Ray.h
//  RayTracer
//

#ifndef __RayTracer__Ray__
#define __RayTracer__Ray__

#include <iostream>

#include "Point.h"
#include "Vector.h"

class Ray {
    
public:
        
    Ray();
    Ray(const Point& a_origin, const Vector& a_direction);
    Ray(const Point& a_origin, const Vector& a_direction, int a_depth, double a_mint, double a_maxt);
    Ray(const Ray& a_ray);
    
    ~Ray();
    
    Ray& operator=(const Ray& a_ray);
    Point operator()(double a_t) const;
        
    Point m_o;
    Vector m_d;
    int m_depth;
    mutable double m_mint;
    mutable double m_maxt;
    
};

inline Point Ray::operator()(double a_t) const
{
    return m_o + m_d * a_t;
}

#endif /* defined(__RayTracer__Ray__) */
