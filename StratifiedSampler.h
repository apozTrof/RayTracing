//
//  StratifiedSampler.h
//  RayTracer
//

#ifndef __RayTracer__StratifiedSampler__
#define __RayTracer__StratifiedSampler__

#include <iostream>

#include "Sampler.h"

class StratifiedSampler : public Sampler {
    
public:
    
    StratifiedSampler();
    StratifiedSampler(int a_nbSamples);
    StratifiedSampler(int a_nbSambles, int a_nbSets);
    StratifiedSampler(const StratifiedSampler& a_ss);
    
    ~StratifiedSampler();
    
private:
    
    virtual void generateSamples();
};

#endif /* defined(__RayTracer__StratifiedSampler__) */
