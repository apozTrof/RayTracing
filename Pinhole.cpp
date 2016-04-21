//
//  Pinhole.cpp
//  RayTracer
//

#include "Pinhole.h"
#include "RGBColor.h"
#include "ViewPlane.h"
#include "World.h"

#include "CImg.h"

using namespace cimg_library;

Pinhole::Pinhole()
:   Camera(),
    m_d(500),
    m_zoom(1.0)
{}

Pinhole::Pinhole(const Pinhole& a_ph)
:   Camera(a_ph),
    m_d(a_ph.m_d),
    m_zoom(a_ph.m_zoom)
{}

Pinhole::~Pinhole()
{}

Pinhole& Pinhole::operator=(const Pinhole& a_ph)
{
    if (this == &a_ph)
    {
        return *this;
    }
    
    Camera::operator=(a_ph);
    
    m_d = a_ph.m_d;
    m_zoom = a_ph.m_zoom;
    
    return *this;
}

void Pinhole::renderScene(const std::shared_ptr<World> a_pWorld, const std::string& a_filename) const
{
	RGBColor color;
	ViewPlane vp(a_pWorld->m_vp);
	Ray ray;
	//sample point and sample point on a pixel
	Point sample, pp;
	CImg<double> img(vp.m_xRes, vp.m_yRes, 1, 3, 0);

	vp.m_s /= m_zoom;

	for (int i = 0; i < vp.m_xRes; ++i)
	{
		for (int j = 0; j < vp.m_yRes; ++j)
		{
			color = RGBColor(0.0);

			for (int s = 0; s < vp.m_nbSamples; ++s)
			{
				sample = vp.m_pSampler->sampleUnitSquare();
				
				pp.m_x = vp.m_s * (i - 0.5 * vp.m_xRes + sample.m_x);
				pp.m_y = -1.0 * vp.m_s * (j - 0.5 * vp.m_yRes + sample.m_y);

				ray.m_o = Point(m_center.m_x, m_center.m_y, m_center.m_z);
				ray.m_d = getRayDirection(Point(pp.m_x, pp.m_y, 0.0));

				color += a_pWorld->m_pTracer->traceRay(ray) / vp.m_nbSamples;
			}

			img(i, j, 0) = color.m_r;
			img(i, j, 1) = color.m_g;
			img(i, j, 2) = color.m_b;
		}
	}


	img *= 255.0;
	img.save(a_filename.c_str());
}

Vector Pinhole::getRayDirection(const Point& a_p) const
{
	Vector retVal;
	retVal = m_u * a_p.m_x + m_v * a_p.m_y - m_w *m_d;
	return retVal.normalize();
}