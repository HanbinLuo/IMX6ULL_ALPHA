#include "bsp_clk.h"

/***************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 bsp_clk.c
作者	   : 左忠凯
版本	   : V1.0
描述	   : 系统时钟驱动。
其他	   : 无
论坛 	   : www.wtmembed.com
日志	   : 初版V1.0 2019/1/4 左忠凯创建
***************************************************************/

/*
 * @description	: 使能I.MX6U所有外设时钟
 * @param 		: 无
 * @return 		: 无
 */
void clk_enable(void)
{
	CCM->CCGR0 = 0XFFFFFFFF;
	CCM->CCGR1 = 0XFFFFFFFF;
	CCM->CCGR2 = 0XFFFFFFFF;
	CCM->CCGR3 = 0XFFFFFFFF;
	CCM->CCGR4 = 0XFFFFFFFF;
	CCM->CCGR5 = 0XFFFFFFFF;
	CCM->CCGR6 = 0XFFFFFFFF;
}

void clk_imx6u_init(void)
{
	if (((CCM->CCSR >> 2) & 0x1) == 1)
	{
		CCM->CCSR &= ~(1 << 8);/* 配置 step_clk 时钟源为 24M */
		CCM->CCSR |= (1 << 2); /* 配置 pll1_sw_clk 时钟源为 step_clk */
	}
	//528mhz
	// CCM_ANALOG->PLL_ARM =(1 <<13) |((88<< 0)& 0X7f);
	// CCM->CACRR=1;/*设置2分频*/

	//696mhz
	CCM_ANALOG->PLL_ARM =(1 <<13) |((58<< 0)& 0X7f);
	CCM->CACRR=0;/*设置1分频*/

	CCM->CCSR &=~(1<< 2);/*设置pll1_sW_clk=pll1_main_clk=1056MHz*/
}


