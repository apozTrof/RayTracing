//
//  GeometricObject.h
//  RayTracer
//

#ifndef __RayTracer__GeometricObject__
#define __RayTracer__GeometricObject__

#include <iostream>
#include <memory>
#include <vector>

#include "BoundingBox.h"
#include "Ray.h"
#include "Intersection.h"
#include "RGBColor.h"
#include "GeometricTransform.h"

class GeometricObject : public std::enable_shared_from_this<GeometricObject> {
    
public:
    
    GeometricObject();
    GeometricObject(const GeometricObject& a_object);    
    GeometricObject(const std::shared_ptr<GeometricTransform> a_pO2W, const std::shared_ptr<GeometricTransform> a_pW2O);
    
    virtual ~GeometricObject();
    
    virtual BoundingBox objectBound() const = 0;
    virtual BoundingBox worldBound() const;
    
    virtual RGBColor getColor() const;
    void setColor(const RGBColor& a_color);
    
    virtual std::shared_ptr<Material> getMaterial() const;
    void setMaterial(const std::shared_ptr<Material> a_pMat);
    
    virtual bool intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const;
    virtual double area() const;
    virtual void refine(std::vector<std::shared_ptr<GeometricObject>>& a_obj) const;
    
    virtual bool intersect() const;
    
    const std::shared_ptr<GeometricTransform> m_objectToWorld;
    const std::shared_ptr<GeometricTransform> m_worldToObject;
    
    const unsigned int m_shapeId;
    static unsigned int m_nextShapeId;
    
    const double m_epsilon = 1e-4f;
    
protected:
        
    GeometricObject& operator=(const GeometricObject& a_obj);
    bool QuadraticSolution(double a_a, double a_b, double a_c, double* a_pT0, double* a_pT1) const;
        
    RGBColor m_color;
    std::shared_ptr<Material> m_pMaterial;
};

inline RGBColor GeometricObject::getColor() const
{
    return m_color;
}

inline std::shared_ptr<Material> GeometricObject::getMaterial() const
{
    return m_pMaterial;
}

inline bool GeometricObject::intersect() const
{
    return true;
}

#endif /* defined(__RayTracer__GeometricObject__) */
