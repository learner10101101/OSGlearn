/**************************************************************************************************
* @file name 文件名:Common.h
* @note 描述：公用函数的归纳
* @author 作者：g00068
* @data 创建时间：2021 -2 -22
**************************************************************************************************/
#ifndef COMMON_H
#define COMMON_H
#include <osg/Node>
#include <osg/Image>
#include <CommonLib/Common/Export.h>
namespace FeCommon
{
	/**
	  * @brief 简要说明：设置模型颜色
	  * @note 详细说明：通过给出模型指针和目标颜色数值，修改模型的显示颜色
	  * @param pNode [in]：目标模型
	  * @param vecColor [in]：目标颜色值
	  * @return 返回值以及说明：
	*/
	COMMON_EXPORT void setColor(osg::Node* pNode,osg::Vec4 vecColor);

	/**
	  * @brief 简要说明：读取模型
	  * @note 详细说明：根据路径，读取模型
	  * @param strPath [in]：路径信息，要求绝对路径
	  * @return ：模型指针
	*/
	COMMON_EXPORT osg::Node* readNode(const std::string& strPath);
	
	/**
	  * @brief 简要说明：读取图片
	  * @note 详细说明：根据路径，读取图片
	  * @param strPath [in]：路径信息，要求绝对路径
	  * @return ：图片指针
	*/
	COMMON_EXPORT osg::Image* readImage(const std::string& strPath);
		
	/**
	  * @brief 简要说明：判断double类型值是否为0
	  * @note 详细说明：根据传入值，进行区间判断，在特定区间内的指，视为0值
	  * @param dValue [in]：传入的判断值
	  * @return ：是否为0
	*/
	COMMON_EXPORT bool equalZero( double dValue );
		
	/**
	  * @brief 简要说明：判断float类型值是否为0
	  * @note 详细说明：根据传入值，进行区间判断，在特定区间内的指，视为0值
	  * @param fValue [in]：传入的判断值
	  * @return ：是否为0
	*/
	COMMON_EXPORT bool equalZero( float fValue );

	/**
	*@note: 度转弧度
	*/
	COMMON_EXPORT osg::Vec3d DegreesToRadians(const osg::Vec3& vecRotate);
	
	/**
	*@note: 弧度转度
	*/
	COMMON_EXPORT osg::Vec3d RadiansToDegrees(const osg::Vec3& vecRotate);

	/**
	*@note: 四元数转度欧拉角
	*/
	COMMON_EXPORT void Quat2DegreesRotate( const osg::Quat& quat, osg::Vec3& vecRotate );
	
	/**
	*@note: 四元数转弧度欧拉角
	*/
	COMMON_EXPORT void Quat2RadiansRotate( const osg::Quat& quat, osg::Vec3& vecRotate );

	/**
	*@note: 度欧拉角转旋转矩阵
	*/
	COMMON_EXPORT osg::Matrix DegreesRotate2Matrix( const osg::Vec3d& vecRotate);
	
	/**
	*@note: 弧度欧拉角转旋转矩阵
	*/
	COMMON_EXPORT osg::Matrix RadiansRotate2Matrix( const osg::Vec3d& vecRotate);

}
#endif COMMON_H