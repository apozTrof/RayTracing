//
//  PerfectSpecular.h
//  RayTracer
//

#ifndef __RayTracer__PerfectSpecular__
#define __RayTracer__PerfectSpecular__

#include <iostream>

#include "BRDF.h"

class PerfectSpecular : public BRDF {
    
public:
    
    PerfectSpecular();
    PerfectSpecular(const PerfectSpecular& a_ps);
    
    ~PerfectSpecular();
    
    virtual RGBColor fSample(const Intersection& a_inter, Vector& a_wi, const Vector& a_wo) const;
    
    void setCoeff(double a_k);
    void setColor(const RGBColor& a_c);
    
private:
    
    double m_k;
    RGBColor m_c;
};

inline void PerfectSpecular::setCoeff(double a_k)
{
    m_k = a_k;
}

inline void PerfectSpecular::setColor(const RGBColor& a_c)
{
    m_c = a_c;
}

#endif /* defined(__RayTracer__PerfectSpecular__) */
