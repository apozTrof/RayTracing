//
//  ImageTexture.cpp
//  RayTracer
//

#include "ImageTexture.h"

ImageTexture::ImageTexture()
{}

ImageTexture::ImageTexture(const ImageTexture& a_it)
{
    if (a_it.m_img)
    {
        m_img = a_it.m_img;
    }
}

ImageTexture::~ImageTexture()
{}

RGBColor ImageTexture::getColor(const Intersection& a_inter) const
{
    double row(a_inter.m_v * (m_img->height() - 1));
    double column(a_inter.m_u * (m_img->width() - 1));
    
    RGBColor color;
    
    color.m_r = m_img->cubic_atXY(column,row,0) / 255.0;
    color.m_g = m_img->cubic_atXY(column,row,1) / 255.0;
    color.m_b = m_img->cubic_atXY(column,row,2) / 255.0;
    
    return color;
}