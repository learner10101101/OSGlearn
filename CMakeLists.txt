# CMakeList.txt: OSGlearn 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("OSGlearn")

set(TARGET ${PROJECT_NAME})
set(TARGET_BIN_OUTPT_PATH "out_bin")
set(TARGET_BIN_OUTPT_PATH_DEBUG "out_bin/Debug")#vs工程中，编译结果在TARGET_BIN_OUTPT_PATH下，会创建一个配置信息文件夹，在里面输出程序结果文件
set(TARGET_LIB_OUTPT_PATH "out_lib")

# 设置文件在VS项目中的映射，并通过文件变量在add_executable中进行链接（非库文件的使用方式，一般是类文件或者函数文件）
file(GLOB COMMON "common/*.h" "common/*.cpp")
source_group("common" FILES ${COMMON})

# 包含头文件目录
include_directories("dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Debug/include")
include_directories("dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Release/include")
include_directories("dependencies/OSG/include")
include_directories("common")

# 包含库文件目录
link_directories(${PROJECT_NAME} "dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Debug/lib")
link_directories(${PROJECT_NAME} "dependencies/OpenSceneGraph-3.6.5-VC2019-64-Release/lib")

# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME} "source/OSGlearn.cpp" "source/OSGlearn.h" ${COMMON})

#设置项目属性
set_target_properties(${TARGET} PROPERTIES VERSION 1.1.0.0)#设置版本信息
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TARGET_BIN_OUTPT_PATH}")#设置bin,exe的输出路径
set_target_properties(${TARGET} PROPERTIES ARCHIVE_OUTPUT_DERECTORY "${TARGET_LIB_OUTPT_PATH}")#设置lib的输出路径
#set_target_properties(${TARGET} PROPERTIES OUT_NAME &{TARGET_OUTPUT_NAME})#设置项目编译结果文件的名
#set_target_properties(${TARGET} PROPERTIES FOLDER "XXX/XXX")#设置项目在IDE工程中的目录结构

# 链接库
target_link_libraries(${PROJECT_NAME} debug osgd.lib osgDBd.lib osgViewerd.lib osgGAd.lib osgManipulatord.lib osgUtild.lib osgTextd.dll)
#target_link_libraries(${PROJECT_NAME} release osg.lib osgDB.lib osgViewer.lib)#注释说明：提示LINK : fatal error LNK1104: 无法打开文件“release.lib”

# 拷贝DLL文件到可执行文件目录下
file(GLOB OSG_DLLS dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Debug/bin/*dll)
file(COPY ${OSG_DLLS} DESTINATION ${TARGET_BIN_OUTPT_PATH_DEBUG})
# 拷贝所有插件DLL
file(GLOB OSG_PLUGIN_DLLs dependencies/OSG/OpenSceneGraph-3.6.5-VC2019-64-Debug/bin/osgPlugins-*/osgdb_*.dll)
file(COPY ${OSG_PLUGIN_DLLs} DESTINATION ${TARGET_BIN_OUTPT_PATH_DEBUG})


# TODO: 如有需要，请添加测试并安装目标。
