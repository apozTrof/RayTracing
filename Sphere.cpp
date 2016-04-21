//
//  Sphere.cpp
//  RayTracer
//

#define _USE_MATH_DEFINES

#include <cmath>

#include "Sphere.h"
#include "GeometricTransform.h"

Sphere::Sphere(const std::shared_ptr<GeometricTransform> a_pO2W, const std::shared_ptr<GeometricTransform> a_pW2O, double a_rad)
:   GeometricObject(a_pO2W, a_pW2O),
    m_rad(a_rad)
{
    m_obb = objectBound();
}

BoundingBox Sphere::objectBound() const
{
    return BoundingBox(Point(-m_rad, -m_rad, -m_rad), Point(m_rad, m_rad, m_rad));
}

bool Sphere::intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const
{
    Ray objRay;
    (*m_worldToObject)(a_ray, &objRay);
    
    double a = objRay.m_d.m_x*objRay.m_d.m_x + objRay.m_d.m_y*objRay.m_d.m_y
                + objRay.m_d.m_z*objRay.m_d.m_z;
    double b = 2 * (objRay.m_d.m_x * objRay.m_o.m_x + objRay.m_d.m_y * objRay.m_o.m_y
                + objRay.m_d.m_z * objRay.m_o.m_z);
    double c = objRay.m_o.m_x*objRay.m_o.m_x + objRay.m_o.m_y*objRay.m_o.m_y
                + objRay.m_o.m_z*objRay.m_o.m_z - m_rad*m_rad;
    
    double t0, t1;
    if (!QuadraticSolution(a,b,c,&t0,&t1))
    {
        return false;
    }
    
    if (t0 > objRay.m_maxt || t1 < objRay.m_mint)
    {
        return false;
    }
    double tHit = t0;
    if (t0 < objRay.m_mint)
    {
        tHit = t1;
        if (tHit > objRay.m_maxt)
        {
            return false;
        }
    }
    
    Point pHit = objRay(tHit);
    
    double theta = acos(pHit.m_y / m_rad);
    double yRad = sqrt(pHit.m_x*pHit.m_x + pHit.m_z*pHit.m_z);
    double cosPhi = pHit.m_z / yRad;
    double sinPhi = pHit.m_x / yRad;
    
    Vector dpdu(2*M_PI*pHit.m_z, 0, -2*M_PI*pHit.m_x);
    Vector dpdv(pHit.m_y*sinPhi*M_PI, -m_rad*sin(theta)*M_PI, pHit.m_y*cosPhi*M_PI);
    Normal n(cross(dpdv, dpdu).normalize());
    
    a_t = tHit;
    
    a_inter.m_hit = true;
    a_inter.m_hitPoint = (*m_objectToWorld)(pHit);
    a_inter.m_normal = (*m_objectToWorld)(n);
    a_inter.m_object = shared_from_this();
    a_inter.m_color = m_color;
    a_inter.m_ray = a_ray;
    a_inter.m_material = m_pMaterial;
    
    double phi = atan2(pHit.m_x, pHit.m_z);
    if (phi < 0.0)
    {
        phi += 2*M_PI;
    }
    
    a_inter.m_u = phi / (2*M_PI);
    a_inter.m_v = theta / M_PI;
    
    return true;
}

double Sphere::area() const
{
    return 4*M_PI*m_rad*m_rad;
}
