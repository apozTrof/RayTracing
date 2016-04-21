//
//  ConstantTexture.cpp
//  RayTracer
//

#include "ConstantTexture.h"

ConstantTexture::ConstantTexture()
:   m_color(RGBColor(0.0))
{}

ConstantTexture::ConstantTexture(const ConstantTexture& a_ct)
:   m_color(a_ct.m_color)
{}

ConstantTexture::~ConstantTexture()
{}

