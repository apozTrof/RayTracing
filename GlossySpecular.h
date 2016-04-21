//
//  GlossySpecular.h
//  RayTracer
//

#ifndef __RayTracer__GlossySpecular__
#define __RayTracer__GlossySpecular__

#include <iostream>

#include "BRDF.h"

class GlossySpecular : public BRDF {
    
public:
    
    GlossySpecular();
    GlossySpecular(const GlossySpecular& a_gs);
    
    ~GlossySpecular();
    
    virtual RGBColor f(const Intersection& a_inter, const Vector& a_wi, const Vector& a_wo) const;
    
    void setCoeff(double a_k);
    void setExponent(double a_exp);
    
private:
    
    double m_k;
    double m_exp;
};

inline void GlossySpecular::setCoeff(double a_k)
{
    m_k = a_k;
}

inline void GlossySpecular::setExponent(double a_exp)
{
    m_exp = a_exp;
}

#endif /* defined(__RayTracer__GlossySpecular__) */
