#include "BSP_Allout.h"
GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t CCR1_Val = 0x02FF;
uint16_t CCR2_Val = 0x0258;
uint16_t CCR3_Val = 0x0190;
uint16_t CCR4_Val = 0x00ff;
uint16_t CCR5_Val = 0x0008;
uint16_t PrescalerValue = 0;
/**
  * @brief  initializes LED.面板指示灯MCU引脚配置
  * @param  None
  * @retval None
  */
void BSP_Allouts_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Configure the GPIO pin */
	/************************************************PWM的PIN脚设置***************************************************/
	/* GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_8); */
	/************************************************245的PIN脚设置***************************************************/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	// EN_245，DIR
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	/************************************************595的PIN脚设置***************************************************/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	// EN_595_2
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	//EN_595_2,SER1,SRC,SER2,RC
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	EN1_595_OFF();
	EN2_595_OFF();
	/************************************************蜂鸣器，继电器，单片机指示灯的PIN脚设置***************************************************/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	// 综合报警输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	// BUZZ,RL3,RL2,RL1
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	// 单片机运行指示灯
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	/************************************************LED0-LED7的PIN脚设置***************************************************/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10;    //LED0-LED2
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8;     //LED3-LED7
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/************************************************报警初始化***************************************************/
	EN1_595_ON();
	EN2_595_ON();
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	BUZZ_OFF();
	AL_OFF();
	RL1_OFF();
	RL2_OFF();
	RL3_OFF();
	LED_N_OFF(0);
	LED_N_OFF(1);
	LED_N_OFF(2);
	LED_N_OFF(3);
	LED_N_OFF(4);
	LED_N_OFF(5);
	LED_N_OFF(6);
	LED_N_OFF(7);
	Operation_595();
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
}




/**************************************************************************
功    能：使某一个指示灯亮
输入参数：第n个指示灯
输出参数：无
备    注：用于数组上
**************************************************************************/
void Operation_595(void)							//LED显示 共阳极，高电平点亮
{
	uchar	i;
	uchar vaule1,vaule2,temp1,temp2,n1=0x01,n2=0x01;
	vaule1=DATA1_595;
	vaule2=DATA2_595;
	RCLK_Low();
	for (i=0; i<8; i++)
	{
		SRCLK_Low();
		temp1=vaule1 & n1;
		if (temp1==0)
		{
			SER1_High();
		}
		else
		{
			SER1_Low();
		}
		n1=n1<<1;
		temp2=vaule2 & n2;
		if (temp2==0)
		{
			SER2_High();
		}
		else
		{
			SER2_Low();
		}
		n2=n2<<1;
		SRCLK_High();
	}
	RCLK_High();
	RCLK_Low();
}

void LED_N_ON(uchar n)
{
	switch (n)
	{
	case 0:
		GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
		break;
	case 1:
		GPIO_WriteBit(GPIOC, GPIO_Pin_11, Bit_RESET);
		break;
	case 2:
		GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_RESET);
		break;
	case 3:
		GPIO_WriteBit(GPIOA, GPIO_Pin_12, Bit_RESET);
		break;
	case 4:
		GPIO_WriteBit(GPIOA, GPIO_Pin_11, Bit_RESET);
		break;
	case 5:
		GPIO_WriteBit(GPIOA, GPIO_Pin_10, Bit_RESET);
		break;
	case 6:
		GPIO_WriteBit(GPIOA, GPIO_Pin_9, Bit_RESET);
		break;
	case 7:
		GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
		break;
	default:
		break;
	}
}

void RL_N_ON(uchar n)
{
	switch (n)
	{
	case 24:
		RL1_ON();
		break;
	case 25:
		RL2_ON();
		break;
	case 26:
		RL3_ON();
		break;
	default:
		break;
	}
}




void LED_N_OFF(uchar n)
{
	switch (n)
	{
	case 0:
		GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
		break;
	case 1:
		GPIO_WriteBit(GPIOC, GPIO_Pin_11, Bit_SET);
		break;
	case 2:
		GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_SET);
		break;
	case 3:
		GPIO_WriteBit(GPIOA, GPIO_Pin_12, Bit_SET);
		break;
	case 4:
		GPIO_WriteBit(GPIOA, GPIO_Pin_11, Bit_SET);
		break;
	case 5:
		GPIO_WriteBit(GPIOA, GPIO_Pin_10, Bit_SET);
		break;
	case 6:
		GPIO_WriteBit(GPIOA, GPIO_Pin_9, Bit_SET);
		break;
	case 7:
		GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
		break;
	default:
		break;
	}
}

void RL_N_OFF(uchar n)
{
	switch (n)
	{
	case 24:
		RL1_OFF();
		break;
	case 25:
		RL2_OFF();
		break;
	case 26:
		RL3_OFF();
		break;
	default:
		break;
	}
}


void DATA_TO_595(void)
{
	uchar i=0;
	DATA1_595=0x00;
	DATA2_595=0x00;
	if (flash_cnt&0x01)			        //1为闪光
	{
		for (i = 8; i < 27; i++)
		{
			if (NewAlarmStature.LED[i]==1)
			{
				Status_595_temp[i-8]=0;
			}
		}
	}
	else
	{
		for (i = 8; i < 27; i++)
		{
			if (NewAlarmStature.LED[i]==1)
			{
				Status_595_temp[i-8]=1;
			}
		}
	}
	for (i = 8; i < 27; i++)
	{
		if (NewAlarmStature.LED[i]==2)
		{
			Status_595_temp[i-8]=1;
		}
	}
	for (i = 8; i < 27; i++)
	{
		if (NewAlarmStature.LED[i]==0)
		{
			Status_595_temp[i-8]=0;
		}
	}

	DATA1_595|=Status_595_temp[7];
	DATA1_595|=Status_595_temp[6]<<1;
	DATA1_595|=Status_595_temp[5]<<2;
	DATA1_595|=Status_595_temp[4]<<3;
	DATA1_595|=Status_595_temp[3]<<4;
	DATA1_595|=Status_595_temp[2]<<5;
	DATA1_595|=Status_595_temp[1]<<6;
	DATA1_595|=Status_595_temp[0]<<7;

	DATA2_595|=Status_595_temp[15];
	DATA2_595|=Status_595_temp[14]<<1;
	DATA2_595|=Status_595_temp[13]<<2;
	DATA2_595|=Status_595_temp[12]<<3;
	DATA2_595|=Status_595_temp[11]<<4;
	DATA2_595|=Status_595_temp[10]<<5;
	DATA2_595|=Status_595_temp[9]<<6;
	DATA2_595|=Status_595_temp[8]<<7;
}

void Operation_out(void)
{
	uchar i=0;
	if (flash_cnt&0x01)			        //1为闪光
	{
		for (i = 0; i < 8; i++)
		{
			if (NewAlarmStature.LED[i]==1)
			{
				LED_N_OFF(i);
			}
		}
		for (i = 24; i < 27; i++)
		{
			if (NewAlarmStature.LED[i]==1)
			{
				RL_N_OFF(i);
			}
		}
		if (BUZZ_flag==1)
		{
			if (BUZZ_Deploy==1)
			{
				BUZZ_OFF();
			}
		}
		if (AL_Deploy==1)
		{
			if (AL_flag==1)
			{
				AL_OFF();
			}
		}
	}
	else
	{
		for (i = 0; i < 8; i++)
		{
			if (NewAlarmStature.LED[i]==1)
			{
				LED_N_ON(i);
			}
		}
		for (i = 24; i < 27; i++)
		{
			if (NewAlarmStature.LED[i]==1)
			{
				RL_N_ON(i);
			}
		}
		if (BUZZ_flag==1)
		{
			if (BUZZ_Deploy==1)
			{
				BUZZ_ON();
			}
		}
		if (AL_Deploy==1)
		{
			if (AL_flag==1)
			{
				AL_ON();
			}
		}
	}
	for (i = 0; i < 8; i++)
	{
		if (NewAlarmStature.LED[i]==2)
		{
			LED_N_ON(i);
		}
		if (NewAlarmStature.LED[i]==0)
		{
			LED_N_OFF(i);
		}
	}
	for (i = 24; i < 27; i++)
	{
		if (NewAlarmStature.LED[i]==2)
		{
			RL_N_ON(i);
		}
		if (NewAlarmStature.LED[i]==0)
		{
			RL_N_OFF(i);
		}
	}
	if (BUZZ_flag==1)
	{
		if (BUZZ_Deploy==0)
		{
			BUZZ_ON();
		}
	}
	if (AL_Deploy==0)
	{
		if (AL_flag==1)
		{
			AL_ON();
		}
		else
		{
			AL_OFF();
		}
	}
	else
	{
		if (AL_flag==2)
		{
			AL_ON();
		}
		if (AL_flag==0)
		{
			AL_OFF();
		}
	}
	if (BUZZ_flag==0)
	{
		BUZZ_OFF();
	}
	Operation_595();
}

void PWM_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);


	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Remap TIM3 GPIOs */
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);	// TIM3复用功能映射

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	PrescalerValue = (uint16_t) (SystemCoreClock / 72000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 665;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channe33 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR5_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC3Init(TIM3, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3, ENABLE);

	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);

//	TIM_SetCompare3(TIM3,CCR3_Val);
}

uchar KeyPress(void)
{
	static	uint 	keypress=0x00,lKeyPress=0x00;     //本次按键值和上次按键值初始化

	if (READ_DIM() == KEY_DOWN_STATUS)				// 调光按键按下
	{
		if (READ_DIM() == KEY_DOWN_STATUS)
		{
			keypress=1;
		}
		else
		{
			keypress=0;
		}
	}
	else
	{
		keypress=0;
	}

	if (keypress==0x00)
	{
		lKeyPress=0x00;
		return(0);
	}

	if (lKeyPress==keypress)  //当上次按键值和本次按键值相同时，返回0
	{
		return(0);
	}
	else
	{
		lKeyPress=keypress;

		return(keypress);
	}
}



void PWM_Process(void)
{
	static uchar KeyLedBL_Count = 3, KeyLedBL_Count_Dir = 0;// 背光按键计数器（1-5），计数方向（0-增加，1-减少）
	uchar keypress_PWM=0;
	keypress_PWM=KeyPress();
	if (keypress_PWM==1)
	{
		if (KeyLedBL_Count == 1)			// 判断下限
		{
			KeyLedBL_Count_Dir = 0;			// 背光增加
		}
		if (KeyLedBL_Count == 5)			// 判断上限
		{
			KeyLedBL_Count_Dir = 1;			// 背光减少
		}
		switch (KeyLedBL_Count_Dir)			// 切换亮度变化方向
		{
		case 0:
			KeyLedBL_Count ++;
			break;
		case 1:
			KeyLedBL_Count --;
			break;
		}
	}


	// 背光调节
	switch (KeyLedBL_Count)
	{
	case 1:
		TIM_SetCompare3(TIM3,CCR1_Val);
		break;
	case 2:
		TIM_SetCompare3(TIM3,CCR2_Val);
		break;
	case 3:
		TIM_SetCompare3(TIM3,CCR3_Val);
		break;
	case 4:
		TIM_SetCompare3(TIM3,CCR4_Val);
		break;
	case 5:
		TIM_SetCompare3(TIM3,CCR5_Val);
		break;
	}
}
