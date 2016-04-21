//
//  Checkerboard3D.h
//  RayTracer
//

#ifndef __RayTracer__Checkerboard3D__
#define __RayTracer__Checkerboard3D__

#include <iostream>

#include "Texture.h"

class Checkerboard3D : public Texture {
    
public:
    
    Checkerboard3D();
    Checkerboard3D(const Checkerboard3D& a_cb3);
    
    ~Checkerboard3D();
    
    void setColor1(const RGBColor& a_color);
    void setColor2(const RGBColor& a_color);
    void setSize(double a_size);
    
    RGBColor getColor(const Intersection& a_inter) const;
    
private:
    
    RGBColor m_c1;
    RGBColor m_c2;
    double m_size;
};

inline void Checkerboard3D::setColor1(const RGBColor& a_color)
{
    m_c1 = a_color;
}

inline void Checkerboard3D::setColor2(const RGBColor& a_color)
{
    m_c2 = a_color;
}

inline void Checkerboard3D::setSize(double a_size)
{
    m_size = a_size;
}

#endif /* defined(__RayTracer__Checkerboard3D__) */
