//
//  Matrix4x4.h
//  RayTracer
//

#ifndef __RayTracer__Matrix4x4__
#define __RayTracer__Matrix4x4__

#include <iostream>

struct Matrix4x4 {
    
    // Matrix4x4 Public Methods
    
    Matrix4x4();
    Matrix4x4(const double a_mat[4][4]);
    Matrix4x4(double a_t00, double a_t01, double a_t02, double a_t03,
              double a_t10, double a_t11, double a_t12, double a_t13,
              double a_t20, double a_t21, double a_t22, double a_t23,
              double a_t30, double a_t31, double a_t32, double a_t33);
    
    ~Matrix4x4();
    
    bool operator==(const Matrix4x4& a_mat) const;
    bool operator!=(const Matrix4x4& a_mat) const;
    
    friend Matrix4x4 transpose(const Matrix4x4& a_m);
    friend Matrix4x4 inverse(const Matrix4x4& a_m);
    
    static Matrix4x4 mult(const Matrix4x4& a_m1, const Matrix4x4& a_m2);
    
    // Matrix4x4 Public Data
    
    double m_mat[4][4];
};

#endif /* defined(__RayTracer__Matrix4x4__) */
