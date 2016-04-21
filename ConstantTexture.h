//
//  ConstantTexture.h
//  RayTracer
//

#ifndef __RayTracer__ConstantTexture__
#define __RayTracer__ConstantTexture__

#include <iostream>

#include "Texture.h"

class ConstantTexture : public Texture {
    
public:
    
    ConstantTexture();
    ConstantTexture(const ConstantTexture& a_ct);
    
    ~ConstantTexture();
    
    void setColor(const RGBColor& a_color);
    RGBColor getColor(const Intersection& a_inter) const;
    
private:
    
    RGBColor m_color;
};

inline void ConstantTexture::setColor(const RGBColor& a_color)
{
    m_color = a_color;
}

inline RGBColor ConstantTexture::getColor(const Intersection& a_inter) const
{
    return m_color;
}

#endif /* defined(__RayTracer__ConstantTexture__) */
