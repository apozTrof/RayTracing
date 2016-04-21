//
//  Alexandre Guertin 10 143 908
//  Antoine Vella 12 035 861
//
//  RandomSampler.cpp
//  RayTracer
//

#include <stdlib.h>
#include <time.h>

#include "RandomSampler.h"

RandomSampler::RandomSampler()
:   Sampler()
{}

RandomSampler::RandomSampler(int a_nbSamples)
:   Sampler(a_nbSamples)
{
    generateSamples();
}

RandomSampler::RandomSampler(int a_nbSambles, int a_nbSets)
:   Sampler(a_nbSambles, a_nbSets)
{
    generateSamples();
}

RandomSampler::RandomSampler(const RandomSampler& a_rs)
:   Sampler(a_rs)
{
    generateSamples();
}

RandomSampler::~RandomSampler()
{}

void RandomSampler::generateSamples()
{
	for (int i = 0; i < m_nbSets; ++i)
	{
		for (int j = 0; j < m_nbSamples; ++j)
		{
			m_samples.push_back(Point((double)rand() / ((double)RAND_MAX), (double)rand() / ((double)RAND_MAX), 0));
		}
	}
}
