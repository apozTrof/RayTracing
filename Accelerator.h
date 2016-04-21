//
//  Accelerator.h
//  RayTracer
//

#ifndef __RayTracer__Accelerator__
#define __RayTracer__Accelerator__

#include <iostream>
#include <vector>
#include <memory>

#include "GeometricObject.h"
#include "RGBColor.h"

class Accelerator : public GeometricObject {
    
public:
    
    Accelerator();
    
    ~Accelerator();
    
    RGBColor getColor() const;
    
    bool intersect() const;
    
protected:
    
    void refine(std::vector<std::shared_ptr<GeometricObject>>& a_obj) const;
    
    std::vector<std::shared_ptr<GeometricObject>> m_objects;
    
};

inline bool Accelerator::intersect() const
{
    return false;
}

#endif /* defined(__RayTracer__Accelerator__) */
