//
//  GeometricObject.cpp
//  RayTracer
//

#include "GeometricObject.h"

unsigned int GeometricObject::m_nextShapeId = 1;

GeometricObject::GeometricObject()
:   m_color(0.0),
    m_shapeId(m_nextShapeId++)
{}

GeometricObject::GeometricObject(const GeometricObject& a_object)
:   m_shapeId(m_nextShapeId++)
{
    m_color = a_object.m_color;
}

GeometricObject::GeometricObject(const std::shared_ptr<GeometricTransform> a_pO2W, const std::shared_ptr<GeometricTransform> a_pW2O)
:   m_objectToWorld(a_pO2W),
    m_worldToObject(a_pW2O),
    m_shapeId(m_nextShapeId++)
{}

GeometricObject::~GeometricObject()
{}

BoundingBox GeometricObject::worldBound() const
{
    return (*m_objectToWorld)(objectBound());
}

void GeometricObject::setColor(const RGBColor& a_color)
{
    m_color = a_color;
}

void GeometricObject::setMaterial(const std::shared_ptr<Material> a_pMat)
{
    m_pMaterial = a_pMat;
}

bool GeometricObject::intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const
{
    std::cerr << "Unimplemented GeometricObject::intersect(.) method called" << std::endl;
    
    return false;
}

double GeometricObject::area() const
{
    std::cerr << "Unimplemented GeometricObject::area() method called" << std::endl;
    
    return 0.;
}

void GeometricObject::refine(std::vector<std::shared_ptr<GeometricObject>>& a_obj) const
{
    std::cerr << "Unimplemented GeometricObject::refine() method called" << std::endl;
}

GeometricObject& GeometricObject::operator=(const GeometricObject &a_obj)
{
    if (this == &a_obj)
    {
        return *this;
    }
    
    m_color = a_obj.m_color;
    
    return *this;
}

bool GeometricObject::QuadraticSolution(double a_a, double a_b, double a_c, double* a_pT0, double* a_pT1) const
{
    // Find quadratic discriminant
    double discrim = a_b*a_b - 4*a_a*a_c;
    
    if (discrim < 0.0)
    {
        return false;
    }
    
    double rootDiscrim = sqrt(discrim);
    
    // Compute quadratic t values
    double q;
    if (a_b < 0.0)
    {
        q = -0.5 * (a_b - rootDiscrim);
    }
    else
    {
        q = -0.5 * (a_b + rootDiscrim);
    }
    
    *a_pT0 = q / a_a;
    *a_pT1 = a_c / q;
    
    if (*a_pT0 > *a_pT1)
    {
        std::swap(*a_pT0, *a_pT1);
    }
    
    return true;
}