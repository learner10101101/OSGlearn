// OSGlearn.cpp: 定义应用程序的入口点。
//

#include "OSGlearn.h"
#include<iostream>
#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/Geometry>
#include <osg/ref_ptr>
#include <osgDB/Registry>
#include <osgDB/WriteFile>
#include <osg/Notify>

// 绘制地球
osg::ref_ptr<osg::Node> createSceneGraph1()
{
	// 创建球体
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), 1.0f)));

	// 给球体添加纹理
	osg::ref_ptr<osg::Texture> texture = new osg::Texture2D(osgDB::readRefImageFile("texture/world.png"));//需要设置OSG的文件搜索路径
	auto stateSet = geode->getOrCreateStateSet();
	stateSet->setTextureAttributeAndModes(0, texture);

	return geode;
}

// 通过设置Geometry进行绘图：指定了一个单一四边形图元的几何信息。这个四边形的每个顶点颜色不同，整个几何图元的法线只有一个。
osg::ref_ptr<osg::Node> createSceneGraph2()
{
	// 创建一个用于保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	// 创建四个顶点的数组
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray(v.get());// 注意，这里v是指针，但是用“.”来使用get()函数返回指针
	v->push_back(osg::Vec3(-1.f,0.f,-1.f));
	v->push_back(osg::Vec3(1.f,0.f,-1.f));
	v->push_back(osg::Vec3(1.f,0.f,1.f));
	v->push_back(osg::Vec3(-1.f,0.f,1.f));

	// 创建四种颜色的数组
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c->push_back(osg::Vec4(1.f,0.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f,1.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f,0.f, 1.f, 1.f));
	c->push_back(osg::Vec4(1.f,1.f, 1.f, 1.f));

	// 为唯一的法线创建一个数组
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(0.f,-1.f,0.f));

	// 由保存的数据绘制四个顶点的多边形
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

	// 向Geode类添加几何体（Drawable）并返回Geode
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->setUpViewInWindow(50,50,800,600);

	viewer->setSceneData(createSceneGraph2());

	//return viewer->run();

	osg::ref_ptr<osg::Node> root = createSceneGraph2();
	if (!root.valid())
	{
		osg::notify(osg::FATAL) << "Failed in createSceneGraph()." << std::endl;
	}

	bool result = osgDB::writeNodeFile(*(root.get()),"Simple.osg");

	if (!result)
	{
		osg::notify(osg::FATAL) << "Failed in osgDB::writeNode()." << std::endl;
	}

	//return 0;
	return viewer->run();
}
