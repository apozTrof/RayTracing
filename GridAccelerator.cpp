//
//  Alexandre Guertin 10 143 908
//  Antoine Vella 12 035 861
//
//  GridAccelerator.cpp
//  RayTracer
//

#include <cmath>

#include "GridAccelerator.h"
#include "Vector.h"

GridAccelerator::GridAccelerator(const std::vector<std::shared_ptr<GeometricObject>>& a_obj)
{
	for (int i = 0; i < a_obj.size(); ++i)
	{
		if (((std::shared_ptr<GeometricObject>)a_obj[i])->intersect())
		{
			m_objects.push_back(a_obj[i]);
			m_bb = combine(m_bb, a_obj[i]->worldBound());
		}
		else
		{
			((std::shared_ptr<GeometricObject>)a_obj[i])->refine(m_objects);
		}
	}

	double a_cellX = std::abs(m_bb.m_pMax.m_x - m_bb.m_pMin.m_x);
	double a_cellY = std::abs(m_bb.m_pMax.m_y - m_bb.m_pMin.m_y);
	double a_cellZ = std::abs(m_bb.m_pMax.m_z - m_bb.m_pMin.m_z);

	double a_nCells = 3 * (std::pow(m_objects.size(), 1.0 / 3.0));

	if (a_cellX > a_cellY)
	{
		if (a_cellX > a_cellZ)
		{
			m_nCells[0] = a_nCells;
			m_cellWidth[0] = a_cellX / m_nCells[0];
			m_invCellWidth[0] = 1.0 / m_cellWidth[0];

			m_nCells[1] = std::max(1.0, a_cellY / m_cellWidth[0]);
			m_cellWidth[1] = a_cellY / m_nCells[1];
			m_invCellWidth[1] = 1.0 / m_cellWidth[1];

			m_nCells[2] = std::max(1.0, a_cellZ / m_cellWidth[0]);
			m_cellWidth[2] = a_cellY / m_nCells[2];
			m_invCellWidth[2] = 1.0 / m_cellWidth[2];
		}
		else
		{
			m_nCells[2] = a_nCells;
			m_cellWidth[2] = a_cellX / m_nCells[2];
			m_invCellWidth[2] = 1.0 / m_cellWidth[2];

			m_nCells[1] = std::max(1.0, a_cellY / m_cellWidth[2]);
			m_cellWidth[1] = a_cellY / m_nCells[1];
			m_invCellWidth[1] = 1.0 / m_cellWidth[1];

			m_nCells[0] = std::max(1.0, a_cellZ / m_cellWidth[2]);
			m_cellWidth[0] = a_cellY / m_nCells[0];
			m_invCellWidth[0] = 1.0 / m_cellWidth[0];
		}
		
	}
	else
	{
		if (a_cellY > a_cellZ)
		{
			m_nCells[1] = a_nCells;
			m_cellWidth[1] = a_cellX / m_nCells[1];
			m_invCellWidth[1] = 1.0 / m_cellWidth[1];

			m_nCells[0] = std::max(1.0, a_cellY / m_cellWidth[1]);
			m_cellWidth[0] = a_cellY / m_nCells[0];
			m_invCellWidth[0] = 1.0 / m_cellWidth[0];

			m_nCells[2] = std::max(1.0, a_cellZ / m_cellWidth[1]);
			m_cellWidth[2] = a_cellY / m_nCells[2];
			m_invCellWidth[2] = 1.0 / m_cellWidth[2];
		}
		else
		{
			m_nCells[2] = a_nCells;
			m_cellWidth[2] = a_cellX / m_nCells[2];
			m_invCellWidth[2] = 1.0 / m_cellWidth[2];

			m_nCells[1] = std::max(1.0, a_cellY / m_cellWidth[2]);
			m_cellWidth[1] = a_cellY / m_nCells[1];
			m_invCellWidth[1] = 1.0 / m_cellWidth[1];

			m_nCells[0] = std::max(1.0, a_cellZ / m_cellWidth[2]);
			m_cellWidth[0] = a_cellY / m_nCells[0];
			m_invCellWidth[0] = 1.0 / m_cellWidth[0];
		}
	}

	m_cells = std::vector<Cell>(m_nCells[0] * m_nCells[1] * m_nCells[2]);

	int a_minX, a_minY, a_minZ, a_maxX, a_maxY, a_maxZ;

	for (int i = 0; i < m_objects.size(); ++i)
	{
		BoundingBox a_bb = m_objects[i]->worldBound();

		a_minX = spaceToCell(a_bb.m_pMin.m_x, 0);
		a_minY = spaceToCell(a_bb.m_pMin.m_y, 1);
		a_minZ = spaceToCell(a_bb.m_pMin.m_z, 2);
		
		a_maxX = spaceToCell(a_bb.m_pMax.m_x, 0);
		a_maxY = spaceToCell(a_bb.m_pMax.m_y, 1);
		a_maxZ = spaceToCell(a_bb.m_pMax.m_z, 2);

		for (int j = a_minZ; j <= a_maxZ; ++j)
		{
			for (int k = a_minY; k <= a_maxY; ++k)
			{
				for (int l = a_minX; l <= a_maxX; ++l)
				{
					m_cells[l + (k * m_nCells[0]) + (j * m_nCells[0] * m_nCells[1])].addObject(m_objects[i]);
				}
			}
		}
	}
}

GridAccelerator::~GridAccelerator()
{}

BoundingBox GridAccelerator::objectBound() const
{
    return m_bb;
}

BoundingBox GridAccelerator::worldBound() const
{
    return m_bb;
}

bool GridAccelerator::intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const
{
	double a_entry, a_exit;

	if (!m_bb.intersect(a_ray, a_entry, a_exit))
	{
		return false;
	}
	
	a_entry = (a_entry > a_ray.m_mint) ? a_entry : a_ray.m_mint;

	Point a_pIntersect = a_ray(a_entry);

	double a_loc[3], a_out[3], a_step[3], a_nextCelT[3], a_dist[3];
	for (int i = 0; i < 3; ++i)
	{
		a_loc[i] = spaceToCell(a_pIntersect, i);

		if (a_ray.m_d[i] < 0)
		{
			a_nextCelT[i] = ((cellToSpace(a_loc[i] - 1, i) - a_pIntersect[i]) / a_ray.m_d[i]);
			a_dist[i] = (-m_cellWidth[i]) / a_ray.m_d[i];
			a_step[i] = -1;
			a_out[i] = -1;
		}
		else
		{
			a_nextCelT[i] = (a_ray.m_d[i]>0) ? ((cellToSpace(a_loc[i] + 1, i) - a_pIntersect[i]) / a_ray.m_d[i]) : INT_MAX;
			a_dist[i] = (a_ray.m_d[i] > 0) ? ((m_cellWidth[i]) / a_ray.m_d[i]) : INT_MAX;
			a_step[i] = 1;
			a_out[i] = m_nCells[i];
		}
	}

	double a_minimalStep = DBL_MAX;
	int a_chx = 0;

	while (true)
	{
		Cell a_cell = m_cells[a_loc[0] + a_loc[1] * m_nCells[0] + a_loc[2] * m_nCells[0] * m_nCells[1]];

		if (a_cell.intersect(a_ray, a_t, a_inter))
		{
			return true;
		}

		a_minimalStep = DBL_MAX;

		for (int i = 0; i < 3; ++i)
		{
			if (a_nextCelT[i] < a_minimalStep)
			{
				a_minimalStep = a_nextCelT[i];
				a_chx = i;
			}
		}

		a_loc[a_chx] += a_step[a_chx];
		a_nextCelT[a_chx] += a_dist[a_chx];

		if ((a_loc[a_chx] == a_out[a_chx]) || (a_nextCelT[a_chx] > a_ray.m_maxt))
		{
			return false;
		}	
	}

	return false;
}

int GridAccelerator::spaceToCell(const Point &a_p, int a_axis) const
{
    int v = static_cast<int>((a_p[a_axis] - m_bb.m_pMin[a_axis]) * m_invCellWidth[a_axis]);
    
    return std::max(0, std::min(v, m_nCells[a_axis]-1));
}

double GridAccelerator::cellToSpace(int a_p, int a_axis) const
{
    return m_bb.m_pMin[a_axis] + a_p*m_cellWidth[a_axis];
}
