//
//  Mirror.cpp
//  RayTracer
//

#include "Mirror.h"
#include "World.h"

Mirror::Mirror()
:   Phong(),
    m_perfectSpecularBRDF(new PerfectSpecular)
{}

Mirror::Mirror(const Mirror& a_ref)
:   Phong(a_ref)
{
    if (a_ref.m_perfectSpecularBRDF)
    {
        m_perfectSpecularBRDF = a_ref.m_perfectSpecularBRDF;
    }
    else
    {
        m_perfectSpecularBRDF = std::make_shared<PerfectSpecular>(PerfectSpecular());
    }
}

Mirror::~Mirror()
{}

RGBColor Mirror::shade(Intersection& a_inter) const
{
	RGBColor L = Phong::shade(a_inter);
	RGBColor C;
	Vector w_i;
	Vector w_o = a_inter.m_ray.m_d;

	if (a_inter.m_ray.m_depth < a_inter.m_pWorld->m_vp.m_maxDepth)
	{
		C = m_perfectSpecularBRDF->fSample(a_inter, w_i, w_o); 
		a_inter.m_ray.m_depth++;
		a_inter.m_ray.m_o = a_inter.m_hitPoint;
		a_inter.m_ray.m_d = w_i;
		L += C*((Whitted*)(a_inter.m_pWorld->m_pTracer.get()))->traceRay(a_inter.m_ray, a_inter.m_ray.m_depth);
	}
	return L;
}
