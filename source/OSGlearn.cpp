
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
#define DAY  3

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
//学习矩阵变换节点的使用：缩放scale，旋转rotate，平移translate（都是osg::Matrix的静态函数）
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

#if DAY == 3
//学习不同图元的绘制
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
	geom->addPrimitiveSet(drawArrays.get());


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
		osg::ref_ptr<osg::Image> image = osgDB::readImageFile("C:/Users/袁壮/Desktop/测试/myTest.jpg");
		texture->setImage(image.get());

		//创建状态集，并将纹理对象设置为当前状态的纹理单元0
		osg::ref_ptr<osg::StateSet> stateSet = geom->getOrCreateStateSet();
		stateSet->setTextureAttributeAndModes(0, texture.get());
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