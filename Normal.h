//
//  Normal.h
//  RayTracer
//

#ifndef __RayTracer__Normal__
#define __RayTracer__Normal__

#include <iostream>

#include "Vector.h"
#include "Point.h"

class Normal {
    
public:
        
    Normal();
    Normal(double a_k);
    Normal(double a_x, double a_y, double a_z);
    Normal(const Normal& a_n);
    Normal(const Vector& a_v);
    
    ~Normal();
    
    Normal& operator=(const Normal& a_n);
    Normal& operator=(const Vector& a_v);
    Normal& operator=(const Point& a_p);
    Normal operator-() const;
    Normal operator*(double a_k) const;
    Normal operator/(double a_k) const;
    Normal& operator*=(double a_k);
    Normal& operator/=(double a_k);
    Normal operator+(const Normal& a_n) const;
    Normal operator-(const Normal& a_n) const;
    Normal& operator+=(const Normal& a_n);
    Normal& operator-=(const Normal& a_n);
    double operator[](int a_i) const;
    double& operator[](int a_i);
    
    double norm() const;
    double squareNorm() const;
    Normal normalize() const;
        
    double m_x;
    double m_y;
    double m_z;
};

inline Normal Normal::operator-() const
{
    return Normal(-m_x, -m_y, -m_z);
}

inline Normal Normal::operator*(double a_k) const
{
    return Normal(m_x * a_k, m_y * a_k, m_z * a_k);
}

inline Normal Normal::operator/(double a_k) const
{
    assert(a_k != 0.0f);
    
    double inv = 1.0f / a_k;
    
    return Normal(m_x * inv, m_y * inv, m_z * inv);
}

inline Normal& Normal::operator*=(double a_k)
{
    m_x *= a_k;
    m_y *= a_k;
    m_z *= a_k;
    
    return *this;
}

inline Normal& Normal::operator/=(double a_k)
{
    assert(a_k != 0.0f);
    
    double inv = 1.0f / a_k;
    
    m_x *= inv;
    m_y *= inv;
    m_z *= inv;
    
    return *this;
}

inline Normal Normal::operator+(const Normal& a_n) const
{
    return Normal(m_x + a_n.m_x, m_y + a_n.m_y, m_z + a_n.m_z);
}

inline Normal Normal::operator-(const Normal& a_n) const
{
    return Normal(m_x - a_n.m_x, m_y - a_n.m_y, m_z - a_n.m_z);
}

inline Normal& Normal::operator+=(const Normal& a_n)
{
    m_x += a_n.m_x;
    m_y += a_n.m_y;
    m_z += a_n.m_z;
    
    return *this;
}

inline Normal& Normal::operator-=(const Normal& a_n)
{
    m_x -= a_n.m_x;
    m_y -= a_n.m_y;
    m_z -= a_n.m_z;
    
    return *this;
}

inline double Normal::operator[](int i) const
{
    assert(i >= 0 && i <= 2);
    
    return (&m_x)[i];
}

inline double& Normal::operator[](int a_i)
{
    assert(a_i >= 0 && a_i <= 2);
    
    return (&m_x)[a_i];
}

inline double Normal::squareNorm() const
{
    return m_x*m_x + m_y*m_y + m_z*m_z;
}

// Non-member Inline Functions

inline double dot(const Normal& a_n1, const Normal& a_n2)
{
    return a_n1.m_x * a_n2.m_x + a_n1.m_y * a_n2.m_y + a_n1.m_z * a_n2.m_z;
}

inline double absDot(const Normal& a_n1, const Normal& a_n2)
{
    return std::abs(dot(a_n1, a_n2));
}

inline double dot(const Normal& a_n, const Vector& a_v)
{
    return a_n.m_x * a_v.m_x + a_n.m_y * a_v.m_y + a_n.m_z * a_v.m_z;
}

inline double absDot(const Normal& a_n, const Vector& a_v)
{
    return std::abs(dot(a_n, a_v));
}

inline double dot(const Vector& a_v, const Normal& a_n)
{
    return a_v.m_x * a_n.m_x + a_v.m_y * a_n.m_y + a_v.m_z * a_n.m_z;
}

inline double absDot(const Vector& a_v, const Normal& a_n)
{
    return std::abs(dot(a_v, a_n));
}

#endif /* defined(__RayTracer__Normal__) */
