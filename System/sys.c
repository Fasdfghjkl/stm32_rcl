#include "sys.h"

/** 参考：https://blog.csdn.net/weixin_61203118/article/details/125942936
  *https://blog.csdn.net/qq_39400113/article/details/111699315
  */
//void WFI_SET(void)
//{
//	__ASM volatile("wfi");		  
//}

////关闭所有中断
//void INTX_DISABLE(void)
//{		  
//	__ASM volatile("cpsid i");
//}

////开启所有中断
//void INTX_ENABLE(void)
//{
//	__ASM volatile("cpsie i");		  
//}

////设置栈顶地址
////addr:栈顶地址
//__asm void MSR_MSP(u32 addr) 
//{
//    MSR_MSP, r0 			//set Main Stack value
//    BX r14
//}
