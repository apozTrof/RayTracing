//
//  Orthographic.h
//  RayTracer
//

#ifndef __RayTracer__Orthographic__
#define __RayTracer__Orthographic__

#include <iostream>

#include "Camera.h"
#include "Vector.h"

class Orthographic : public Camera {
    
public:
    
    Orthographic();
    Orthographic(const Orthographic& a_ortho);
    
    ~Orthographic();
    
    Orthographic& operator=(const Orthographic& a_ortho);
    
    void setViewPlaneDistance(double a_pos);
    void setZoom(double a_zoom);
    
    virtual void renderScene(const std::shared_ptr<World> a_pWorld, const std::string& a_filename) const;
    
private:
    
    double m_d;
    double m_zoom;
    Vector m_direction;
};

inline void Orthographic::setViewPlaneDistance(double a_dist)
{
    m_d = a_dist;
}

inline void Orthographic::setZoom(double a_zoom)
{
    m_zoom = a_zoom;
}

#endif /* defined(__RayTracer__Orthographic__) */
