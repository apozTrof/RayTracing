//
//  Phong.cpp
//  RayTracer
//

#include "Phong.h"
#include "World.h"

Phong::Phong()
:   Material(),
    m_diffuseBRDF(new PerfectDiffuse),
    m_glossySpecularBRDF(new GlossySpecular)
{}

Phong::Phong(const Phong& a_phong)
:   Material(a_phong)
{
    if (a_phong.m_diffuseBRDF)
    {
        m_diffuseBRDF = a_phong.m_diffuseBRDF;
    }
    else
    {
        m_diffuseBRDF = std::make_shared<PerfectDiffuse>(PerfectDiffuse());
    }
    
    if (a_phong.m_glossySpecularBRDF)
    {
        m_glossySpecularBRDF = a_phong.m_glossySpecularBRDF;
    }
    else
    {
        m_glossySpecularBRDF = std::make_shared<GlossySpecular>(GlossySpecular());
    }
}

Phong::~Phong()
{}

RGBColor Phong::shade(Intersection& a_inter) const
{
	Vector wo = -a_inter.m_ray.m_d;
	RGBColor L(0.0);
	unsigned long nbLum = a_inter.m_pWorld->m_lights.size();
	Point position, ori;
	//check if the light contribute
	bool cont = true;

	Vector wi;
	double tLmin, tLmax;

	for (int i = 0; i < nbLum; ++i)
	{	
		cont = true;

		position = a_inter.m_pWorld->m_lights[i]->getPosition();
		ori = a_inter.m_hitPoint + a_inter.m_normal * a_inter.m_object->m_epsilon;
		wi = a_inter.m_pWorld->m_lights[i]->getDirection(a_inter);
		tLmin = a_inter.m_object->m_epsilon;
		tLmax = (position.m_x - ori.m_x) / wi.m_x;
		// un peu de latin pour faire le malin *.*
		Ray umbra(ori, wi, 0, tLmin, tLmax);

		for (int j = 0; j < a_inter.m_pWorld->m_objects.size(); ++j)
		{
			Intersection tmp(a_inter.m_pWorld);
			double t;
			if (a_inter.m_pWorld->m_objects[j]->intersect(umbra, t, tmp))
			{
				cont = false;
				break;
			}
		}

		double cosOmegaI = dot(wi, a_inter.m_normal.normalize());
		if (cont &&  cosOmegaI > 0)
		{
			L += m_diffuseBRDF->f(a_inter, wi, wo) * a_inter.m_pWorld->m_lights[i]->getRadiance(a_inter) * cosOmegaI;
			L += m_glossySpecularBRDF->f(a_inter, wi, wo) * a_inter.m_pWorld->m_lights[i]->getRadiance(a_inter) * cosOmegaI;
		}
	}

	return L;
}
