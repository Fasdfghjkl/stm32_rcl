#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "AD.h"
#include "SWITCH.h"

long Zx_Cal(float ad2, float ad3, uint8_t sn) //阻抗值返回
{
	return (long)(ad2 / ad3 * Sn(sn));
}

long Zx_GetValue(void)
{
	uint16_t ad2[5], ad3[5], val[5];
	uint8_t s = 3, i;
	float mad2 = AD_GetValue(ADC_Channel_2), mad3 = AD_GetValue(ADC_Channel_3);
	float mval = mad2 / mad3;
	
	Delay_ms(20);
	if (mval >= 5.6)
	{
		for (i = 0; s <= 8; i++)
		{
			ad2[i] = AD_GetValue(ADC_Channel_2);
			ad3[i] = AD_GetValue(ADC_Channel_3);
			val[i] = mval;
			s++;
			Switch_Set(s);
			if (mval <= 1.0)
			{
				break;
			}
			Delay_ms(20);
		}
		if (mval == 1.0)
		{
			return Zx_Cal(ad2[i], ad3[i], s);
		}
		else
		{
			if (val[i - 1] - 1.0 > 1.0 - val[i])
			{
				return Zx_Cal(ad2[i], ad3[i], s);
			}
			else
			{
				return Zx_Cal(ad2[i - 1], ad3[i - 1], s);
			}
		}
	}
	else if (mval <= 5.6)
	{
		for (i = 0; s >= 1; i++)
		{
			ad2[i] = AD_GetValue(ADC_Channel_2);
			ad3[i] = AD_GetValue(ADC_Channel_3);
			val[i] = mval;
			s--;
			Switch_Set(s);
			if (mval >= 1.0)
			{
				break;
			}
			Delay_ms(20);
		}
		if (mval == 1.0)
		{
			return Zx_Cal(ad2[i], ad3[i], s);
		}
		else
		{
			if (1.0 - val[i - 1] > val[i] - 1.0)
			{
				return Zx_Cal(ad2[i], ad3[i], s);
			}
			else
			{
				return Zx_Cal(ad2[i - 1], ad3[i - 1], s);
			}
		}
	}
	else
	{
		return Zx_Cal(mad2, mad3, s);
	}
}

float Xxang_GetValue(void)
{
	float cc1 = TIM_GetCapture1(TIM3), cc2 = TIM_GetCapture2(TIM3);
	return 180.0 * (2.0 * ((cc2 + 1.0) * 100.0 / (cc1 + 1.0)) - 1.0);
}
