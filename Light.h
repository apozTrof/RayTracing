//
//  Light.h
//  RayTracer
//

#ifndef __RayTracer__Light__
#define __RayTracer__Light__

#include <iostream>

#include "Vector.h"
#include "Intersection.h"
#include "RGBColor.h"
#include "Point.h"

class Light {
    
public:
    
    Light();
    
    virtual ~Light();
        
    virtual Vector getDirection(const Intersection& a_inter) const = 0;
    virtual RGBColor getRadiance(const Intersection& a_inter) const;
    
    virtual double g(const Intersection& a_inter) const;
    virtual double pdf(const Intersection& a_inter) const;
    
    virtual Point getPosition();
};

inline double Light::g(const Intersection& a_inter) const
{
    return 1.0;
}

inline double Light::pdf(const Intersection& a_inter) const
{
    return 1.0;
}

#endif /* defined(__RayTracer__Light__) */
