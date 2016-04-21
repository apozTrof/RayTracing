//
//  Alexandre Guertin 10 143 908
//  Antoine Vella 12 035 861
//  World.cpp
//  RayTracer
//

#define _USE_MATH_DEFINES

#include <ctime>
#include <vector>
#include <memory>

#include "CImg.h"

using namespace cimg_library;

#include "World.h"
#include "Cylinder.h"
#include "MultipleObjects.h"
#include "MultipleObjectsNormals.h"
#include "RayCast.h"
#include "Whitted.h"
#include "GeometricTransform.h"
#include "Sphere.h"
#include "GridAccelerator.h"
#include "PointLight.h"
#include "Sampler.h"
#include "UniformSampler.h"
#include "RandomSampler.h"
#include "StratifiedSampler.h"
#include "Camera.h"
#include "Cone.h"
#include "Pinhole.h"
#include "Orthographic.h"
#include "ThinLens.h"
#include "FishEye.h"
#include "Material.h"
#include "Matte.h"
#include "Phong.h"
#include "Mirror.h"
#include "MatteT.h"
#include "ConstantTexture.h"
#include "ImageTexture.h"
#include "Checkerboard3D.h"
#include "Checkerboard2D.h"

World::World()
:   m_backgroundColor(RGBColor(0)),
m_pTracer(nullptr),
m_pCamera(nullptr)
{}

World::~World()
{}

void World::build()
{
    m_vp.setXRes(1000);
    m_vp.setYRes(500);
    m_vp.setPixelSize(1);
    m_vp.setGamma(1.0);
    
    std::shared_ptr<StratifiedSampler> vpSampler(new StratifiedSampler(9));
    m_vp.setSampler(vpSampler);
    
	std::shared_ptr<Orthographic> camera(new Orthographic());
    camera->setCenter(Point(0, 0, 500));
    camera->setLookAt(Point(0, 0, -50));
    camera->setViewPlaneDistance(400);
    camera->buildCCS();
    setCamera(camera);
    
    m_backgroundColor = RGBColor(0.0);
    m_pTracer = std::shared_ptr<Whitted>(new Whitted(shared_from_this()));
    
	std::vector<std::shared_ptr<GeometricObject>> objects;

	std::shared_ptr<Checkerboard3D> text1(new Checkerboard3D());
	text1->setSize(50);
	std::shared_ptr<MatteT> matteT1(new MatteT());
	matteT1->setKd(1.0);
	matteT1->setCd(text1);

	std::shared_ptr<GeometricTransform>
		o2w1(new GeometricTransform(translate(Vector(250, 0, 0))*rotateY(15 * M_PI / 16)*rotateX(0)));
	std::shared_ptr<GeometricTransform>
		w2o1(new GeometricTransform(inverse(*o2w1)));

	std::shared_ptr<Sphere> sp1(new Sphere(o2w1, w2o1, 200));
	sp1->setMaterial(matteT1);
	objects.push_back(sp1);

	std::shared_ptr<Mirror> mirror1(new Mirror());
	mirror1->setCd(RGBColor(0.0, 0.0, 1.0));
	mirror1->setKd(1);
	mirror1->setExponent(50);
	mirror1->setKs(1);
	mirror1->setCr(RGBColor(1.0));
	mirror1->setKr(1);

	std::shared_ptr<GeometricTransform>
		o2w2(new GeometricTransform(translate(Vector(-250, 0, 0))));
	std::shared_ptr<GeometricTransform>
		w2o2(new GeometricTransform(inverse(*o2w2)));

	std::shared_ptr<Sphere> sp2(new Sphere(o2w2, w2o2, 200));
	sp2->setMaterial(mirror1);
	objects.push_back(sp2);

	std::shared_ptr<GridAccelerator> accel(new GridAccelerator(objects));
	addObject(accel);

	PointLight l1(1, RGBColor(1, 1, 1), Point(400, 400, 300));
	addLight(std::make_shared<PointLight>(l1));

	PointLight l2(1, RGBColor(1, 1, 1), Point(400, -400, 300));
	addLight(std::make_shared<PointLight>(l2));

	PointLight l3(1, RGBColor(1, 1, 1), Point(-400, 400, 300));
	addLight(std::make_shared<PointLight>(l3));

	PointLight l4(1, RGBColor(1, 1, 1), Point(-400, -400, 300));
	addLight(std::make_shared<PointLight>(l4));

	PointLight l5(1, RGBColor(1), Point(0, 0, 300));
	addLight(std::make_shared<PointLight>(l5));
}
