#include "stm32f10x.h"                  // Device header

/** 针脚：GPIOA, GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 | GPIO_Pin_11
  * 函    数：VEE初始化
  * 参    数：无
  * 返 回 值：无
  */
void VEE_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//将PA8 9 10 11引脚初始化为开漏输出
	
	/*设置GPIO初始化后的默认电平*/
	GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 | GPIO_Pin_11);				//设置PA8 9 10 11引脚为低电平
}

/**
  * 函    数：VEE1开启
  * 参    数：无
  * 返 回 值：无
  */
void VEE1_ON(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);		//设置PA8引脚为高电平
}

/**
  * 函    数：VEE1关闭
  * 参    数：无
  * 返 回 值：无
  */
void VEE1_OFF(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);		//设置PA8引脚为低电平
}

/**
  * 函    数：VEE1状态翻转
  * 参    数：无
  * 返 回 值：无
  */
void VEE1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);					//则设置PA8引脚为高电平
	}
	else													//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);					//则设置PA8引脚为低电平
	}
}

void VEE2_ON(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_9);		//设置PA9引脚为高电平
}

/**
  * 函    数：VEE2关闭
  * 参    数：无
  * 返 回 值：无
  */
void VEE2_OFF(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_9);		//设置PA9引脚为低电平
}

/**
  * 函    数：VEE2状态翻转
  * 参    数：无
  * 返 回 值：无
  */
void VEE2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_9) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_9);					//则设置PA9引脚为高电平
	}
	else													//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_9);					//则设置PA9引脚为低电平
	}
}

void VEE3_ON(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_10);		//设置PA10引脚为高电平
}

/**
  * 函    数：VEE3关闭
  * 参    数：无
  * 返 回 值：无
  */
void VEE3_OFF(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_10);		//设置PA10引脚为低电平
}

/**
  * 函    数：VEE3状态翻转
  * 参    数：无
  * 返 回 值：无
  */
void VEE3_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_10) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_10);					//则设置PA10引脚为高电平
	}
	else													//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_10);					//则设置PA10引脚为低电平
	}
}

void VEE4_ON(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_11);		//设置PA11引脚为高电平
}

/**
  * 函    数：VEE4关闭
  * 参    数：无
  * 返 回 值：无
  */
void VEE4_OFF(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);		//设置PA11引脚为低电平
}

/**
  * 函    数：VEE4状态翻转
  * 参    数：无
  * 返 回 值：无
  */
void VEE4_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_11);					//则设置PA11引脚为高电平
	}
	else													//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_11);					//则设置PA11引脚为低电平
	}
}

void VEESet(uint8_t VEE1, uint8_t VEE2, uint8_t VEE3, uint8_t VEE4)
{
	if (VEE1)
	{
		VEE1_ON();
	}
	if (!VEE1)
	{
		VEE1_OFF();
	}
	if (VEE2)
	{
		VEE2_ON();
	}
	if (!VEE2)
	{
		VEE2_OFF();
	}
	if (VEE3)
	{
		VEE3_ON();
	}
	if (!VEE3)
	{
		VEE3_OFF();
	}
	if (VEE4)
	{
		VEE4_ON();
	}
	if (!VEE4)
	{
		VEE4_OFF();
	}
}
