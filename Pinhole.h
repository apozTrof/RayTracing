//
//  Pinhole.h
//  RayTracer
//

#ifndef __RayTracer__Pinhole__
#define __RayTracer__Pinhole__

#include <iostream>

#include "Camera.h"

class Pinhole : public Camera {
    
public:
    
    Pinhole();
    Pinhole(const Pinhole& a_ph);
    
    ~Pinhole();

    Pinhole& operator=(const Pinhole& a_ph);

    void setViewPlaneDistance(double a_dist);
    void setZoom(double a_zoom);

    virtual void renderScene(const std::shared_ptr<World> a_pWorld, const std::string& a_filename) const;

private:

    Vector getRayDirection(const Point& a_p) const;

    double m_d;
    double m_zoom;
};

inline void Pinhole::setViewPlaneDistance(double a_dist)
{
    m_d = a_dist;
}

inline void Pinhole::setZoom(double a_zoom)
{
    m_zoom = a_zoom;
}

#endif /* defined(__RayTracer__Pinhole__) */
