#include <osg/BlendColor>
#include <osg/BlendFunc>
#include <osgDB/ReadFile>
#include <CommonLib/Common/Common.h>
namespace FeCommon
{
	void setColor(osg::Node* pNode,osg::Vec4 vecColor)
	{
		osg::StateSet* StateSet = pNode->getOrCreateStateSet();//获取节点状态设置
		osg::ref_ptr<osg::BlendColor> rpBlendColor =new osg::BlendColor();//混合颜色
		osg::ref_ptr<osg::BlendFunc> rpBlendFunc = new osg::BlendFunc();//混合功能
		StateSet->setAttributeAndModes(rpBlendFunc.get(),osg::StateAttribute::PROTECTED | osg::StateAttribute::ON );//添加混合功能属性
		StateSet->setAttributeAndModes(rpBlendColor.get(),osg::StateAttribute::PROTECTED | osg::StateAttribute::ON );//添加混合颜色属性
		rpBlendFunc->setSource(osg::BlendFunc::ONE_MINUS_CONSTANT_COLOR);//一减常量颜色
		rpBlendFunc->setDestination(osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);//一减常量透明度
		osg::Vec4 vecColorNew = osg::Vec4(1.0,1.0,1.0,1.0) - vecColor;
		vecColorNew.a() = vecColor.a();
		rpBlendColor->setConstantColor(vecColorNew);//设置颜色
	}

	osg::Node* readNode(const std::string& strPath)
	{
		osg::ref_ptr<osg::Node> rpNode = osgDB::readNodeFile(strPath);//读取路径所在的模型
		if (rpNode.valid())
		{
			rpNode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL,osg::StateAttribute::ON);//重新设置节点规模后，重置法向量
		}
		return rpNode.release();//release(）释放超级指针并传出节点指针
	}

	osg::Image* readImage( const std::string& strPath )
	{
		osg::ref_ptr<osg::Image> rpImage = osgDB::readImageFile(strPath);
		return rpImage.release();
	}

	bool equalZero( double dValue )
	{
		if( abs(dValue) <= DBL_EPSILON )
		{
			return true;
		}

		return false;
	}

	bool equalZero( float fValue )
	{
		if( abs(fValue) <= FLT_EPSILON )
		{
			return true;
		}

		return false;
	}

	osg::Vec3d DegreesToRadians( const osg::Vec3& vecRotate )
	{
		osg::Vec3 vecRotateNew;
		vecRotateNew.x() = osg::DegreesToRadians(vecRotate.x());
		vecRotateNew.y() = osg::DegreesToRadians(vecRotate.y());
		vecRotateNew.z() = osg::DegreesToRadians(vecRotate.z());
		return vecRotateNew;
	}

	osg::Vec3d RadiansToDegrees( const osg::Vec3& vecRotate )
	{
		osg::Vec3 vecRotateNew;
		vecRotateNew.x() = osg::RadiansToDegrees(vecRotate.x());
		vecRotateNew.y() = osg::RadiansToDegrees(vecRotate.y());
		vecRotateNew.z() = osg::RadiansToDegrees(vecRotate.z());
		return vecRotateNew;
	}

	void Quat2DegreesRotate( const osg::Quat& quat, osg::Vec3& vecRotate )
	{
		Quat2RadiansRotate(quat,vecRotate);
		vecRotate = RadiansToDegrees(vecRotate);
	}

	void Quat2RadiansRotate( const osg::Quat& quat, osg::Vec3& vecRotate )
	{
		double q0 = quat.w();
		double q1 = quat.x();
		double q2 = quat.y();
		double q3 = quat.z();

		vecRotate.x() = float(atan2(2*(q2*q3+q0*q1), (q0*q0-q1*q1-q2*q2+q3*q3)));
		vecRotate.y() = float(asin(-2*(q1*q3-q0*q2)));
		vecRotate.z() = float(atan2(2*(q1*q2+q0*q3), (q0*q0+q1*q1-q2*q2-q3*q3)));
	}

	osg::Matrix DegreesRotate2Matrix( const osg::Vec3d& vecRotate )
	{
		return RadiansRotate2Matrix(DegreesToRadians(vecRotate));
	}

	osg::Matrix RadiansRotate2Matrix( const osg::Vec3d& vecRotate )
	{
		return osg::Matrix::rotate(vecRotate.x(),osg::X_AXIS,vecRotate.y(),osg::Y_AXIS,vecRotate.z(),osg::Z_AXIS);
	}

}