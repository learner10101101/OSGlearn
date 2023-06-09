
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
#include <osg/Point>
#include <osg/LineWidth>
#include <osg/LineStipple>

#if 0
//#知识点：绘制场景图流程的简单熟悉
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

	viewer->setSceneData(createSceneGraph1());

	return viewer->run();
}
#endif


#if 0
////#知识点：自定义Viewer类的事件处理器
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

#if 0
//#知识点：学习矩阵变换节点的使用：缩放scale，旋转rotate，平移translate（都是osg::Matrix的静态函数）
//osg::ref_ptr<osg::MatrixTransform> rpMTRT = new osg::MatrixTransform;
//rpMTRT->setMatrix(osg::Matrix::scale(10, 10, 10)* osg::Matrix::rotate(osg::DegreesToRadians(90.0), osg::Vec3(0, 0, 1))* osg::Matrix::translate(50, 0, 0));

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

#if 0
//#知识点：学习不同图元的绘制，点（osg::Point）和线（osg::LineWidth）属性对象的使用

int main(int argc, char** argv)
{
	// 创建一个用于保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	// 创建四个顶点的数组
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray(v.get());// 注意，这里v是指针，但是用“.”来使用get()函数返回指针
	v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(-0.5f, 0.f, -1.f));
	v->push_back(osg::Vec3(-0.5f, 0.f, 1.f));
	v->push_back(osg::Vec3(-1.f, 0.f, 1.f));

	v->push_back(osg::Vec3(0.5f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, 1.f));
	v->push_back(osg::Vec3(0.5f, 0.f, 1.f));


	// 创建四种颜色的数组
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));

	// 为唯一的法线创建一个数组
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));

	// 使用DrawArrays方式创建图元
	////POINTS
	//osg::ref_ptr<osg::DrawArrays> drawArrays = new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size());
	////LINES
	//osg::ref_ptr<osg::DrawArrays> drawArrays = new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size());
 	////LINE_STRIP
 	//osg::ref_ptr<osg::DrawArrays> drawArrays = new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, v->size());
	////LINE_LOOP
	//osg::ref_ptr<osg::DrawArrays> drawArrays = new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, v->size());
	////TRIANGLES：使用新的顶点绘制三角形，点数不够绘制出新的三角形，则不进行绘制
	//osg::ref_ptr<osg::DrawArrays> drawArrays = new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, v->size());
	////TRIANGLE_STRIP：三角形带，每次绘制一个三角形舍弃一个顶点，其余顶点循环使用
	//osg::ref_ptr<osg::DrawArrays> drawArrays = new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, v->size());
	////TRIANGLE_FAN：第一个顶点不变，舍弃一个中间顶点，循环使用一个最后顶点
	//osg::ref_ptr<osg::DrawArrays> drawArrays = new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_FAN, 0, v->size());
	//QUADS：
	osg::ref_ptr<osg::DrawArrays> drawArrays = new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, v->size());
	////QUAD_STRIP：两点成线构成矢量，另外两个点构成的矢量方向要与上两点的矢量方向基本一致，否则矩形发送扭曲，类似卷轴对扭的情况
	//osg::ref_ptr<osg::DrawArrays> drawArrays = new osg::DrawArrays(osg::PrimitiveSet::QUAD_STRIP, 0, v->size());
	////POLYGON：(填充与线框模式不符)在OpenGL中，GL_POLYGON图元按照逆时针顺序绘制多边形的顶点。不按照逆时针多边形顶点会影响到[多边形的面向]，[多边形的填充]，[深度测试和遮挡关系]
	//osg::ref_ptr<osg::DrawArrays> drawArrays = new osg::DrawArrays(osg::PrimitiveSet::POLYGON, 0, v->size());
	geom->addPrimitiveSet(drawArrays.get());//图元集决定了如何使用顶点进行绘图，即顶点的组织形式//#注意


	{//设置geom的纹理属性：图元进行贴图//在默认情况下，最终效果是顶点颜色会与纹理混合
		// 创建纹理坐标数组
		osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array;
		//纹理坐标对应第一个矩形
		texCoords->push_back(osg::Vec2(0.0, 0.0));   // 左下角纹理坐标
		texCoords->push_back(osg::Vec2(1.0, 0.0));   // 右下角纹理坐标
		texCoords->push_back(osg::Vec2(1.0, 1.0));   // 右上角纹理坐标
		texCoords->push_back(osg::Vec2(0.0, 1.0));   // 左上角纹理坐标
		//纹理坐标对应第二个矩形
		texCoords->push_back(osg::Vec2(0.0, 0.0));   // 左下角纹理坐标
		texCoords->push_back(osg::Vec2(1.0, 0.0));   // 右下角纹理坐标
		texCoords->push_back(osg::Vec2(1.0, 1.0));   // 右上角纹理坐标
		texCoords->push_back(osg::Vec2(0.0, 1.0));   // 左上角纹理坐标
		geom->setTexCoordArray(0, texCoords.get());//geom设置纹理坐标

		//创建纹理对象
		osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
		osg::ref_ptr<osg::Image> image = osgDB::readImageFile("texture/myTest.jpg");
		texture->setImage(image.get());

		//创建状态集，并将纹理对象设置为当前状态的纹理单元0
		osg::ref_ptr<osg::StateSet> stateSet = geom->getOrCreateStateSet();
		stateSet->setTextureAttributeAndModes(0, texture.get());
	}

	{//设置点和线属性对象，设置点线的尺寸后，将属性对象设置到geom中，在线框模式下线宽由线对象控制（不显示点，不受点对象尺寸影响）；在点集模式下，点的尺寸由点对象控制//#注意
		// 创建点对象并设置属性
		osg::ref_ptr<osg::Point> point = new osg::Point;
		point->setSize(point->getMaxSize());   // 设置点的大小为10像素
		std::cout << "point->getMaxSize() == " << point->getMaxSize() << std::endl;//通过point->getMaxSize()获取点最大直径为100，实际测试为20像素

		// 创建线对象并设置属性
		osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth;
		lineWidth->setWidth(30);   // 设置线的宽度为2像素

		// 将点对象和线对象应用到几何图形节点上的状态集中
		osg::ref_ptr<osg::StateSet> stateSet = geom->getOrCreateStateSet();
		stateSet->setAttributeAndModes(point.get());
		stateSet->setAttributeAndModes(lineWidth.get());
	}
	
	// 向Geode类添加几何体（Drawable）并返回Geode
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());

	osg::ref_ptr<osgViewer::Viewer> rpViewer = new osgViewer::Viewer;
	rpViewer->setSceneData(geode.get());
	rpViewer->addEventHandler(new osgViewer::StatsHandler);
	rpViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	rpViewer->addEventHandler(new osgGA::StateSetManipulator(rpViewer->getCamera()->getOrCreateStateSet()));
	return rpViewer->run();
}
#endif

#if 0
//#知识点：点（osg::Point）和线（osg::LineWidth）属性对象的使用
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Point>
#include <osg/LineWidth>
#include <osg/LineStipple>
#include <osgViewer/Viewer>

int main()
{
	// 创建几何图形节点
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	// 创建顶点数组
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back(osg::Vec3(-1.0, 0.0, 0.0));   // 起点
	vertices->push_back(osg::Vec3(1.0, 0.0, 0.0));    // 终点
	geom->setVertexArray(vertices.get());

	// 创建绘制图元（线段）
	osg::ref_ptr<osg::DrawArrays> drawArraysLines = new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2);
	geom->addPrimitiveSet(drawArraysLines.get());

	// 创建绘制图元（点）//顶点可以被重复使用，可以用来绘制不同的图元，即geom->addPrimitiveSet()可以添加多个DrawArrays对象//#注意
	osg::ref_ptr<osg::DrawArrays> drawArraysPoints = new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, 2);
	geom->addPrimitiveSet(drawArraysPoints.get());

	// 创建点对象并设置属性
	osg::ref_ptr<osg::Point> point = new osg::Point;
	point->setSize(10.0);   // 设置点的大小为10像素

	// 创建线对象并设置属性
	osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth;
	lineWidth->setWidth(2.0);   // 设置线的宽度为2像素

	// 创建线型对象并设置属性
	osg::ref_ptr<osg::LineStipple> lineStipple = new osg::LineStipple;
	lineStipple->setFactor(10);    // 点画线的点间距
	lineStipple->setPattern(0xAAAA);  // 点画线的模式

	// 将点对象,线对象,线型对象应用到几何图形节点上的状态集中
	osg::ref_ptr<osg::StateSet> stateSet = geom->getOrCreateStateSet();
	stateSet->setAttributeAndModes(point.get());
	stateSet->setAttributeAndModes(lineWidth.get());//stateSet->setAttributeAndModes可以添加多个属性对象//知识点
	stateSet->setAttributeAndModes(lineStipple.get());

	// 创建根节点，并将几何图形节点添加到根节点下
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());

	// 创建查看器并设置根节点
	osgViewer::Viewer viewer;
	viewer.setSceneData(geode.get());

	// 运行查看器
	return viewer.run();
}

#endif

#if 0
//#知识点：自定义节点访问器
//重载了osg::Node& node和osg::Geode& node的apply，Geode节点走osg::Geode& node的apply,其余节点走osg::Node& node的apply

/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * Chapter 4: Scene Graph Management
 * a) How to create a node visitor
*/

#include <osg/Node>
#include <osgDB/ReadFile>
#include <iostream>

class InfoVisitor : public osg::NodeVisitor
{
public:
	InfoVisitor()
		: osg::NodeVisitor(TRAVERSE_ALL_CHILDREN), _indent(0) {}

	virtual void apply(osg::Node& node)
	{
		for (int i = 0; i < _indent; ++i) std::cout << "  ";
		std::cout << "[a" << _indent + 1 << "] " << node.libraryName()
			<< "::" << node.className() << std::endl;

		_indent++;
		traverse(node);
		_indent--;
	}

	virtual void apply(osg::Geode& node)
	{
		for (int i = 0; i < _indent; ++i) std::cout << "  ";
		std::cout << "[b" << _indent + 1 << "] " << node.libraryName()
			<< "::" << node.className() << std::endl;

		_indent++;
		traverse(node);
		_indent--;
	}

protected:
	int _indent;
};

int main(int argc, char** argv)
{
	osg::ArgumentParser arguments(&argc, argv);
	osg::Node* root = osgDB::readNodeFiles(arguments);
	if (!root) root = osgDB::readNodeFile("axes.osg");

	InfoVisitor infoVisitor;
	if (root) root->accept(infoVisitor);

	osg::ref_ptr<osgViewer::Viewer> rpViewer = new osgViewer::Viewer;
	rpViewer->setSceneData(root);
	rpViewer->addEventHandler(new osgViewer::StatsHandler);
	rpViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	rpViewer->addEventHandler(new osgGA::StateSetManipulator(rpViewer->getCamera()->getOrCreateStateSet()));
	return rpViewer->run();
}
#endif

#if 0
//#知识点：使用更新回调实现旋转动画

/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to set a node update callback
*/

#include <osg/io_utils>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <iostream>

class RotateCallback : public osg::NodeCallback
{
public:
	RotateCallback() : _rotateZ(0.0) {}

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::PositionAttitudeTransform* pat =
			dynamic_cast<osg::PositionAttitudeTransform*>(node);
		if (pat)
		{
			osg::Quat quat(osg::DegreesToRadians(_rotateZ), osg::Z_AXIS);
			pat->setAttitude(quat);
			_rotateZ += 1.0;
		}
		traverse(node, nv);
	}

protected:
	double _rotateZ;
};

class InfoCallback : public osg::NodeCallback
{
public:
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::PositionAttitudeTransform* pat =
			dynamic_cast<osg::PositionAttitudeTransform*>(node);
		if (pat)
		{
			double angle = 0.0;
			osg::Vec3 axis;
			pat->getAttitude().getRotate(angle, axis);

			std::cout << "Node is rotating around the (" << axis << ") axis, "
				<< osg::RadiansToDegrees(angle) << " degrees" << std::endl;
		}
		traverse(node, nv);
	}
};

int main(int argc, char** argv)
{
	osg::ArgumentParser arguments(&argc, argv);
	osg::Node* model = osgDB::readNodeFiles(arguments);
	if (!model) model = osgDB::readNodeFile("cow.osg");

	osg::ref_ptr<osg::PositionAttitudeTransform> pat =
		new osg::PositionAttitudeTransform;
	pat->addChild(model);

	pat->setUpdateCallback(new RotateCallback);
	pat->addUpdateCallback(new InfoCallback);//这个添加多一个更新回调，不会覆盖上一个回调

	osgViewer::Viewer viewer;
	viewer.setSceneData(pat.get());
	return viewer.run();
}

#endif

#if 0
//#知识点：使用空间变换节点

/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create different transform nodes
*/

#include <osg/AutoTransform>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

osg::Transform* createAutoTransform(double posX, osg::Node* model)
{
	osg::ref_ptr<osg::AutoTransform> at = new osg::AutoTransform;
	at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
	at->setPosition(osg::Vec3(posX, 0.0, 0.0));

	at->addChild(model);
	return at.release();
}

osg::Transform* createMatrixTransform(double posX, double rotateZ, osg::Node* model)
{
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
	mt->setMatrix(osg::Matrix::rotate(rotateZ, osg::Z_AXIS) *
		osg::Matrix::translate(posX, 0.0, 0.0));

	mt->addChild(model);
	return mt.release();
}

osg::Transform* createPositionAttitudeTransform(double posX, double rotateZ, osg::Node* model)
{
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform;
	pat->setPosition(osg::Vec3(posX, 0.0, 0.0));
	pat->setAttitude(osg::Quat(rotateZ, osg::Z_AXIS));

	pat->addChild(model);
	return pat.release();
}

int main(int argc, char** argv)
{
	osg::ArgumentParser arguments(&argc, argv);
	osg::Node* model = osgDB::readNodeFiles(arguments);
	if (!model) model = osgDB::readNodeFile("axes.osg");

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(createMatrixTransform(-5.0, osg::PI / 4, model));
	root->addChild(createAutoTransform(0.0, model));
	root->addChild(createPositionAttitudeTransform(5.0, -osg::PI / 4, model));

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	return viewer.run();
}


#endif

#if 0
//#知识点：使用开关节点

/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a switch node
*/

#include <osg/Switch>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class CessnaCallback : public osg::NodeCallback
{
public:
	static const int _fireStartFrame = 120;

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::Switch* cessnaSwitch = dynamic_cast<osg::Switch*>(node);
		if (cessnaSwitch && nv)
		{
			const osg::FrameStamp* frameStamp = nv->getFrameStamp();
			if (frameStamp)
			{
				if (_fireStartFrame < frameStamp->getFrameNumber())
				{
					cessnaSwitch->setValue(0, false);//开关节点根据子节点索引设置子节点是否显示//#注意
					cessnaSwitch->setValue(1, true);
				}
			}
		}
		traverse(node, nv);
	}
};

int main(int argc, char** argv)
{
	osg::ref_ptr<osg::Switch> root = new osg::Switch;
	root->addChild(osgDB::readNodeFile("cessna.osg"), true);
	root->addChild(osgDB::readNodeFile("cessnafire.osg"), false);
	root->setUpdateCallback(new CessnaCallback);

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.addEventHandler(new osgViewer::StatsHandler);
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	return viewer.run();
}

#endif

#if 0
//#知识点：使用LOD节点
//测试场景：读取三个精细度（即顶点数）不同的模型，在不同的视点与模型距离使用不同的模型，
//近时用精细模型，远时用粗糙模型，减少渲染压力

/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a Level-of-Details node
*/

#include <osg/LOD>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main(int argc, char** argv)
{
	osg::Node* model = osgDB::readNodeFile("bunny-high.ive");
	float r = model->getBound().radius();

	osg::ref_ptr<osg::LOD> root = new osg::LOD;
	root->addChild(osgDB::readNodeFile("bunny-low.ive"), r * 7, FLT_MAX);
	root->addChild(osgDB::readNodeFile("bunny-mid.ive"), r * 3, r * 7);
	root->addChild(model, 0.0, r * 3);

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.addEventHandler(new osgViewer::StatsHandler);
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	return viewer.run();
}

#endif

#if 0
//知识点：使用代理节点
//测试场景：

/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a proxy node
*/

#include <osg/ProxyNode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main(int argc, char** argv)
{
	osg::ArgumentParser arguments(&argc, argv);
	osg::ref_ptr<osg::ProxyNode> root = new osg::ProxyNode;

	unsigned int childrenNo = 0;
	for (int i = 1; i < arguments.argc(); ++i)
	{
		if (arguments.isString(i))
			root->setFileName(childrenNo++, arguments[i]);
	}
	if (!root->getNumFileNames())
		root->setFileName(0, "cow.osg");

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.addEventHandler(new osgViewer::StatsHandler);
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	return viewer.run();
}

#endif


#if 0
//#知识点：构建osg::Geometry对象进行绘制图形
//测试场景：通过创建顶点数组、颜色数组、法线数组和纹理数组，构造一个简单的人字顶房屋

/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a geometric house
*/

#include <osg/Texture2D>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgUtil/SmoothingVisitor>
#include <osgViewer/Viewer>

osg::Drawable* createHouseWall()
{
	// House vertices
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back(osg::Vec3(0.0, 0.0, 4.0));  // 0
	vertices->push_back(osg::Vec3(0.0, 0.0, 0.0));  // 1
	vertices->push_back(osg::Vec3(6.0, 0.0, 4.0));  // 2
	vertices->push_back(osg::Vec3(6.0, 0.0, 0.0));  // 3
	vertices->push_back(osg::Vec3(6.0, 4.0, 4.0));  // 4
	vertices->push_back(osg::Vec3(6.0, 4.0, 0.0));  // 5
	vertices->push_back(osg::Vec3(0.0, 4.0, 4.0));  // 6
	vertices->push_back(osg::Vec3(0.0, 4.0, 0.0));  // 7
	vertices->push_back(osg::Vec3(0.0, 0.0, 4.0));  // 8
	vertices->push_back(osg::Vec3(0.0, 0.0, 0.0));  // 9

	// House normals
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(10);
	(*normals)[0].set(-0.707, -0.707, 0.0);
	(*normals)[1].set(-0.707, -0.707, 0.0);
	(*normals)[2].set(0.707, -0.707, 0.0);
	(*normals)[3].set(0.707, -0.707, 0.0);
	(*normals)[4].set(0.707, 0.707, 0.0);
	(*normals)[5].set(0.707, 0.707, 0.0);
	(*normals)[6].set(-0.707, 0.707, 0.0);
	(*normals)[7].set(-0.707, 0.707, 0.0);
	(*normals)[8].set(-0.707, -0.707, 0.0);
	(*normals)[9].set(-0.707, -0.707, 0.0);

	// House texture coordinates
	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array(10);
	(*texcoords)[0].set(0.0, 1.0);
	(*texcoords)[1].set(0.0, 0.0);
	(*texcoords)[2].set(0.3, 1.0);
	(*texcoords)[3].set(0.3, 0.0);
	(*texcoords)[4].set(0.5, 1.0);
	(*texcoords)[5].set(0.5, 0.0);
	(*texcoords)[6].set(0.8, 1.0);
	(*texcoords)[7].set(0.8, 0.0);
	(*texcoords)[8].set(1.0, 1.0);
	(*texcoords)[9].set(1.0, 0.0);

	// Create wall geometry
	osg::ref_ptr<osg::Geometry> houseWall = new osg::Geometry;
	houseWall->setVertexArray(vertices.get());
	houseWall->setTexCoordArray(0, texcoords.get());
	houseWall->setNormalArray(normals.get());
	houseWall->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	houseWall->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 10));

	houseWall->getOrCreateStateSet()->setTextureAttributeAndModes(0,
		new osg::Texture2D(osgDB::readImageFile("wall.png")));
	return houseWall.release();
}

osg::Drawable* createHouseRoof()
{
	// House vertices
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back(osg::Vec3(-0.2, -0.5, 3.5));  // 0
	vertices->push_back(osg::Vec3(6.2, -0.5, 3.5));  // 1
	vertices->push_back(osg::Vec3(0.8, 2.0, 6.0));  // 2
	vertices->push_back(osg::Vec3(5.2, 2.0, 6.0));  // 3
	vertices->push_back(osg::Vec3(-0.2, 4.5, 3.5));  // 4
	vertices->push_back(osg::Vec3(6.2, 4.5, 3.5));  // 5

	// Roof primitives
	osg::ref_ptr<osg::DrawArrays> roof = new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 6);
	osg::ref_ptr<osg::DrawElementsUInt> roofSide =
		new osg::DrawElementsUInt(osg::DrawElementsUInt::TRIANGLES, 6);
	(*roofSide)[0] = 0; (*roofSide)[1] = 2; (*roofSide)[2] = 4;
	(*roofSide)[3] = 5; (*roofSide)[4] = 3; (*roofSide)[5] = 1;

	// Color
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(0.25, 0.0, 0.0, 1.0));

	// Create roof geometry
	osg::ref_ptr<osg::Geometry> houseRoof = new osg::Geometry;
	houseRoof->setVertexArray(vertices.get());
	houseRoof->setColorArray(colors.get());
	houseRoof->setColorBinding(osg::Geometry::BIND_OVERALL);
	houseRoof->addPrimitiveSet(roof.get());
	houseRoof->addPrimitiveSet(roofSide.get());

	osgUtil::SmoothingVisitor smv;
	smv.smooth(*houseRoof);
	return houseRoof.release();
}

int main(int argc, char** argv)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(createHouseWall());
	geode->addDrawable(createHouseRoof());

	osgViewer::Viewer viewer;
	viewer.setSceneData(geode.get());
	return viewer.run();
}

#endif

#if 1
//#知识点：几何体的更新回调函数的写法，在绘图函数内修改顶点数组
//#测试场景：利用几何体的更新回调函数修改顶点数组，是的线图元进行环状运动

/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to create a dynamic line
*/

#include <osg/LineWidth>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>

class DynamicLineCallback : public osg::Drawable::UpdateCallback
{
public:
	DynamicLineCallback() : _angle(0.0) {}

	virtual void update(osg::NodeVisitor* nv, osg::Drawable* drawable)
	{
		osg::Geometry* geom = dynamic_cast<osg::Geometry*>(drawable);
		if (!geom) return;

		osg::Vec3Array* vertices = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
		if (vertices)
		{
			for (osg::Vec3Array::iterator itr = vertices->begin(); itr != vertices->end() - 1; ++itr)
				itr->set((*(itr + 1)));//修改顶点位置，将最后一个顶点做圆周运动，其它点取代其下一个点的位置，实现跟这最后一个点进行运动的效果

			_angle += 1.0 / 10.0;
			osg::Vec3& pt = vertices->back();
			pt.set(10.0 * cos(_angle), 0.0, 10.0 * sin(_angle));
			vertices->dirty();
		}
	}

protected:
	float _angle;
};

int main(int argc, char** argv)
{
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(10);
	for (unsigned int i = 0; i < 10; ++i)
		(*vertices)[i].set(float(i), 0.0, 0.0);

	osg::ref_ptr<osg::Geometry> lineGeom = new osg::Geometry;
	lineGeom->setVertexArray(vertices.get());
	lineGeom->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_STRIP, 0, 10));

	lineGeom->setInitialBound(osg::BoundingBox(osg::Vec3(-10.0, -10.0, -10.0), osg::Vec3(10.0, 10.0, 10.0)));//节点的boundingbox就是viewer的展示区域，viewer自动对场景节点的boundingbox进行全屏显示
	lineGeom->setUpdateCallback(new DynamicLineCallback);
	lineGeom->setUseDisplayList(false);//显示列表是编译好的程序指令，默认是开启的，顶点数组进行修改时，显示列表无法进行修改，所以需要禁用，在更新回调中，需要启用VBO
	lineGeom->setUseVertexBufferObjects(true);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(2.0));
	geode->addDrawable(lineGeom.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData(geode.get());
	return viewer.run();
}

#endif


