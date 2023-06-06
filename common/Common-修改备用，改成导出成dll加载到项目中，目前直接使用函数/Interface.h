#ifndef COMMON_H
#define COMMON_H

namespace BaseInterFace{
	/**
	  * @brief 简要说明：事件通信时用到的结构体
	*/
	struct SEvent
	{
		SEvent()
		{
			bState = false;
		}
		bool bState;//显隐状态
	};
}

#endif COMMON_H