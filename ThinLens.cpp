//
//  ThinLens.cpp
//  RayTracer
//

#include "ThinLens.h"
#include "RGBColor.h"
#include "ViewPlane.h"
#include "World.h"

#include "CImg.h"

using namespace cimg_library;

ThinLens::ThinLens()
:   Camera(),
    m_radius(1.0),
    m_d(500),
    m_f(100),
    m_zoom(1.0)
{}

ThinLens::ThinLens(const ThinLens& a_tl)
:   Camera(),
    m_radius(a_tl.m_radius),
    m_d(a_tl.m_d),
    m_f(a_tl.m_f),
    m_zoom(a_tl.m_zoom),
    m_pSampler(a_tl.m_pSampler)
{}

ThinLens::~ThinLens()
{}

ThinLens& ThinLens::operator=(const ThinLens& a_tl)
{
    if (this == &a_tl)
    {
        return *this;
    }
    
    Camera::operator=(a_tl);
    
    m_radius = a_tl.m_radius;
    m_d = a_tl.m_d;
    m_f = a_tl.m_f;
    m_zoom = a_tl.m_zoom;
    m_pSampler = a_tl.m_pSampler;
    
    return *this;
}

void ThinLens::setSampler(const std::shared_ptr<Sampler> a_pSampler)
{
    m_pSampler = a_pSampler;
    m_pSampler->mapSquare2Circle();
}

void ThinLens::renderScene(const std::shared_ptr<World> a_pWorld, const std::string& a_filename) const
{
	RGBColor color;
	ViewPlane vp(a_pWorld->m_vp);
	Ray ray;
	Point sample;
	double x, y; 
	int tt = vp.m_pSampler->getNbSamples();
	sample = vp.m_pSampler->sampleUnitSquare();

	CImg<double> img(vp.m_xRes, vp.m_yRes, 1, 3, 0);

	vp.m_s /= m_zoom;

	for (int i = 0; i < vp.m_xRes - 1; ++i) //up
	{
		for (int j = 0; j < vp.m_yRes - 1; ++j) //accross
		{
			color = RGBColor(0.0);
			
			for (int s = 0; s < vp.m_nbSamples; ++s)
			{
				sample = vp.m_pSampler->sampleUnitSquare();
				x = vp.m_s * (i - 0.5 * vp.m_xRes + sample.m_x);
				y = -1.0 * vp.m_s * (j - 0.5 * vp.m_yRes + sample.m_y);
				//y = vp.m_s * (j - 0.5 * vp.m_yRes + sample.m_y);
				int test  = m_pSampler->getNbSamples();
				for (int l = 0; l < m_pSampler->getNbSamples(); ++l)
				{
					Point circleSample = m_pSampler->sampleUnitCircle() * m_radius;
					
					ray.m_o = Point(circleSample.m_x, circleSample.m_y, circleSample.m_z);
					ray.m_d = getRayDirection(Point((x*m_f) / m_d, (y*m_f) / m_d, 0.0), circleSample);

					color += a_pWorld->m_pTracer->traceRay(ray) / vp.m_nbSamples;
				}
			}

			img(i, j, 0) = color.m_r;
			img(i, j, 1) = color.m_g;
			img(i, j, 2) = color.m_b;
		}
	}


	img *= 255.0;
	img.save(a_filename.c_str());

}

Vector ThinLens::getRayDirection(const Point& a_pixelPoint, const Point& a_lensPoint) const
{
  Vector retVal;

	retVal = m_u*(a_pixelPoint.m_x - a_lensPoint.m_x) + m_v*(a_pixelPoint.m_y - a_lensPoint.m_y) - m_w*m_f;
	retVal.normalize();
	return retVal;
}
