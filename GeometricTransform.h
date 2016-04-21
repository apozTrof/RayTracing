//
//  GeometricTransform.h
//  RayTracer
//

#ifndef __RayTracer__GeometricTransform__
#define __RayTracer__GeometricTransform__

#include <iostream>

#include "Matrix4x4.h"
#include "Vector.h"
#include "Point.h"
#include "Normal.h"
#include "Ray.h"
#include "BoundingBox.h"

class GeometricTransform {
    
public:
    
    GeometricTransform();
    GeometricTransform(const GeometricTransform& a_gt);
    GeometricTransform(const double a_mat[4][4]);
    GeometricTransform(const Matrix4x4& a_mat);
    GeometricTransform(const Matrix4x4& a_mat, const Matrix4x4& a_inv);
    
    ~GeometricTransform();
    
    bool operator==(const GeometricTransform& a_t) const;
    bool operator!=(const GeometricTransform& a_t) const;
    
    bool isIdentity() const;
    
    const Matrix4x4& getMatrix() const;
    const Matrix4x4& getInverseMatrix() const;
    
    friend GeometricTransform inverse(const GeometricTransform& a_t);
    
    Point operator()(const Point& a_p) const;
    void operator()(const Point& a_p, Point* a_pPimg) const;
    Vector operator()(const Vector& a_v) const;
    void operator()(const Vector& a_v, Vector* a_pVimg) const;
    Normal operator()(const Normal& a_n) const;
    void operator()(const Normal& a_n, Normal* a_pNimg) const;
    Ray operator()(const Ray& a_r) const;
    void operator()(const Ray& a_r, Ray* a_pRimg) const;
    BoundingBox operator()(const BoundingBox& a_b) const;
    GeometricTransform operator*(const GeometricTransform& a_t) const;
    
private:
	void multiply(double& x, double& y, double& z, double& w, const Matrix4x4 mat) const;

    Matrix4x4 m_mat;
    Matrix4x4 m_inv;
};

GeometricTransform translate(const Vector& a_v);
GeometricTransform scale(double a_x, double a_y, double a_z);
GeometricTransform rotateX(double a_t);
GeometricTransform rotateY(double a_t);
GeometricTransform rotateZ(double a_t);
GeometricTransform rotate(double a_t, const Vector& a_d);

inline bool GeometricTransform::operator==(const GeometricTransform& a_t) const
{
    return a_t.m_mat == m_mat && a_t.m_inv == m_inv;
}

inline bool GeometricTransform::operator!=(const GeometricTransform& a_t) const
{
    return a_t.m_mat != m_mat || a_t.m_inv != m_inv;
}

inline bool GeometricTransform::isIdentity() const
{
    return (m_mat.m_mat[0][0] == 1.f && m_mat.m_mat[0][1] == 0.f &&
            m_mat.m_mat[0][2] == 0.f && m_mat.m_mat[0][3] == 0.f &&
            m_mat.m_mat[1][0] == 0.f && m_mat.m_mat[1][1] == 1.f &&
            m_mat.m_mat[1][2] == 0.f && m_mat.m_mat[1][3] == 0.f &&
            m_mat.m_mat[2][0] == 0.f && m_mat.m_mat[2][1] == 0.f &&
            m_mat.m_mat[2][2] == 1.f && m_mat.m_mat[2][3] == 0.f &&
            m_mat.m_mat[3][0] == 0.f && m_mat.m_mat[3][1] == 0.f &&
            m_mat.m_mat[3][2] == 0.f && m_mat.m_mat[3][3] == 1.f);
}

inline const Matrix4x4& GeometricTransform::getMatrix() const
{
    return m_mat;
}

inline const Matrix4x4& GeometricTransform::getInverseMatrix() const
{
    return m_inv;
}

inline Point GeometricTransform::operator()(const Point& a_p) const
{
	Point a_pBuffer = a_p;
	double w = 1.0;
	if (!(this->isIdentity()))
	{
		this->multiply(a_pBuffer.m_x, a_pBuffer.m_y, a_pBuffer.m_z, w, this->m_mat);
	}
	a_pBuffer /= w;

	return a_pBuffer;
}

inline void GeometricTransform::operator()(const Point& a_p, Point* a_pPimg) const
{
	*a_pPimg = (*this)(a_p);
}

inline Vector GeometricTransform::operator()(const Vector& a_v) const
{
	Vector a_vBuffer = a_v;
	double w = 0.0;
	this->multiply(a_vBuffer.m_x, a_vBuffer.m_y, a_vBuffer.m_z, w, this->m_mat);

	return a_vBuffer;
}

inline void GeometricTransform::operator()(const Vector& a_v, Vector* a_pVimg) const
{
	*a_pVimg = (*this)(a_v);
}

inline Normal GeometricTransform::operator()(const Normal& a_n) const
{
	Matrix4x4 m_m = transpose(this->m_inv);
	Normal a_nBuf = a_n;
	double w = 0.0;
	this->multiply(a_nBuf.m_x, a_nBuf.m_y, a_nBuf.m_z, w, m_m);

	return a_nBuf.normalize();
}

inline void GeometricTransform::operator()(const Normal& a_n, Normal* a_pNimg) const
{
	*a_pNimg = (*this)(a_n);
}

inline Ray GeometricTransform::operator()(const Ray& a_r) const
{
	return Ray((*this)(a_r.m_o), (*this)(a_r.m_d));
}

inline void GeometricTransform::operator()(const Ray& a_r, Ray* a_pRimg) const
{
	*a_pRimg = (*this)(a_r);
}

inline void GeometricTransform::multiply(double& x, double& y, double& z, double& w, const Matrix4x4 mat) const {
	double x1 = x;
	double y1 = y;
	double z1 = z;
	double w1 = w;
	x = mat.m_mat[0][0] * x1 + mat.m_mat[0][1] * y1 + mat.m_mat[0][2] * z1 + w1*mat.m_mat[0][3];
	y = mat.m_mat[1][0] * x1 + mat.m_mat[1][1] * y1 + mat.m_mat[1][2] * z1 + w1*mat.m_mat[1][3];
	z = mat.m_mat[2][0] * x1 + mat.m_mat[2][1] * y1 + mat.m_mat[2][2] * z1 + w1*mat.m_mat[2][3];
	w = mat.m_mat[3][0] * x1 + mat.m_mat[3][1] * y1 + mat.m_mat[3][2] * z1 + w1*mat.m_mat[3][3];
}

#endif /* defined(__RayTracer__GeometricTransform__) */
