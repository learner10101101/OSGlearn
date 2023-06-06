
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
#include <osg/Material>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osg/MatrixTransform>
#include <common.h>

//b站《2021版OSG教学》课程源码学习
#define DAY  2

#if 0 //自定义学习
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

// 扩展createSceneGraph2的场景，添加指定数量的矩形图形
osg::ref_ptr<osg::Node> createSceneGraph3()
{
	// 创建Geode对象
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	// 创建Geometry对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	// Geode对象引用Geometry对象
	geode->addDrawable(geom.get());

	// 创建顶点数组
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray(v.get());// 注意，这里v是指针，但是用“.”来使用get()函数返回指针

		// 创建顶点颜色
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	int32_t num = 100;
	int32_t graphNum = num * num;
	float visualLen = 1.0 / num;
	float offsize = 0.1 * visualLen;
	float realLen = visualLen - 2 * offsize;

	for (int32_t row = 0; row < num; ++row)
	{
		for (int32_t col = 0; col < num; ++col)
		{
			osg::Vec3 leftTopPoint = osg::Vec3(col*visualLen+offsize,0.f,row*visualLen+offsize);
			osg::Vec3 rightTopPoint = osg::Vec3(leftTopPoint.x()+realLen,0.f,leftTopPoint.z());
			osg::Vec3 rightBottomPoint = osg::Vec3(leftTopPoint.x()+realLen,0.f,leftTopPoint.z()+realLen);
			osg::Vec3 leftBottomPoint = osg::Vec3(leftTopPoint.x(),0.f,leftTopPoint.z()+realLen);
		
			v->push_back(leftTopPoint);
			v->push_back(rightTopPoint);
			v->push_back(rightBottomPoint);
			v->push_back(leftBottomPoint);

			c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
			c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
			c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
			c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));
		}
	}

	// 为唯一的法线创建一个数组
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));

	// 由保存的数据绘制四个顶点的多边形
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4 * graphNum));

	return geode.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	//viewer->setUpViewInWindow(50,50,800,600);

	viewer->setSceneData(createSceneGraph3());

	return viewer->run();
}
#endif


#if DAY == 1
//自定义Viewer类的事件处理器
//重写函数：bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override
//const osgGA::GUIEventAdapter& ea: 获取鼠标键盘事件
//const osgGA::GUIActionAdapter& aa : Viewer的操作器，通过aa.asView()获取关联的Viewer指针，实现对Viewer的修改
class ToggleWireframeEventHandler : public osgGA::GUIEventHandler
{
public:
	ToggleWireframeEventHandler() {}

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override
	{
		if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN && ea.getKey() == 'q')
		{
			osg::StateSet* stateSet = aa.asView()->getCamera()->getOrCreateStateSet();
			osg::PolygonMode* polygonMode = dynamic_cast<osg::PolygonMode*>(stateSet->getAttribute(osg::StateAttribute::POLYGONMODE));
			if (polygonMode)
			{
				if (polygonMode->getMode(osg::PolygonMode::FRONT_AND_BACK) == osg::PolygonMode::FILL)
					polygonMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
				else
					polygonMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);
			}
			else
			{
				polygonMode = new osg::PolygonMode;
				polygonMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
				stateSet->setAttributeAndModes(polygonMode, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
			}

			return true; // 停止事件传递
		}

		return false; // 继续事件传递
	}
};

int main(int argc, char** argv)
{
	int nType = 0;
	while (nType < 4)
	{
		std::cout << "选择显示场景:" << std::endl;
		std::cout << "1.最简场景" << std::endl;
		std::cout << "2.显示模型" << std::endl;
		std::cout << "3.键盘事件" << std::endl;
		std::cout << "4.退出" << std::endl;
		std::cin >> nType;
		osg::ref_ptr<osgViewer::Viewer> rpViewer = new osgViewer::Viewer;
		if (nType == 2 || nType == 3)
		{
			osg::ref_ptr<osg::Node> rpCow = osgDB::readNodeFile("cow.osg");
			rpViewer->setSceneData(rpCow.get());
		}
		if (nType == 3)
		{
			rpViewer->addEventHandler(new osgViewer::StatsHandler);
			rpViewer->addEventHandler(new osgViewer::WindowSizeHandler);
			rpViewer->addEventHandler(new osgGA::StateSetManipulator(rpViewer->getCamera()->getOrCreateStateSet()));
			rpViewer->addEventHandler(new ToggleWireframeEventHandler);//自定义事件处理器，通过“q”切换面模型和线框模型
		}
		if (nType < 4)
		{
			rpViewer->run();
		}
	}
	return 0;
}
#endif

#if DAY == 2
int main(int argc, char** argv)
{
	osg::ref_ptr<osgViewer::Viewer> rpViewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> rpGroup = new osg::Group;
	osg::ref_ptr<osg::Node> rpCow = FeCommon::readNode("cow.osg");
	rpGroup->addChild(rpCow.get());
	{
		osg::ref_ptr<osg::MatrixTransform> rpMT = new osg::MatrixTransform;
		rpMT->setMatrix(osg::Matrix::translate(0, 0, 10));
		rpMT->addChild(rpCow.get());
		FeCommon::setColor(rpMT.get(), osg::Vec4(1.0, 0.0, 0.0, 1.0));
		rpGroup->addChild(rpMT.get());
	}
	{
		//矩阵旋转关键函数为osg::Matrix::rotate，并且根据重载的方法，入参也各不相同
		//实例中为：绕（0，0，1）轴，旋转90.0角度，即绕z轴旋转90.0角度

		//矩阵平移osg::Matrix::translate
		//osg::Matrix::translate(10,0,0)，即按照x轴正方向平移10个单位
		osg::ref_ptr<osg::MatrixTransform> rpMTRT = new osg::MatrixTransform;
		rpMTRT->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(90.0), osg::Vec3(0, 0, 1)) * osg::Matrix::translate(10, 0, 0));
		rpMTRT->addChild(rpCow.get());
		FeCommon::setColor(rpMTRT.get(), osg::Vec4(0.0, 1.0, 0.0, 1.0));
		rpGroup->addChild(rpMTRT.get());
		osg::ref_ptr<osg::MatrixTransform> rpMTTR = new osg::MatrixTransform;
		rpMTTR->setMatrix(osg::Matrix::translate(10, 0, 0) * osg::Matrix::rotate(osg::DegreesToRadians(90.0), osg::Vec3(0, 0, 1)));
		rpMTTR->addChild(rpCow.get());
		FeCommon::setColor(rpMTTR.get(), osg::Vec4(0.0, 0.0, 1.0, 1.0));
		rpGroup->addChild(rpMTTR.get());
	}
	{
		//矩阵缩放，osg::Matrix::scale
		//osg::Matrix::scale(10,10,10)，按照x，y，z三个轴方向放大10倍
		osg::ref_ptr<osg::MatrixTransform> rpMTRT = new osg::MatrixTransform;
		rpGroup->addChild(rpMTRT.get());
		rpMTRT->addChild(rpCow.get());
		rpMTRT->setMatrix(osg::Matrix::scale(10, 10, 10) * osg::Matrix::rotate(osg::DegreesToRadians(90.0), osg::Vec3(0, 0, 1)) * osg::Matrix::translate(50, 0, 0));
		FeCommon::setColor(rpMTRT.get(), osg::Vec4(1.0, 1.0, 0.0, 1.0));

	}
	rpViewer->setSceneData(rpGroup.get());
	rpViewer->addEventHandler(new osgViewer::StatsHandler);
	rpViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	rpViewer->addEventHandler(new osgGA::StateSetManipulator(rpViewer->getCamera()->getOrCreateStateSet()));
	return rpViewer->run();
}
#endif

#if DAY == 3
#endif