#include "stm32f10x.h"                  // Device header
#include "math.h"
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "VEE.h"
#include "KEY.h"
#include "IC.h"
#include "ZX.h"
#include "SWITCH.h"
#include "AD9833.h"

#define PI 3.14159265
#define FRE10 10000
#define FRE100 100000

void OLED_ShowMode(uint8_t mode);
void OLED_Select(uint8_t type);
void Mode_R(void);
void Mode_C(void);
void Mode_L(void);

long z, x, c, l;

int main(void)
{
	/*模块初始化*/
	OLED_Init();
	IC_Init();
	AD_Init();
	VEE_Init();
	KEY_Init();
	
	AD9833_AmpSet(50);

	/*主程序*/
	if (AD_GetValue(ADC_Channel_1) >= 4000)
	{
		//自动测量
		uint8_t i;
		long j[2];
		
		start:
		OLED_ShowMode(1);
		
		while (1)
		{
			if (KEY_GetNum() == 1)
			{
				OLED_ShowMode(2);
				for (i = 0; i <= 1; i++)
				{
					AD9833_WaveSeting(FRE10 * pow(10, i), 0, SIN_WAVE, 0);
					j[i] = Zx_GetValue();
				}
				OLED_ShowMode(3);
				while (1)
				{
					if (j[0] - j[1] >= 0.5) //判断为电容
					{
						Mode_C();
					}
					else if (j[1] - j[0] >= 1.4) //判断为电感
					{
						Mode_L();
					}
					else //电阻
					{
						Mode_R();
					}
					if (KEY_GetNum() == 1)
					{
						goto start;
					}
				}
			}
		}
	}
	else
	{
		//手动测量
		uint8_t type = 1;
		
		OLED_ShowMode(4);
		
		while (1)
		{
			if (KEY_GetNum() == 1)
			{
				type++;
			}
			if (type == 4)
			{
				type = 1; //按键值循环
			}
			//电阻
			if (type == 1)
			{
				Mode_R();
			}
			//电容
			if (type == 2)
			{
				Mode_C();
			}
			//电感
			if (type == 3)
			{
				Mode_L();
			}
		}
	}
}

void OLED_ShowMode(uint8_t mode)
{
	if (mode == 1) //自动测量开始前
	{
		OLED_Clear();
		OLED_ShowString(1, 1, "Auto detect mode");
		OLED_ShowString(2, 2, "Press to start");
		OLED_ShowString(3, 1, "Note: Please ");
		OLED_ShowString(4, 1, "connect firstly");
	}
	if (mode == 2) //自动测量时
	{
		OLED_Clear();
		OLED_ShowString(2, 3, "Working...");
	}
	if (mode == 3) //自动测量显示
	{
		OLED_Clear();
		OLED_ShowString(1, 1, "Type:");
		OLED_ShowString(2, 1, "Val:");
		OLED_ShowString(3, 1, "unit:");
		OLED_ShowString(4, 1, "Press to reload");
	}
	if (mode == 4) //手动测量
	{
		OLED_Clear();
		OLED_ShowString(1, 1, "Type:");
		OLED_ShowString(2, 1, "Val:");
		OLED_ShowString(3, 1, "unit:");
		OLED_ShowString(4, 1, "Press to select");
	}
}

void OLED_Select(uint8_t type)
{
	if (type == 1)
	{
		OLED_ShowChar(1, 7, 'R');
		OLED_ShowString(3, 7, "ohm");
	}
	if (type == 2)
	{
		OLED_ShowChar(1, 7, 'C');
		OLED_ShowString(3, 7, "nF ");
	}
	if (type == 3)
	{
		OLED_ShowChar(1, 7, 'L');
		OLED_ShowString(3, 7, "uH ");
	}
}

void Mode_R(void)
{
	OLED_Select(1);
	AD9833_WaveSeting(FRE10, 0, SIN_WAVE, 0);
	Switch_Set(4); //默认为S4挡位
	z =  Zx_GetValue();
	OLED_ShowNum(2, 6, z, 8);
}

void Mode_C(void)
{
	OLED_Select(2);
	AD9833_WaveSeting(FRE100, 0, SIN_WAVE, 0);
	Switch_Set(3); //默认为S3挡位
	z = Zx_GetValue();
	x = PI * (2 * Xxang_GetValue() - 1);
	c = 15910 / x;
	OLED_ShowNum(2, 6, c, 8);
}

void Mode_L(void)
{
	OLED_Select(3);
	AD9833_WaveSeting(FRE100, 0, SIN_WAVE, 0);
	Switch_Set(2); //默认为S2挡位
	z = Zx_GetValue();
	x = PI * (2 * Xxang_GetValue() - 1);
	l = x * 1.59;
	OLED_ShowNum(2, 6, l, 8);
}
