//
//  Matte.h
//  RayTracer
//

#ifndef __RayTracer__Matte__
#define __RayTracer__Matte__

#include <iostream>
#include <memory>

#include "Material.h"
#include "PerfectDiffuse.h"

class Matte : public Material {
    
public:
    
    Matte();
    Matte(const Matte& a_matte);
    
    ~Matte();
        
    RGBColor shade(Intersection& a_inter) const;
    
    void setKd(double a_kd);
    void setCd(const RGBColor& a_cd);
    
private:
    
    std::shared_ptr<PerfectDiffuse> m_diffuseBRDF;
};

inline void Matte::setKd(double a_kd)
{
    m_diffuseBRDF->setCoeff(a_kd);
}

inline void Matte::setCd(const RGBColor& a_cd)
{
    m_diffuseBRDF->setColor(a_cd);
}

#endif /* defined(__RayTracer__Matte__) */
