//
//  ViewPlane.h
//  RayTracer
//

#ifndef __RayTracer__ViewPlane__
#define __RayTracer__ViewPlane__

#include <iostream>
#include <memory>

#include "Sampler.h"

class ViewPlane {
    
public:
        
    ViewPlane();
    ViewPlane(const ViewPlane& a_vp);
    
    ~ViewPlane();
    
    ViewPlane& operator=(const ViewPlane& a_vp);
    
    void setXRes(int a_xRes);
    void setYRes(int a_yRes);
    void setPixelSize(double a_pixelSize);
    void setGamma(double a_gamma);
    void setSampler(const std::shared_ptr<Sampler> a_pSampler);
        
    int m_xRes;
    int m_yRes;
    double m_s;
    double m_gamma;
    double m_invGamma;
    const int m_maxDepth;
    
    int m_nbSamples;
    std::shared_ptr<Sampler> m_pSampler;
};

inline void ViewPlane::setXRes(int a_xRes)
{
    m_xRes = a_xRes;
}

inline void ViewPlane::setYRes(int a_yRes)
{
    m_yRes = a_yRes;
}

inline void ViewPlane::setPixelSize(double a_pixelSize)
{
    m_s = a_pixelSize;
}

inline void ViewPlane::setGamma(double a_gamma)
{
    m_gamma = a_gamma;
}

#endif /* defined(__RayTracer__ViewPlane__) */
