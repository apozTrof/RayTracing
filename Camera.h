//
//  Camera.h
//  RayTracer
//

#ifndef __RayTracer__Camera__
#define __RayTracer__Camera__

#include <iostream>
#include <string>
#include <memory>

#include "Point.h"
#include "Vector.h"

class World;

class Camera {
    
public:
    
    Camera();
    Camera(const Camera& a_cam);
    
    virtual ~Camera();
    
    Camera& operator=(const Camera& a_cam);
    
    void setCenter(const Point& a_p);
    void setLookAt(const Point& a_p);
    void setUpVector(const Vector& a_v);
    
    void buildCCS();
    
    virtual void renderScene(const std::shared_ptr<World> a_pWorld, const std::string& a_filename) const = 0;
    
protected:
    
    Point m_center;
    Point m_lookAt;
    Vector m_up;
    Vector m_u;
    Vector m_v;
    Vector m_w;
};

inline void Camera::setCenter(const Point& a_p)
{
    m_center = a_p;
}

inline void Camera::setLookAt(const Point& a_p)
{
    m_lookAt = a_p;
}

inline void Camera::setUpVector(const Vector& a_v)
{
    m_up = a_v;
}

#endif /* defined(__RayTracer__Camera__) */
