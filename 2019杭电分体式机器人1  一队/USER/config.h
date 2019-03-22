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
#define ID 1  //�������

#define PI 3.1415926

#define K_P 2.775  // P constant
#define K_I 0.065 // I constant
#define K_D 0  // D constant


#define C610R		

#define hK_P 0.65  // P constant
#define hK_I 0 // I constant
#define hK_D 0.06 // D constant


#define MaxVel (0.67)


#define fast_vel (0.64)		//һ������³���
#define slow_vel (0.25)		//���ӻ�������״̬����ͳ���
#define down_vel (0.035)	//�ﵽ���һ��ʱ��ÿ�����ڼ��µ��ٶ�


#define BLACK 0
#define WHITE 1



#define True 1
#define False 0

#define Dis_Vel 500				//���ϰ�����ʱ�ĵ�ѹֵ

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����


/** motor param **/
#define MAX_RPM 8500      //motor's maximum RPM���ת��
#define COUNTS_PER_REV 36 //wheel encoder's no of ticks per rev(gear_ratio * pulse_per_rev)���ٱ�
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


#define infrared_PIN5          GPIO_Pin_4
#define infrared_PORT5          GPIOB
#define infrared_CLK5          RCC_APB2Periph_GPIOB			//infread5:��ײģ��


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
#define key_PIN1          GPIO_Pin_4		//��
#define key_PIN2          GPIO_Pin_5		//��
#define key_PIN3          GPIO_Pin_6		//��
#define key_PIN4          GPIO_Pin_7		//��
#define key_PIN5          GPIO_Pin_8		//��
#define key_PIN6          GPIO_Pin_1		//����

#define key_PORT          GPIOE
#define key_CLK         RCC_APB2Periph_GPIOE

/*duoji config*/
#define duoji_PIN1          GPIO_Pin_0
#define duoji_PORT1          GPIOA
#define duoji_CLK1          RCC_APB2Periph_GPIOA

#define duoji_PIN2          GPIO_Pin_1
#define duoji_PORT2          GPIOA
#define duoji_CLK2          RCC_APB2Periph_GPIOA

#define duoji_PIN3          GPIO_Pin_2
#define duoji_PORT3          GPIOA
#define duoji_CLK3         RCC_APB2Periph_GPIOA

#define duoji_PIN4          GPIO_Pin_8
#define duoji_PORT4          GPIOB
#define duoji_CLK4          RCC_APB2Periph_GPIOB

#define duoji_PIN5         GPIO_Pin_9
#define duoji_PORT5          GPIOB
#define duoji_CLK5          RCC_APB2Periph_GPIOB

#endif // _CONFIG_H_
