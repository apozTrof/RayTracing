//
//  ViewPlane.cpp
//  RayTracer
//

#include "ViewPlane.h"

ViewPlane::ViewPlane()
:   m_xRes(400),
    m_yRes(400),
    m_s(1.0),
    m_gamma(1.0),
    m_invGamma(1.0),
    m_maxDepth(5)
{}

ViewPlane::ViewPlane(const ViewPlane& a_vp)
:   m_xRes(a_vp.m_xRes),
    m_yRes(a_vp.m_yRes),
    m_s(a_vp.m_s),
    m_gamma(a_vp.m_gamma),
    m_invGamma(a_vp.m_invGamma),
    m_nbSamples(a_vp.m_nbSamples),
    m_pSampler(a_vp.m_pSampler),
    m_maxDepth(a_vp.m_maxDepth)
{}

ViewPlane::~ViewPlane()
{}

ViewPlane& ViewPlane::operator=(const ViewPlane &a_vp)
{
    if (this == &a_vp)
    {
        return (*this);
    }
    
    m_xRes = a_vp.m_xRes;
    m_yRes = a_vp.m_yRes;
    m_s = a_vp.m_s;
    m_gamma = a_vp.m_gamma;
    m_invGamma = a_vp.m_invGamma;
    m_nbSamples = a_vp.m_nbSamples;
    m_pSampler = a_vp.m_pSampler;
    
    return (*this);
}

void ViewPlane::setSampler(const std::shared_ptr<Sampler> a_pSampler)
{
    m_nbSamples = a_pSampler->getNbSamples();
    m_pSampler = a_pSampler;
}