//
//  Phong.h
//  RayTracer
//

#ifndef __RayTracer__Phong__
#define __RayTracer__Phong__

#include <iostream>
#include <memory>

#include "Material.h"
#include "PerfectDiffuse.h"
#include "GlossySpecular.h"

class Phong : public Material {
    
public:
    
    Phong();
    Phong(const Phong& a_phong);
    
    ~Phong();
        
    RGBColor shade(Intersection& a_inter) const;
    
    void setKd(double a_kd);
    void setCd(const RGBColor& a_cd);
    void setKs(double a_ks);
    void setExponent(double a_exp);
    
private:
    
    std::shared_ptr<PerfectDiffuse> m_diffuseBRDF;
    std::shared_ptr<GlossySpecular> m_glossySpecularBRDF;
};

inline void Phong::setKd(double a_kd)
{
    m_diffuseBRDF->setCoeff(a_kd);
}

inline void Phong::setCd(const RGBColor& a_cd)
{
    m_diffuseBRDF->setColor(a_cd);
}

inline void Phong::setKs(double a_ks)
{
    m_glossySpecularBRDF->setCoeff(a_ks);
}

inline void Phong::setExponent(double a_exp)
{
    m_glossySpecularBRDF->setExponent(a_exp);
}

#endif /* defined(__RayTracer__Phong__) */
