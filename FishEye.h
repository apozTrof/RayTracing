//
//  FishEye.h
//  RayTracer
//

#ifndef __RayTracer__FishEye__
#define __RayTracer__FishEye__

#include <iostream>

#include "Camera.h"

class FishEye : public Camera {
    
public:
    
    FishEye();
    FishEye(const FishEye& a_fe);
    
    ~FishEye();
    
    FishEye& operator=(const FishEye& a_fe);
    
    void setMaxPsi(double a_psi);
        
    virtual void renderScene(const std::shared_ptr<World> a_pWorld, const std::string& a_filename) const;
    
private:
    
    Vector getRayDirection(const Point& a_p, int a_xRes, int a_yRes, double a_s, double& a_rSquared) const;
    
    double m_maxPsi;
};

inline void FishEye::setMaxPsi(double a_psi)
{
    m_maxPsi = a_psi;
}

#endif /* defined(__RayTracer__FishEye__) */
