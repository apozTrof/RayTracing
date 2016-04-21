//
//  Matte.cpp
//  RayTracer
//

#include "Matte.h"
#include "World.h"

Matte::Matte()
:   Material(),
    m_diffuseBRDF(new PerfectDiffuse)
{}

Matte::Matte(const Matte& a_matte)
:   Material(a_matte)
{
    if (a_matte.m_diffuseBRDF)
    {
        m_diffuseBRDF = a_matte.m_diffuseBRDF;
    }
    else
    {
        m_diffuseBRDF = std::make_shared<PerfectDiffuse>(PerfectDiffuse());
    }
}

Matte::~Matte()
{}

RGBColor Matte::shade(Intersection& a_inter) const
{
    Vector wo = -a_inter.m_ray.m_d;
    
    RGBColor L(0.0);
    
    unsigned long nbLights = a_inter.m_pWorld->m_lights.size();
    
    for (int i = 0; i < nbLights; ++i)
    {
        bool contribute = true;
        
        Point position = a_inter.m_pWorld->m_lights[i]->getPosition();
        Point origin = a_inter.m_hitPoint + a_inter.m_normal * a_inter.m_object->m_epsilon;
        Vector wi = a_inter.m_pWorld->m_lights[i]->getDirection(a_inter);
        double tLightMin = a_inter.m_object->m_epsilon;
        double tLightMax = (position - origin).norm();
        
        Ray shadow(origin, wi, 0, tLightMin, tLightMax);
        
        for (int j = 0; j < a_inter.m_pWorld->m_objects.size(); ++j)
        {
            Intersection tmp(a_inter.m_pWorld);
            double t;
            if (a_inter.m_pWorld->m_objects[j]->intersect(shadow, t, tmp))
            {
                contribute = false;
                break;
            }
        }
        
        double cosOmegaI = dot(wi, a_inter.m_normal.normalize());
        if (contribute &&  cosOmegaI > 0)
        {
            L += m_diffuseBRDF->f(a_inter, wi, wo) * a_inter.m_pWorld->m_lights[i]->getRadiance(a_inter) * a_inter.m_pWorld->m_lights[i]->g(a_inter) * cosOmegaI / a_inter.m_pWorld->m_lights[i]->pdf(a_inter);
        }
    }
    
    return L;
}
