//
//  GeometricTransform.cpp
//  RayTracer
//

#include "GeometricTransform.h"

#include "Matrix4x4.h"

GeometricTransform::GeometricTransform()
{}

GeometricTransform::GeometricTransform(const GeometricTransform& a_gt)
{
    m_mat = a_gt.m_mat;
    m_inv = a_gt.m_inv;
}

GeometricTransform::GeometricTransform(const double a_mat[4][4])
{
    m_mat = Matrix4x4(a_mat);
    m_inv = inverse(m_mat);
}

GeometricTransform::GeometricTransform(const Matrix4x4& a_mat)
:   m_mat(a_mat),
m_inv(inverse(a_mat))
{}

GeometricTransform::GeometricTransform(const Matrix4x4& a_mat, const Matrix4x4& a_inv)
:   m_mat(a_mat),
m_inv(a_inv)
{}

GeometricTransform::~GeometricTransform()
{}

GeometricTransform inverse(const GeometricTransform& a_t)
{
    return GeometricTransform(a_t.m_inv, a_t.m_mat);
}

GeometricTransform translate(const Vector& a_v)
{
    Matrix4x4 mat(1, 0, 0, a_v.m_x,
                  0, 1, 0, a_v.m_y,
                  0, 0, 1, a_v.m_z,
                  0, 0, 0, 1);
    
    Matrix4x4 inv(1, 0, 0, -a_v.m_x,
                  0, 1, 0, -a_v.m_y,
                  0, 0, 1, -a_v.m_z,
                  0, 0, 0, 1);
    
    return GeometricTransform(mat, inv);
}

GeometricTransform scale(double a_x, double a_y, double a_z)
{
    Matrix4x4 mat(a_x, 0, 0, 0,
                  0, a_y, 0, 0,
                  0, 0, a_z, 0,
                  0, 0, 0, 1);
    
    Matrix4x4 inv(1./a_x, 0, 0, 0,
                  0, 1./a_y, 0, 0,
                  0, 0, 1./a_z, 0,
                  0, 0, 0, 1);
    
    return GeometricTransform(mat, inv);
}

GeometricTransform rotateX(double a_t)
{
	Matrix4x4 mat(1, 0, 0, 0,
		0, cos(a_t), -sin(a_t), 0,
		0, sin(a_t), cos(a_t), 0,
		0, 0, 0, 1);

	Matrix4x4 inv = transpose(mat);

	return GeometricTransform(mat, inv);
}

GeometricTransform rotateY(double a_t)
{
	Matrix4x4 mat(cos(a_t), 0, sin(a_t), 0,
		0, 1, 0, 0,
		-sin(a_t), 0, cos(a_t), 0,
		0, 0, 0, 1);

	Matrix4x4 inv = transpose(mat);

	return GeometricTransform(mat, inv);
}

GeometricTransform rotateZ(double a_t)
{
	Matrix4x4 mat(cos(a_t), -sin(a_t), 0, 0,
		sin(a_t), cos(a_t), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	Matrix4x4 inv = transpose(mat);

	return GeometricTransform(mat, inv);
}

GeometricTransform rotate(double a_t, const Vector& a_d)
{
	Vector vectX(1, 0, 0), vectY(0, 1, 0), vectZ(0, 0, 1);
	Vector d = a_d.normalize();

	double a_dNorm = a_d.norm();

	double angleX = dot(vectX, d) / a_dNorm;
	double angleY = dot(vectY, d) / a_dNorm;
	double angleZ = dot(vectZ, d) / a_dNorm;

	Vector vd1 = d*angleX, vd2 = d*angleY, vd3 = d*angleZ;
	Vector v1X = vectX - vd1, v2X = cross(v1X, d);
	Vector v1Y = vectY - vd2, v2Y = cross(v1Y, d);
	Vector v1Z = vectZ - vd3, v2Z = cross(v1Z, d);

	Vector vPrimeX = vd1 + v1X*cos(a_t) + v2X*sin(a_t);
	Vector vPrimeY = vd2 + v1Y*cos(a_t) + v2Y*sin(a_t);
	Vector vPrimeZ = vd3 + v1Z*cos(a_t) + v2Z*sin(a_t);

	Matrix4x4 mat(vPrimeX.m_x, vPrimeY.m_x, vPrimeZ.m_x, 0,
		vPrimeX.m_y, vPrimeY.m_y, vPrimeZ.m_y, 0,
		vPrimeX.m_z, vPrimeY.m_z, vPrimeZ.m_z, 0,
		0, 0, 0, 1);

	Matrix4x4 inv = transpose(mat);

	return GeometricTransform(mat, inv);
}

BoundingBox GeometricTransform::operator()(const BoundingBox& a_b) const
{
	BoundingBox a_bBuffer = a_b;
	
	Point a_pBuffer[8] = {
		Point(a_bBuffer.m_pMin.m_x, a_bBuffer.m_pMin.m_y, a_bBuffer.m_pMin.m_z),
		Point(a_bBuffer.m_pMax.m_x, a_bBuffer.m_pMax.m_y, a_bBuffer.m_pMax.m_z),
		Point(a_bBuffer.m_pMin.m_x, a_bBuffer.m_pMin.m_y, a_bBuffer.m_pMax.m_z),
		Point(a_bBuffer.m_pMin.m_x, a_bBuffer.m_pMax.m_y, a_bBuffer.m_pMax.m_z),
		Point(a_bBuffer.m_pMax.m_x, a_bBuffer.m_pMin.m_y, a_bBuffer.m_pMin.m_z),
		Point(a_bBuffer.m_pMax.m_x, a_bBuffer.m_pMax.m_y, a_bBuffer.m_pMin.m_z),
		Point(a_bBuffer.m_pMax.m_x, a_bBuffer.m_pMin.m_y, a_bBuffer.m_pMax.m_z),
		Point(a_bBuffer.m_pMin.m_x, a_bBuffer.m_pMax.m_y, a_bBuffer.m_pMin.m_z)
	};

	BoundingBox Box = BoundingBox();
	double w = 1.0;

	for each(Point a_p in a_pBuffer) {
		this->multiply(a_p.m_x, a_p.m_y, a_p.m_z, w, this->m_mat);
		Box = combine(Box, a_p);
	}

	return Box;
}

GeometricTransform GeometricTransform::operator*(const GeometricTransform& a_t) const
{
    Matrix4x4 mat = Matrix4x4::mult(m_mat, a_t.m_mat);
    Matrix4x4 inv = Matrix4x4::mult(a_t.m_inv, m_inv);
    
    return GeometricTransform(mat, inv);
}
