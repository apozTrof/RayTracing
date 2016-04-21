//
//  GridAccelerator.h
//  RayTracer
//

#ifndef __RayTracer__GridAccelerator__
#define __RayTracer__GridAccelerator__

#include <iostream>
#include <vector>
#include <memory>
#include <limits>

#include "Accelerator.h"
#include "GeometricObject.h"
#include "BoundingBox.h"
#include "Ray.h"
#include "Intersection.h"

class GridAccelerator : public Accelerator {
    
public:
    
    GridAccelerator(const std::vector<std::shared_ptr<GeometricObject>>& a_obj);
    
    ~GridAccelerator();
    
    BoundingBox objectBound() const;
    BoundingBox worldBound() const;
    
    bool intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const;
    
private:
    
    class Cell {
        
    public:
        
        Cell()
        {}
        
        void addObject(const std::shared_ptr<GeometricObject>& a_object)
        {
            m_objects.push_back(a_object);
        }
        
        unsigned long size() const
        {
            return m_objects.size();
        }
        
        bool intersect(const Ray& a_ray, double& a_t, Intersection& a_inter)
        {
            bool hit = false;
            double mint = std::numeric_limits<double>::max();
            
            Intersection tmpi(a_inter);
            double tmpt;
            
            for (int i = 0; i < m_objects.size(); ++i)
            {
                m_objects[i]->intersect(a_ray, tmpt, tmpi);
                
                if (tmpi.m_hit && tmpt < mint)
                {
                    mint = tmpt;
                    a_inter = tmpi;
                    a_t = mint;
                    hit = true;
                }
            }
            
            return hit;
        }
        
    private:
        
        std::vector<std::shared_ptr<GeometricObject>> m_objects;
    };
    
    int spaceToCell(const Point& a_p, int a_axis) const;
    double cellToSpace(int a_p, int a_axis) const;
    
    int m_nCells[3];
    BoundingBox m_bb;
    Vector m_cellWidth;
    Vector m_invCellWidth;
    std::vector<Cell> m_cells;
    
};

#endif /* defined(__RayTracer__GridAccelerator__) */
