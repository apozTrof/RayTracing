//
//  BRDF.h
//  RayTracer
//

#ifndef __RayTracer__BRDF__
#define __RayTracer__BRDF__

#include <iostream>

#include "RGBColor.h"
#include "Vector.h"
#include "Intersection.h"

class BRDF {
    
public:
    
    BRDF();
    BRDF(const BRDF& a_brdf);
    
    ~BRDF();
    
    virtual RGBColor f(const Intersection& a_inter, const Vector& a_wi, const Vector& a_wo) const;
    virtual RGBColor fSample(const Intersection& a_inter, Vector& a_wi, const Vector& a_wo) const;
    
};

#endif /* defined(__RayTracer__BRDF__) */
