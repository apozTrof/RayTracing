//
//  Checkerboard2D.h
//  RayTracer
//

#ifndef __RayTracer__Checkerboard2D__
#define __RayTracer__Checkerboard2D__

#include <iostream>

#include "Texture.h"

class Checkerboard2D : public Texture {
    
public:
    
    Checkerboard2D();
    Checkerboard2D(const Checkerboard2D& a_cb2);
    
    ~Checkerboard2D();
    
    void setColor1(const RGBColor& a_color);
    void setColor2(const RGBColor& a_color);
    void setNbSquare(int a_n);
    
    RGBColor getColor(const Intersection& a_inter) const;
    
private:
    
    RGBColor m_c1;
    RGBColor m_c2;
    double m_n;
};

inline void Checkerboard2D::setColor1(const RGBColor& a_color)
{
    m_c1 = a_color;
}

inline void Checkerboard2D::setColor2(const RGBColor& a_color)
{
    m_c2 = a_color;
}

inline void Checkerboard2D::setNbSquare(int a_n)
{
    m_n = a_n;
}

#endif /* defined(__RayTracer__Checkerboard2D__) */
