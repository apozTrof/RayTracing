//
//  Accelerator.cpp
//  RayTracer
//

#include "Accelerator.h"

Accelerator::Accelerator()
{}

Accelerator::~Accelerator()
{}

RGBColor Accelerator::getColor() const
{
    std::cerr << "Unimplemented Accelerator::getColor() method called" << std::endl;
    
    return RGBColor();
}

void Accelerator::refine(std::vector<std::shared_ptr<GeometricObject>>& a_obj) const
{
    for (int i = 0; i < m_objects.size(); ++i)
    {
        if (m_objects[i]->intersect())
        {
            a_obj.push_back(m_objects[i]);
        }
        else
        {
            m_objects[i]->refine(a_obj);
        }
    }
}