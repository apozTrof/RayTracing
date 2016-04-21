//
//  Alexandre Guertin 10 143 908
//  Antoine Vella 12 035 861
//
//  Sampler.cpp
//  RayTracer
//

#define _USE_MATH_DEFINES

#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <limits>

#include "Sampler.h"

Sampler::Sampler()
:   m_nbSamples(1),
    m_nbSets(83),
    m_count(0),
    m_jump(0)
{
    m_samples.reserve(m_nbSamples*m_nbSets);
    setupShuffledIndices();
}

Sampler::Sampler(int a_nbSamples)
:   m_nbSamples(a_nbSamples),
    m_nbSets(83),
    m_count(0),
    m_jump(0)
{
    m_samples.reserve(m_nbSamples*m_nbSets);
    setupShuffledIndices();
}

Sampler::Sampler(int a_nbSambles, int a_nbSets)
:   m_nbSamples(a_nbSambles),
    m_nbSets(a_nbSets),
    m_count(0),
    m_jump(0)
{
    m_samples.reserve(m_nbSamples*m_nbSets);
    setupShuffledIndices();
}

Sampler::Sampler(const Sampler& a_s)
:   m_nbSamples(a_s.m_nbSamples),
    m_nbSets(a_s.m_nbSets),
    m_samples(a_s.m_samples),
    m_shuffledIndices(a_s.m_shuffledIndices),
    m_circleSamples(a_s.m_circleSamples),
    m_hemisphereSamples(a_s.m_hemisphereSamples),
    m_count(a_s.m_count),
    m_jump(a_s.m_jump)
{}

Sampler::~Sampler()
{}

Sampler& Sampler::operator=(const Sampler& a_s)
{
    if (this == &a_s)
    {
        return *this;
    }
    
    m_nbSamples = a_s.m_nbSamples;
    m_nbSets = a_s.m_nbSets;
    m_samples = a_s.m_samples;
    m_shuffledIndices = a_s.m_shuffledIndices;
    m_circleSamples = a_s.m_circleSamples;
    m_hemisphereSamples = a_s.m_hemisphereSamples;
    m_count = a_s.m_count;
    m_jump = a_s.m_jump;
    
    return *this;
}

void Sampler::setNbSets(int a_nbSets)
{
    m_nbSets = a_nbSets;
}

Point Sampler::sampleUnitSquare()
{
    if (m_count % m_nbSamples == 0)
    {
        srand((unsigned)time(0));
        m_jump = (rand() % m_nbSets) * m_nbSamples;
    }
    
    return m_samples[m_jump + m_shuffledIndices[int(m_jump + m_count++ % m_nbSamples)]];
}

Point Sampler::sampleUnitCircle()
{
    if (m_count % m_nbSamples == 0)
    {
        srand((unsigned)time(0));
        m_jump = (rand() % m_nbSets) * m_nbSamples;
    }
    
    return m_circleSamples[m_jump + m_shuffledIndices[m_jump + m_count++ % m_nbSamples]];
}

Point Sampler::sampleUnitHemisphere()
{
    if (m_count % m_nbSamples == 0)
    {
        srand((unsigned)time(0));
        m_jump = (rand() % m_nbSets) * m_nbSamples;
    }
    
    return m_hemisphereSamples[m_jump + m_shuffledIndices[m_jump + m_count++ % m_nbSamples]];
}

void Sampler::mapSquare2Circle()
{
	double x, y;
	for (std::vector<Point>::iterator it = m_samples.begin(); it != m_samples.end(); it++)
	{
		x = it->m_x * 2.0 - 1.0;
		y = it->m_y * 2.0 - 1.0;
		
		if (x > y && x < -y)
		{
			if (y == 0.0)
				m_circleSamples.push_back(Point(0, 0, 0));
			else
				m_circleSamples.push_back(Point(-y*cos(M_PI_4*(6 - (x / y))), -y*sin(M_PI_4*(6 - (x / y))), 0));
		}
		else if (x <= y && x <= -y)
		{
			if (x == 0.0)
				m_circleSamples.push_back(Point(0, 0, 0));
			else
				m_circleSamples.push_back(Point(-x*cos(M_PI_4*(4 + (y / x))), -x*sin(M_PI_4*(4 + (y / x))), 0));
		}
		else if (x < y && x > -y)
		{
			if (y == 0.0)
				m_circleSamples.push_back(Point(0, 0, 0));
			else
				m_circleSamples.push_back(Point(y*cos(M_PI_4*(2 - (x / y))), y*sin(M_PI_4*(2 - (x / y))), 0));
		}
		else if (x >= y && x >= -y)
		{
			if (x == 0.0)
				m_circleSamples.push_back(Point(0, 0, 0));
			else
				m_circleSamples.push_back(Point(x*cos(M_PI_4*(y / x)), x*sin(M_PI_4*(y / x)), 0));
		}

		m_circleSamples.back().m_x = m_circleSamples.back().m_x / 2.0 + 0.5;
		m_circleSamples.back().m_y = m_circleSamples.back().m_y / 2.0 + 0.5;
	}
}

void Sampler::mapSquare2Hemisphere(double a_alpha)
{
	for (std::vector<Point>::iterator it = m_samples.begin(); it != m_samples.end(); ++it)
	{
		double theta = acos(pow((1.0 - it->m_y), 1.0 / (a_alpha + 1.0)));
		double phi = M_PI* 2.0 * it->m_x;
		m_hemisphereSamples.push_back(Point(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta)));
	}
}

void Sampler::setupShuffledIndices()
{
    m_shuffledIndices.reserve(m_nbSamples*m_nbSets);
    std::vector<int> indices;
    
    for (int i = 0; i < m_nbSamples; ++i)
    {
        indices.push_back(i);
    }
    
    for (int j = 0; j < m_nbSets; ++j)
    {
        random_shuffle(indices.begin(), indices.end());
        
        for (int i = 0; i < m_nbSamples; ++i)
        {
            m_shuffledIndices.push_back(indices[i]);
        }
    }
}