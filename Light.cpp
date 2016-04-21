//
//  Light.cpp
//  RayTracer
//

#include "Light.h"

Light::Light()
{}

Light::~Light()
{}

RGBColor Light::getRadiance(const Intersection& a_inter) const
{
    return RGBColor(0.0);
}

Point Light::getPosition()
{
    std::cerr << "Unimplemented Light::getPosition() method called" << std::endl;
    
    return Point();
}

