//
//  Material.h
//  RayTracer
//

#ifndef __RayTracer__Material__
#define __RayTracer__Material__

#include <iostream>

#include "RGBColor.h"
#include "Intersection.h"

class Material : public std::enable_shared_from_this<Material> {
    
public:
    
    Material();
    Material(const Material& a_mat);
    
    virtual ~Material();
        
    virtual RGBColor shade(Intersection& a_inter) const = 0;
    
    virtual RGBColor getRadiance(const Intersection& a_inter) const;
    
};

inline RGBColor Material::getRadiance(const Intersection& a_inter) const
{
    return RGBColor(0.0);
}

#endif /* defined(__RayTracer__Material__) */
