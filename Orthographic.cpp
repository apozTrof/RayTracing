//
//  Orthographic.cpp
//  RayTracer
//

#include "Orthographic.h"
#include "RGBColor.h"
#include "ViewPlane.h"
#include "World.h"

#include "CImg.h"

using namespace cimg_library;

Orthographic::Orthographic()
:   Camera(),
    m_d(100),
    m_zoom(1.0),
    m_direction(Vector(0, 0, -1))
{}

Orthographic::Orthographic(const Orthographic& a_ortho)
:   Camera(a_ortho),
    m_d(a_ortho.m_d),
    m_zoom(a_ortho.m_zoom),
    m_direction(a_ortho.m_direction)
{}

Orthographic::~Orthographic()
{}

Orthographic& Orthographic::operator=(const Orthographic& a_ortho)
{
    if (this == &a_ortho)
    {
        return *this;
    }
    
    Camera::operator=(a_ortho);
    
    m_d = a_ortho.m_d;
    m_zoom = a_ortho.m_zoom;
    m_direction = a_ortho.m_direction;
    
    return *this;
}

void Orthographic::renderScene(const std::shared_ptr<World> a_pWorld, const std::string& a_filename) const
{
    RGBColor color;
    ViewPlane vp(a_pWorld->m_vp);
    Ray ray;
    double x, y;
    Point sample;
    
    CImg<double> img(vp.m_xRes, vp.m_yRes, 1, 3, 0);
    
    vp.m_s /= m_zoom;
    ray.m_d = m_direction;
    
    for (int i = 0; i < vp.m_xRes; ++i)
    {
        for (int j = 0; j < vp.m_yRes; ++j)
        {
            color = RGBColor(0.0);
            
            for (int s = 0;  s < vp.m_nbSamples; ++s)
            {
                sample = vp.m_pSampler->sampleUnitSquare();
                
                x = vp.m_s * (i - 0.5 * vp.m_xRes + sample.m_x);
                y = -1.0 * vp.m_s * (j - 0.5 * vp.m_yRes + sample.m_y);
                
                ray.m_o = Point(x, y, m_d);
                
                color += a_pWorld->m_pTracer->traceRay(ray) / vp.m_nbSamples;
            }
            
            img(i,j,0) = color.m_r;
            img(i,j,1) = color.m_g;
            img(i,j,2) = color.m_b;
        }
    }

    
    img*=255.0;
    img.save(a_filename.c_str());
}