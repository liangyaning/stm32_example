    
#define  POWER_GLOBAL

#include "Power\Power.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void Power_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    /*PWR-OFF(PC15) shutdown detection*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //Init GPIO C  clock
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);   // Init GPIOC

    /*PWE(PC14) power on*/
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14 /*GPIO_Pin_2|GPIO_Pin_8|GPIO_Pin_5*/;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);   // Init GPIOC    

   // printf("Power init ok !_!\n");
}




void Power_On(void)
{
    GPIO_SetBits(GPIOC, GPIO_Pin_14) ;  
}

void Power_Off(void)
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_14); 
}


