//
//  Camera.cpp
//  RayTracer
//

#include "Camera.h"

Camera::Camera()
:   m_center(Point(0,0,500)),
    m_lookAt(Point(0,0,0)),
    m_up(Vector(0,1,0)),
    m_u(Vector(1,0,0)),
    m_v(Vector(0,1,0)),
    m_w(Vector(0,0,1))
{}

Camera::Camera(const Camera& a_cam)
:   m_center(a_cam.m_center),
    m_lookAt(a_cam.m_lookAt),
    m_up(a_cam.m_up),
    m_u(a_cam.m_u),
    m_v(a_cam.m_v),
    m_w(a_cam.m_w)
{}

Camera::~Camera()
{}

Camera& Camera::operator=(const Camera& a_cam)
{
    if (this == &a_cam)
    {
        return *this;
    }
    
    m_center = a_cam.m_center;
    m_lookAt = a_cam.m_lookAt;
    m_up = a_cam.m_up;
    m_u = a_cam.m_u;
    m_v = a_cam.m_v;
    m_w = a_cam.m_w;
    
    return *this;
}

void Camera::buildCCS()
{
    m_w = m_center - m_lookAt;
    m_w = m_w.normalize();
    
    m_u = cross(m_up, m_w);
    m_u = m_u.normalize();
    
    m_v = cross(m_w, m_u);
    
    if (std::abs(m_center.m_x - m_lookAt.m_x) < std::numeric_limits<double>::epsilon()
        && std::abs(m_center.m_z - m_lookAt.m_z) < std::numeric_limits<double>::epsilon()
        && m_center.m_y > m_lookAt.m_y)
    {
        m_u = Vector(0, 0, 1);
		m_v = Vector(1, 0, 0);
		m_w = Vector(0, 1, 0);
    }
    
    if (std::abs(m_center.m_x - m_lookAt.m_x) < std::numeric_limits<double>::epsilon()
        && std::abs(m_center.m_z - m_lookAt.m_z) < std::numeric_limits<double>::epsilon()
        && m_center.m_y < m_lookAt.m_y)
    {
        m_u = Vector(1, 0, 0);
		m_v = Vector(0, 0, 1);
		m_w = Vector(0, -1, 0);
    }
}
