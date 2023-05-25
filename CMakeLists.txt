# CMakeList.txt: OSGlearn 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("OSGlearn")

# 包含头文件目录
include_directories("dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Debug/include")
include_directories("dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Release/include")
include_directories("dependencies/OSG/include")

# 包含库文件目录
link_directories(${PROJECT_NAME} "dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Debug/lib")
link_directories(${PROJECT_NAME} "dependencies/OpenSceneGraph-3.6.5-VC2019-64-Release/lib")

# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME} "source/OSGlearn.cpp" "source/OSGlearn.h")

# 链接库
target_link_libraries(${PROJECT_NAME} debug osgd.lib osgDBd.lib osgViewerd.lib)
#target_link_libraries(${PROJECT_NAME} release osg.lib osgDB.lib osgViewer.lib)#注释说明：提示LINK : fatal error LNK1104: 无法打开文件“release.lib”

# 拷贝DLL文件到可执行文件目录下
file(GLOB OSG_DLLS dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Debug/bin/*dll)
file(COPY ${OSG_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
# 拷贝插件DLL
file(GLOB OSG_PLUGIN_DLL_PNG dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Debug/bin/osgPlugins-*/osgdb_png*.dll)# 拷贝读取.png插件DLL
file(COPY ${OSG_PLUGIN_DLL_PNG} DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB OSG_PLUGIN_DLL_OSG dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Debug/bin/osgPlugins-*/osgdb_osg*.dll)# 拷贝读取.osg插件DLL
file(COPY ${OSG_PLUGIN_DLL_OSG} DESTINATION ${CMAKE_BINARY_DIR})

# TODO: 如有需要，请添加测试并安装目标。
