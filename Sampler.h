//
//  Sampler.h
//  RayTracer
//

#ifndef __RayTracer__Sampler__
#define __RayTracer__Sampler__

#include <iostream>
#include <vector>

#include "Point.h"

class Sampler {
    
public:
    
    Sampler();
    Sampler(int a_nbSamples);
    Sampler(int a_nbSambles, int a_nbSets);
    Sampler(const Sampler& a_s);
    
    virtual ~Sampler();
    
    Sampler& operator=(const Sampler& a_s);
    
    void setNbSets(int a_nbSets);
    int getNbSamples() const;
    
    Point sampleUnitSquare();
    Point sampleUnitCircle();
    Point sampleUnitHemisphere();
    
    void mapSquare2Circle();
    void mapSquare2Hemisphere(double a_alpha);
    
private:
    
    virtual void generateSamples() = 0;
    void setupShuffledIndices();
    
protected:
    
    int m_nbSamples;
    int m_nbSets;
    std::vector<Point> m_samples;
    std::vector<int> m_shuffledIndices;
    std::vector<Point> m_circleSamples;
    std::vector<Point> m_hemisphereSamples;
    unsigned long m_count;
    int m_jump;
};

inline int Sampler::getNbSamples() const
{
    return m_nbSamples;
}

#endif /* defined(__RayTracer__Sampler__) */
