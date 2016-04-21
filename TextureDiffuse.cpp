//
//  TextureDiffuse.cpp
//  RayTracer
//
#include "math.h"
#include "TextureDiffuse.h"
#include "ConstantTexture.h"

TextureDiffuse::TextureDiffuse()
:   m_k(0.0)
{
    m_texture = std::make_shared<ConstantTexture>(ConstantTexture());
}

TextureDiffuse::TextureDiffuse(const TextureDiffuse& a_td)
:   m_k(a_td.m_k)
{
    if (a_td.m_texture)
    {
        m_texture = a_td.m_texture;
    }
    else
    {
        m_texture = std::make_shared<ConstantTexture>(ConstantTexture());
    }
}

TextureDiffuse::~TextureDiffuse()
{}

RGBColor TextureDiffuse::f(const Intersection& a_inter, const Vector& a_wi, const Vector& a_wo) const
{
	return m_k * m_texture->getColor(a_inter) * 0.318309886183790671538;
}