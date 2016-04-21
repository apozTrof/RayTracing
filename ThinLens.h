//
//  ThinLens.h
//  RayTracer
//

#ifndef __RayTracer__ThinLens__
#define __RayTracer__ThinLens__

#include <iostream>
#include <memory>

#include "Camera.h"
#include "Sampler.h"

class ThinLens : public Camera {
    
public:
    
    ThinLens();
    ThinLens(const ThinLens& a_tl);
    
    ~ThinLens();
    
    ThinLens& operator=(const ThinLens& a_tl);
    
    void setSampler(const std::shared_ptr<Sampler> a_pSampler);
    void setViewPlaneDistance(double a_dist);
    void setZoom(double a_zoom);
    void setFocalDistance(double a_fd);
    void setLensRadius(double a_r);
    
    virtual void renderScene(const std::shared_ptr<World> a_pWorld, const std::string& a_filename) const;
    
private:
    
    Vector getRayDirection(const Point& a_pixelPoint, const Point& a_lensPoint) const;
    
    double m_radius;
    double m_d;
    double m_f;
    double m_zoom;
    std::shared_ptr<Sampler> m_pSampler;
};

inline void ThinLens::setLensRadius(double a_r)
{
    m_radius = a_r;
}

inline void ThinLens::setViewPlaneDistance(double a_dist)
{
    m_d = a_dist;
}

inline void ThinLens::setFocalDistance(double a_fd)
{
    m_f = a_fd;
}

inline void ThinLens::setZoom(double a_zoom)
{
    m_zoom = a_zoom;
}

#endif /* defined(__RayTracer__ThinLens__) */
