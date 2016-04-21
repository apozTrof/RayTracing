//
//  RGBColor.h
//  RayTracer
//

#ifndef __RayTracer__RGBColor__
#define __RayTracer__RGBColor__

#include <iostream>
#include <algorithm>

class RGBColor {
    
public:
        
    RGBColor();
    RGBColor(double a_color);
    RGBColor(double a_r, double a_g, double a_b);
    RGBColor(const RGBColor& a_color);
    
    ~RGBColor(void);
    
    RGBColor& operator=(const RGBColor& a_color);
    RGBColor operator+(const RGBColor& a_color) const;
    RGBColor& operator+=(const RGBColor& a_color);
    RGBColor operator*(const double a_k) const;
    RGBColor& operator*=(const double a_k);
    RGBColor operator/(const double a_k) const;
    RGBColor& operator/=(const double a_k);
    RGBColor operator*(const RGBColor& a_color) const;
    bool operator==(const RGBColor& a_color) const;
    
    RGBColor powc(const double a_k) const;
    double average() const;
        
    double m_r;
    double m_g;
    double m_b;
};

inline RGBColor RGBColor::operator+(const RGBColor &a_color) const
{
    double r = std::min(m_r + a_color.m_r, 1.0);
    double g = std::min(m_g + a_color.m_g, 1.0);
    double b = std::min(m_b + a_color.m_b, 1.0);
    
    return (RGBColor(r, g, b));
}

inline RGBColor& RGBColor::operator+=(const RGBColor& a_color)
{
	m_r = std::min(m_r + a_color.m_r, 1.0);
    m_g = std::min(m_g + a_color.m_g, 1.0);
    m_b = std::min(m_b + a_color.m_b, 1.0);
    return (*this);
}

inline RGBColor RGBColor::operator*(const double a_k) const
{
	return (RGBColor (m_r * a_k, m_g * a_k, m_b * a_k));
}

inline RGBColor& RGBColor::operator*=(const double a_k)
{
	m_r *= a_k; m_g *= a_k; m_b *= a_k;
	return (*this);
}

inline RGBColor RGBColor::operator/(const double a_k) const
{
	return (RGBColor (m_r / a_k, m_g / a_k, m_b / a_k));
}

inline RGBColor& RGBColor::operator/=(const double a_k)
{
	m_r /= a_k; m_g /= a_k; m_b /= a_k;
	return (*this);
}

inline RGBColor RGBColor::operator*(const RGBColor& a_color) const
{
	return (RGBColor (m_r * a_color.m_r, m_g * a_color.m_g, m_b * a_color.m_b));
}

inline bool RGBColor::operator==(const RGBColor& a_color) const
{
	return (m_r == a_color.m_r && m_g == a_color.m_g && m_b == a_color.m_b);
}

inline double RGBColor::average() const
{
	return (0.333333333333 * (m_r + m_g + m_b));
}

inline RGBColor& RGBColor::operator=(const RGBColor& a_color) {
	if (this == &a_color)
		return (*this);
    
	m_r = a_color.m_r; m_g = a_color.m_g; m_b = a_color.m_b;
    
	return (*this);
}

RGBColor operator*(const double a_k, const RGBColor& a_color);

inline RGBColor operator*(const double a_k, const RGBColor& a_color)
{
	return (RGBColor(a_k * a_color.m_r, a_k * a_color.m_g, a_k * a_color.m_b));
}

#endif /* defined(__RayTracer__RGBColor__) */
