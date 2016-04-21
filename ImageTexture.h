//
//  ImageTexture.h
//  RayTracer
//

#ifndef __RayTracer__ImageTexture__
#define __RayTracer__ImageTexture__

#include <iostream>

#include "Texture.h"

#include "CImg.h"

using namespace cimg_library;

class ImageTexture : public Texture {
    
public:
    
    ImageTexture();
    ImageTexture(const ImageTexture& a_it);
    
    ~ImageTexture();
    
    void setImage(const CImg<double>& a_img);
    RGBColor getColor(const Intersection& a_inter) const;
    
private:
    
    std::shared_ptr<CImg<double>> m_img;
};

inline void ImageTexture::setImage(const CImg<double>& a_img)
{
    m_img = std::make_shared<CImg<double>>(a_img);
}

#endif /* defined(__RayTracer__ImageTexture__) */
