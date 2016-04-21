//
//  TextureMatte.h
//  RayTracer
//

#ifndef __RayTracer__TextureMatte__
#define __RayTracer__TextureMatte__

#include <iostream>
#include <memory>

#include "Material.h"
#include "TextureDiffuse.h"

class MatteT : public Material {
    
public:
    
    MatteT();
    MatteT(const MatteT& a_mt);
    
    ~MatteT();
    
    RGBColor shade(Intersection& a_inter) const;
    
    void setKd(double a_kd);
    void setCd(const std::shared_ptr<Texture> a_cd);
    
private:
    
    std::shared_ptr<TextureDiffuse> m_textureDiffuseBRDF;
};

inline void MatteT::setKd(double a_kd)
{
    m_textureDiffuseBRDF->setCoeff(a_kd);
}

inline void MatteT::setCd(const std::shared_ptr<Texture> a_cd)
{
    m_textureDiffuseBRDF->setTexture(a_cd);
}

#endif /* defined(__RayTracer__TextureMatte__) */
