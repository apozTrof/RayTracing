//
//  UniformSampler.cpp
//  RayTracer
//

#include "UniformSampler.h"

UniformSampler::UniformSampler()
:   Sampler()
{}

UniformSampler::UniformSampler(int a_nbSamples)
:   Sampler(a_nbSamples)
{
    generateSamples();
}

UniformSampler::UniformSampler(int a_nbSamples, int a_nbSets)
:   Sampler(a_nbSamples, a_nbSets)
{
    generateSamples();
}

UniformSampler::UniformSampler(const UniformSampler& a_us)
:   Sampler(a_us)
{
    generateSamples();
}

UniformSampler::~UniformSampler()
{}

void UniformSampler::generateSamples()
{
    int n = (int) sqrt(m_nbSamples);
    
    for (int s = 0; s < m_nbSets; ++s)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                m_samples.push_back(Point((i+0.5)/n, (j+0.5)/n, 0));
            }
        }
    }
}