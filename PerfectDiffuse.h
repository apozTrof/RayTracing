//
//  PerfectDiffuse.h
//  RayTracer
//

#ifndef __RayTracer__PerfectDiffuse__
#define __RayTracer__PerfectDiffuse__

#include <iostream>

#include "BRDF.h"

class PerfectDiffuse : public BRDF {
    
public:
    
    PerfectDiffuse();
    PerfectDiffuse(const PerfectDiffuse& a_pd);
    
    ~PerfectDiffuse();
    
    virtual RGBColor f(const Intersection& a_inter, const Vector& a_wi, const Vector& a_wo) const;
    
    void setCoeff(const double a_k);
    void setColor(const RGBColor& a_c);
    
private:
    
    double m_k;
    RGBColor m_c;
};

inline void PerfectDiffuse::setCoeff(const double a_k)
{
    m_k = a_k;
}

inline void PerfectDiffuse::setColor(const RGBColor& a_c)
{
    m_c = a_c;
}

#endif /* defined(__RayTracer__PerfectDiffuse__) */
