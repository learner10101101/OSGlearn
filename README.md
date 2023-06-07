# 项目说明
  **该项目用于入门学习OSG**

# 项目配置和系统环境变量配置说明
1. 本项目使用配置：VS2019-x64-Debug
2. 系统变量设置
+ OSG_SCREEN：在使用多屏幕时，保证只显示在一个屏幕上
```
变量名：OSG_SCREEN
变量值：0
```
+ OSG_WINDOW：不使用全屏显示，固定窗口尺寸
```
变量名：OSG_WINDOW
变量值：100 100 1000 800
```
+ OSG_FILE_PATH：OSG的数据搜索路径，存在多个data文件，可以通过“;”分隔，一个是自定义的数据路径，另一个是使用OSG的数据包的路径，其余是学习资源中的data文件路径
```
变量名：OSG_FILE_PATH
变量值：xxx/OSGlearn/myData;xxx/OSGlearn/OpenSceneGraph-Data;xxx/OSGlearn/learnSource/OpenSceneGraph三维渲染引擎设计与实践/Examples/data
```
3. [learnSource/OpenSceneGraph三维渲染引擎设计与实践/Examples]使用说明
该Examples是一个cmake工程，构建尝试失败，未进行修改，目前的用法是拷贝Examples代码到OSGlearn.cpp中测试学习

# main函数入口文件OSGlearn.cpp的代码组织
由于测试代码都是独立的main函数，使用编译宏#if进行选择运行，使用VA的“#”方式进行标注不同的main函数和一些注意点
```
//#知识点:标注main函数入口，说明改测试用例学习的知识
//#注意:标注OSG使用上需要注意的点
```

# 常用代码功能，方便拷贝使用
1. 使用Viewer显示节点场景图
```
	osg::ref_ptr<osgViewer::Viewer> rpViewer = new osgViewer::Viewer;
	rpViewer->setSceneData(场景图节点指针);
	rpViewer->addEventHandler(new osgViewer::StatsHandler);
	rpViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	rpViewer->addEventHandler(new osgGA::StateSetManipulator(rpViewer->getCamera()->getOrCreateStateSet()));
	return rpViewer->run();
```
键盘事件：
"s"：[StatsHandler]显示统计信息，有多段
"f"：[WindowSizeHandler]切换“窗口全屏/原尺寸”
"w"：[osgGA::StateSetManipulator]面模型/线框模型/点模型