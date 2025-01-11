#include "stm32f10x.h"                  // Device header
#include "VEE.h"
#include "SWITCH.h"

/** 针脚：--
  * 函    数：
  * 参    数：无
  * 返 回 值：无
  */

uint32_t Sn(uint8_t sn) //各开关对应电阻
{
	switch (sn)
	{
		case 1 :
		{
			return 2;
		}
		case 2 :
		{
			return 47;
		}
		case 3 :
		{
			return 510;
		}
		case 4 :
		{
			return 1800;
		}
		case 5 :
		{
			return 10000;
		}
		case 6 :
		{
			return 330000;
		}
		case 7 :
		{
			return 750000;
		}
		case 8 :
		{
			return 3900000;
		}
		default :
		{
			return 0;
		}
	}
}

void Switch_Set(uint8_t sn)
{
	switch (sn)
	{
		case 1 :
		{
			VEESet(1, 0, 0, 0); //开关切换至S1
			break;
		}
		case 2 :
		{
			VEESet(1, 1, 0, 0); //开关切换至S2
			break;
		}
		case 3 :
		{
			VEESet(1, 0, 1, 0); //开关切换至S3
			break;
		}
		case 4 :
		{
			VEESet(1, 1, 1, 0); //开关切换至S4
			break;
		}
		case 5 :
		{
			VEESet(1, 0, 0, 1); //开关切换至S5
			break;
		}
		case 6 :
		{
			VEESet(1, 1, 0, 1); //开关切换至S6
			break;
		}
		case 7 :
		{
			VEESet(1, 0, 1, 1); //开关切换至S7
			break;
		}
		case 8 :
		{
			VEESet(1, 1, 1, 1); //开关切换至S8
			break;
		}
		default :
		{
			VEESet(0, 0, 0, 0);
		}
	}
}

