//
//  Texture.h
//  RayTracer
//

#ifndef __RayTracer__Texture__
#define __RayTracer__Texture__

#include <iostream>

#include "RGBColor.h"
#include "Intersection.h"

class Texture {
    
public:
    
    Texture();
    Texture(const Texture& a_texture);
    
    ~Texture();
    
    virtual RGBColor getColor(const Intersection& a_inter) const = 0;
};

#endif /* defined(__RayTracer__Texture__) */
