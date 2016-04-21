//
//  Matrix4x4.cpp
//  RayTracer
//

#include <cmath>

#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
    m_mat[0][0] = 1.0; m_mat[0][1] = 0.0; m_mat[0][2] = 0.0; m_mat[0][3] = 0.0;
    m_mat[1][0] = 0.0; m_mat[1][1] = 1.0; m_mat[1][2] = 0.0; m_mat[1][3] = 0.0;
    m_mat[2][0] = 0.0; m_mat[2][1] = 0.0; m_mat[2][2] = 1.0; m_mat[2][3] = 0.0;
    m_mat[3][0] = 0.0; m_mat[3][1] = 0.0; m_mat[3][2] = 0.0; m_mat[3][3] = 1.0;
}

Matrix4x4::Matrix4x4(const double a_mat[4][4])
{
    memcpy(m_mat, a_mat, 16*sizeof(double));
}

Matrix4x4::Matrix4x4(double a_t00, double a_t01, double a_t02, double a_t03,
                     double a_t10, double a_t11, double a_t12, double a_t13,
                     double a_t20, double a_t21, double a_t22, double a_t23,
                     double a_t30, double a_t31, double a_t32, double a_t33)
{
    m_mat[0][0] = a_t00; m_mat[0][1] = a_t01; m_mat[0][2] = a_t02; m_mat[0][3] = a_t03;
    m_mat[1][0] = a_t10; m_mat[1][1] = a_t11; m_mat[1][2] = a_t12; m_mat[1][3] = a_t13;
    m_mat[2][0] = a_t20; m_mat[2][1] = a_t21; m_mat[2][2] = a_t22; m_mat[2][3] = a_t23;
    m_mat[3][0] = a_t30; m_mat[3][1] = a_t31; m_mat[3][2] = a_t32; m_mat[3][3] = a_t33;
}

Matrix4x4::~Matrix4x4()
{}

bool Matrix4x4::operator==(const Matrix4x4& a_m) const
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (m_mat[i][j] != a_m.m_mat[i][j])
            {
                return false;
            }
        }
    }
    
    return true;
}

bool Matrix4x4::operator!=(const Matrix4x4& a_m) const
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (m_mat[i][j] != a_m.m_mat[i][j])
            {
                return true;
            }
        }
    }
    
    return false;
}

// Non-member Functions

Matrix4x4 mul(const Matrix4x4& a_m1, const Matrix4x4& a_m2)
{
    Matrix4x4 result;
    
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result.m_mat[i][j] = a_m1.m_mat[i][0] * a_m2.m_mat[0][j] +
                                 a_m1.m_mat[i][1] * a_m2.m_mat[1][j] +
                                 a_m1.m_mat[i][2] * a_m2.m_mat[2][j] +
                                 a_m1.m_mat[i][3] * a_m2.m_mat[3][j];
        }
    }
    
    return result;
}

Matrix4x4 transpose(const Matrix4x4& a_m)
{
    return Matrix4x4(a_m.m_mat[0][0], a_m.m_mat[1][0], a_m.m_mat[2][0], a_m.m_mat[3][0],
                     a_m.m_mat[0][1], a_m.m_mat[1][1], a_m.m_mat[2][1], a_m.m_mat[3][1],
                     a_m.m_mat[0][2], a_m.m_mat[1][2], a_m.m_mat[2][2], a_m.m_mat[3][2],
                     a_m.m_mat[0][3], a_m.m_mat[1][3], a_m.m_mat[2][3], a_m.m_mat[3][3]);
}

Matrix4x4 inverse(const Matrix4x4& a_m)
{
    int indxc[4];
    int indxr[4];
    int ipiv[4] = { 0, 0, 0, 0 };
    double minv[4][4];
    memcpy(minv, a_m.m_mat, 4*4*sizeof(double));
    
    for (int i = 0; i < 4; i++)
    {
        int irow = -1;
        int icol = -1;
        
        double big = 0.0;
        
        // Choose pivot
        for (int j = 0; j < 4; j++)
        {
            if (ipiv[j] != 1)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (ipiv[k] == 0)
                    {
                        if (fabsf(minv[j][k]) >= big)
                        {
                            big = double(fabs(minv[j][k]));
                            irow = j;
                            icol = k;
                        }
                    }
                    else if (ipiv[k] > 1)
                        std::cerr << "Singular matrix in inverse(const Matrix4x4& a_m)";
                }
            }
        }
        ++ipiv[icol];
        
        // Swap rows _irow_ and _icol_ for pivot
        if (irow != icol)
        {
            for (int k = 0; k < 4; ++k)
            {
                std::swap(minv[irow][k], minv[icol][k]);
            }
        }
        indxr[i] = irow;
        indxc[i] = icol;
        
        if (minv[icol][icol] == 0.0)
            std::cerr << "Singular matrix in inverse(const Matrix4x4& a_m)";
        
        
        // Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
        double pivinv = 1.0 / minv[icol][icol];
        minv[icol][icol] = 1.0;
        for (int j = 0; j < 4; j++)
        {
            minv[icol][j] *= pivinv;
        }
        
        // Subtract this row from others to zero out their columns
        for (int j = 0; j < 4; j++)
        {
            if (j != icol)
            {
                double save = minv[j][icol];
                minv[j][icol] = 0;
                for (int k = 0; k < 4; k++)
                {
                    minv[j][k] -= minv[icol][k]*save;
                }
            }
        }
    }
    
    // Swap columns to reflect permutation
    for (int j = 3; j >= 0; j--)
    {
        if (indxr[j] != indxc[j])
        {
            for (int k = 0; k < 4; k++)
            {
                std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
            }
        }
    }
    return Matrix4x4(minv);
}

Matrix4x4 Matrix4x4::mult(const Matrix4x4& a_m1, const Matrix4x4& a_m2)
{
    Matrix4x4 ret;
    
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            ret.m_mat[i][j] = a_m1.m_mat[i][0] * a_m2.m_mat[0][j] +
                              a_m1.m_mat[i][1] * a_m2.m_mat[1][j] +
                              a_m1.m_mat[i][2] * a_m2.m_mat[2][j] +
                              a_m1.m_mat[i][3] * a_m2.m_mat[3][j];
        }
    }
    
    return ret;
}