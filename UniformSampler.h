//
//  UniformSampler.h
//  RayTracer
//

#ifndef __RayTracer__UniformSampler__
#define __RayTracer__UniformSampler__

#include <iostream>

#include "Sampler.h"

class UniformSampler : public Sampler {
    
public:
    
    UniformSampler();
    UniformSampler(int a_nbSamples);
    UniformSampler(int a_nbSamples, int a_nbSets);
    UniformSampler(const UniformSampler& a_us);
    
    ~UniformSampler();
    
private:
    
    virtual void generateSamples();
};

#endif /* defined(__RayTracer__UniformSampler__) */
