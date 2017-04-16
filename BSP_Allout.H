#ifndef BSP_ALLOUT_H
#define BSP_ALLOUT_H

/* Includes ------------------------------------------------------------------*/
#include "UserConfig.h"


/* Exported types ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define AL_ON()				GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET)		
#define BUZZ_ON()			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET)	
#define RL1_ON()			GPIO_WriteBit(GPIOC, GPIO_Pin_3, Bit_RESET)
#define RL2_ON()			GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_RESET)
#define RL3_ON()			GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET)

#define AL_OFF()			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET)		
#define BUZZ_OFF()			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET)		
#define RL1_OFF()			GPIO_WriteBit(GPIOC, GPIO_Pin_3, Bit_SET)
#define RL2_OFF()			GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET)
#define RL3_OFF()			GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET)

#define SER1_High()			GPIO_WriteBit(GPIOC, GPIO_Pin_4, Bit_SET)	
#define SER1_Low()			GPIO_WriteBit(GPIOC, GPIO_Pin_4, Bit_RESET)

#define SER2_High()			GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET)	
#define SER2_Low()			GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET)

#define SRCLK_High()		GPIO_WriteBit(GPIOC, GPIO_Pin_5, Bit_SET)	
#define SRCLK_Low()			GPIO_WriteBit(GPIOC, GPIO_Pin_5, Bit_RESET)

#define EN1_595_ON()		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_RESET)
#define EN1_595_OFF()		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_SET)

#define EN2_595_ON()		GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET)
#define EN2_595_OFF()		GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET)

#define RCLK_High()			GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET)	
#define RCLK_Low()			GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET)



/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */
void BSP_Allouts_Config(void);
void Operation_595(void);
void DATA_TO_595(void);
void Operation_out(void);
void LED_N_OFF(uchar n);
void LED_N_ON(uchar n);
void RL_N_OFF(uchar n);
void RL_N_ON(uchar n);
void PWM_Config(void);
void PWM_Process(void);
uchar KeyPress(void);
#endif
