//
//  FishEye.cpp
//  RayTracer
//

#include "FishEye.h"
#include "RGBColor.h"
#include "ViewPlane.h"
#include "World.h"

#include "CImg.h"

using namespace cimg_library;

FishEye::FishEye()
:   Camera(),
    m_maxPsi(90.0)
{}

FishEye::FishEye(const FishEye& a_fe)
:   Camera(a_fe),
    m_maxPsi(a_fe.m_maxPsi)
{}

FishEye::~FishEye()
{}

FishEye& FishEye::operator=(const FishEye& a_fe)
{
    if (this == &a_fe)
    {
        return *this;
    }
    
    Camera::operator=(a_fe);
    
    m_maxPsi = a_fe.m_maxPsi;
    
    return *this;
}

void FishEye::renderScene(const std::shared_ptr<World> a_pWorld, const std::string& a_filename) const
{
	RGBColor color;
	ViewPlane vp(a_pWorld->m_vp);
	Ray ray;
	double x, y;
	Point sample, pp;
	double rSquared;

	CImg<double> img(vp.m_xRes, vp.m_yRes, 1, 3, 0);

	for (int i = 0; i < vp.m_xRes; ++i) //up
	{
		for (int j = 0; j < vp.m_yRes; ++j) //accross
		{
			color = RGBColor(0.0);

			for (int s = 0; s < vp.m_nbSamples; ++s)
			{
				sample = vp.m_pSampler->sampleUnitSquare();

				pp.m_x = vp.m_s * (i - 0.5 * vp.m_xRes + sample.m_x);
				pp.m_y = -1.0 * vp.m_s * (j - 0.5 * vp.m_yRes + sample.m_y);



				ray.m_o = Point(m_center.m_x, m_center.m_y, m_center.m_z);
				ray.m_d = getRayDirection(pp, vp.m_xRes, vp.m_yRes, vp.m_s, rSquared);

				if (rSquared <= 1.0)
				{
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

Vector FishEye::getRayDirection(const Point& a_p, int a_xRes, int a_yRes, double a_s, double& a_rSquared) const
{
	Vector retVal(0,0,0);
	double xn, yn;
	const double 	PI_ON_180 = 0.0174532925199432957;
	//compute normnalized device coordinates
	Point pn(a_p.m_x * (2.0 / (a_s*a_xRes)), a_p.m_y * (2.0 / (a_s*a_yRes)), 0.0);
	a_rSquared = pn.m_x*pn.m_x + pn.m_y*pn.m_y;
	
	if (a_rSquared <= 1.0){
		float r = sqrt(a_rSquared);
		float psi = r *m_maxPsi*PI_ON_180;
		float sin_psi = sin(psi);
		float cos_psi = cos(psi);
		float sin_a = pn.m_y / r;
		float cos_a = pn.m_x / r;
		retVal = m_u*sin_psi*cos_a + m_v*sin_a*sin_psi - m_w*cos_psi;
		return (retVal.normalize());
	}
	else
		return retVal;
	
}

