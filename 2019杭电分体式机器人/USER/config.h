#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "stm32f10x.h"
#include "millisecondtimer.h"


#define PI 3.1415926

#define K_P 2.475  // P constant
#define K_I 0.029 // I constant
#define K_D 0.02  // D constant


#define hK_P 0.40  // P constant
#define hK_I 0.1 // I constant
#define hK_D 0.01  // D constant


#define MaxVel (1.20)


#define fast_vel (0.7)		//һ������³���
#define slow_vel (0.2)		//���ӻ�������״̬����ͳ���
#define down_vel (0.05)	//�ﵽ���һ��ʱ��ÿ�����ڼ��µ��ٶ�




#define True 1
#define False 0

/** motor param **/
#define MAX_RPM 8000      //motor's maximum RPM���ת��
#define COUNTS_PER_REV 19 //wheel encoder's no of ticks per rev(gear_ratio * pulse_per_rev)���ٱ�
#define WHEEL_DIAMETER 0.055 //wheel's diameter in metersֱ��


/** LED config **/
#define LED_PIN1 GPIO_Pin_0
#define LED_PIN2 GPIO_Pin_1
#define LED_GPIO_PORT GPIOC
#define LED_GPIO_CLK RCC_APB2Periph_GPIOC



#define LED_GPIO_PORT3 GPIOF
#define LED_PIN3 GPIO_Pin_10
#define LED_GPIO_CLK3 RCC_APB2Periph_GPIOF


/**BEEP config**/
#define BEEP_PIN          GPIO_Pin_15
#define BEEP_PORT          GPIOA
#define BEEP_CLK          RCC_APB2Periph_GPIOA



/**bottom_sensor config**/
#define infrared_PIN1          GPIO_Pin_0
#define infrared_PORT1          GPIOB
#define infrared_CLK1          RCC_APB2Periph_GPIOB

#define infrared_PIN2          GPIO_Pin_1
#define infrared_PORT2          GPIOB
#define infrared_CLK2          RCC_APB2Periph_GPIOB

#define infrared_PIN3          GPIO_Pin_2
#define infrared_PORT3          GPIOB
#define infrared_CLK3         RCC_APB2Periph_GPIOB

#define infrared_PIN4          GPIO_Pin_3
#define infrared_PORT4          GPIOB
#define infrared_CLK4          RCC_APB2Periph_GPIOB

/**huidu config**/

//ADC�궨��
#define       ADCx                         ADC1
#define       ADCx_CLK                     RCC_APB2Periph_ADC1

#define       ADC_GPIO_CLK                 RCC_APB2Periph_GPIOC
#define       ADC_PORT                     GPIOC

//ת��ͨ������
#define       NOFCHANEL                    4

#define       ADC_PIN1                     GPIO_Pin_2
#define       ADC_CHANNEL1                 ADC_Channel_12
#define       ADC_PIN2                     GPIO_Pin_3
#define       ADC_CHANNEL2                 ADC_Channel_13
#define       ADC_PIN3                     GPIO_Pin_4
#define       ADC_CHANNEL3                 ADC_Channel_14
#define       ADC_PIN4                     GPIO_Pin_5
#define       ADC_CHANNEL4                 ADC_Channel_15

//ADC1��ӦDMA1ͨ��1��ADC3��ӦDMA2ͨ��5��ADC2û��DMA����
#define       ADC_DMA_CHANNEL              DMA1_Channel1

//ת����,��(0~4096)��ģ�������0��3.3V��ʵ�ʵ�ѹ
#define       CONVERT a                    (float)a/4096*3.3


/**key config**/
#define key_PIN1          GPIO_Pin_4
#define key_PIN2          GPIO_Pin_5
#define key_PIN3          GPIO_Pin_6
#define key_PIN4          GPIO_Pin_7
#define key_PIN5          GPIO_Pin_8
#define key_PIN6          GPIO_Pin_1

#define key_PORT          GPIOE
#define key_CLK         RCC_APB2Periph_GPIOE



#endif // _CONFIG_H_
