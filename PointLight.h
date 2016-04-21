//
//  PointLight.h
//  RayTracer
//

#ifndef __RayTracer__PointLight__
#define __RayTracer__PointLight__

#include <iostream>

#include "Light.h"
#include "Point.h"

class PointLight : public Light {
    
public:
    
    PointLight();
    PointLight(double a_ls, const RGBColor& a_color, const Point& a_pos);
    
    ~PointLight();
    
    Vector getDirection(const Intersection& a_inter) const;
    RGBColor getRadiance(const Intersection& a_inter) const;
    
    Point getPosition();
    
private:
    
    double m_ls;
    RGBColor m_color;
    Point m_pos;
};

inline RGBColor PointLight::getRadiance(const Intersection& a_inter) const
{
    return m_ls * m_color;
}

inline Point PointLight::getPosition()
{
    return m_pos;
}

#endif /* defined(__RayTracer__PointLight__) */
