//
//  Mirror.h
//  RayTracer
//

#ifndef __RayTracer__Mirror__
#define __RayTracer__Mirror__

#include <iostream>
#include <memory>

#include "Phong.h"
#include "PerfectSpecular.h"

class Mirror : public Phong {
    
public:
    
    Mirror();
    Mirror(const Mirror& a_ref);
    
    ~Mirror();
    
    RGBColor shade(Intersection& a_inter) const;
    
    void setKr(double a_kr);
    void setCr(const RGBColor& a_cr);
    
private:
    
    std::shared_ptr<PerfectSpecular> m_perfectSpecularBRDF;
};

inline void Mirror::setKr(double a_kr)
{
    m_perfectSpecularBRDF->setCoeff(a_kr);
}

inline void Mirror::setCr(const RGBColor& a_cr)
{
    m_perfectSpecularBRDF->setColor(a_cr);
}

#endif /* defined(__RayTracer__Mirror__) */
