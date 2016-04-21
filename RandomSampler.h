//
//  RandomSampler.h
//  RayTracer
//

#ifndef __RayTracer__RandomSampler__
#define __RayTracer__RandomSampler__

#include <iostream>

#include "Sampler.h"

class RandomSampler : public Sampler {
    
public:
    
    RandomSampler();
    RandomSampler(int a_nbSamples);
    RandomSampler(int a_nbSambles, int a_nbSets);
    RandomSampler(const RandomSampler& a_rs);
    
    ~RandomSampler();
    
private:
    
    virtual void generateSamples();
};

#endif /* defined(__RayTracer__RandomSampler__) */
