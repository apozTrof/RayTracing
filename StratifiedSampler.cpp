//
//  Alexandre Guertin 10 143 908
//  Antoine Vella 12 035 861
//
//  StratifiedSampler.cpp
//  RayTracer
//
#include "StratifiedSampler.h"

StratifiedSampler::StratifiedSampler()
:   Sampler()
{}

StratifiedSampler::StratifiedSampler(int a_nbSamples)
:   Sampler(a_nbSamples)
{
    generateSamples();
}

StratifiedSampler::StratifiedSampler(int a_nbSambles, int a_nbSets)
:   Sampler(a_nbSambles, a_nbSets)
{
    generateSamples();
}

StratifiedSampler::StratifiedSampler(const StratifiedSampler& a_ss)
:   Sampler(a_ss)
{
    generateSamples();
}

StratifiedSampler::~StratifiedSampler()
{}

void StratifiedSampler::generateSamples()
{
	int sSamples = (int)sqrt(m_nbSamples);
	for (int i = 0; i < m_nbSets; ++i)
	{
		for (int j = 0; j < sSamples; ++j)
		{
			
			for (int k = 0; k < sSamples; ++k)
			{
				m_samples.push_back(Point((j + (double)rand() / ((double)RAND_MAX)) / sSamples, (k + (double)rand() / ((double)RAND_MAX)) / sSamples, 0));
			}
		}
	}
}