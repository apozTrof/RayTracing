//
//  TextureDiffuse.h
//  RayTracer
//

#ifndef __RayTracer__TextureDiffuse__
#define __RayTracer__TextureDiffuse__

#include <iostream>
#include <memory>

#include "BRDF.h"
#include "Texture.h"

class TextureDiffuse : public BRDF {
    
public:
    
    TextureDiffuse();
    TextureDiffuse(const TextureDiffuse& a_td);
    
    ~TextureDiffuse();
    
    virtual RGBColor f(const Intersection& a_inter, const Vector& a_wi, const Vector& a_wo) const;
    
    void setCoeff(double a_k);
    void setTexture(const std::shared_ptr<Texture> a_texture);
    
private:
    
    double m_k;
    std::shared_ptr<Texture> m_texture;
};

inline void TextureDiffuse::setCoeff(double a_k)
{
    m_k = a_k;
}

inline void TextureDiffuse::setTexture(const std::shared_ptr<Texture> a_texture)
{
    m_texture = a_texture;
}

#endif /* defined(__RayTracer__TextureDiffuse__) */
