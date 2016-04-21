//
//  BRDF.cpp
//  RayTracer
//

#include "BRDF.h"

BRDF::BRDF()
{}

BRDF::BRDF(const BRDF& a_brdf)
{}

BRDF::~BRDF()
{}

RGBColor BRDF::f(const Intersection& a_inter, const Vector& a_wi, const Vector& a_wo) const
{
    return RGBColor(0.0);
}

RGBColor BRDF::fSample(const Intersection& a_inter, Vector& a_wi, const Vector& a_wo) const
{
    return RGBColor(0.0);
}
