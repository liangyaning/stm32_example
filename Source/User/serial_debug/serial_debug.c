    
#define  SERIAL_DEBUG_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "serial_debug\serial_debug.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "main.h"

/* Private macro&definde------------------------------------------------------*/
#ifdef SERIAL_DEBUG
    #define SERIAL_DEBUG_COM                        USART2
    #define SERIAL_DEBUG_COM_CLK                    RCC_APB1Periph_USART2
    #define SERIAL_DEBUG_COM_CLK_INIT               RCC_APB1PeriphClockCmd
    #define SERIAL_DEBUG_COM_TX_PIN                 GPIO_Pin_2
    #define SERIAL_DEBUG_COM_TX_GPIO_PORT           GPIOA
    #define SERIAL_DEBUG_COM_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
    #define SERIAL_DEBUG_COM_TX_SOURCE              GPIO_PinSource2
    #define SERIAL_DEBUG_COM_RX_PIN                 GPIO_Pin_3
    #define SERIAL_DEBUG_COM_RX_GPIO_PORT           GPIOA
    #define SERIAL_DEBUG_COM_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
    #define SERIAL_DEBUG_COM_RX_SOURCE              GPIO_PinSource3
    #define SERIAL_DEBUG_COM_IRQn                   USART2_IRQn
#endif



/* Private typedef -----------------------------------------------------------*/
/* 
**  With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
**  set to 'Yes') calls __io_putchar() 
*/
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */



/* Private variables ---------------------------------------------------------*/
#ifdef SERIAL_DEBUG
#define SZ_LogBuFF_MAXSIZE  128
uint8_t aucLogBuff[SZ_LogBuFF_MAXSIZE+1] = {0};
#endif


/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
    

void __Prompt__(const char *file, int line, const char *func, const char *format, va_list argp)
#ifdef SERIAL_DEBUG
{
    if(NULL == format|| 0 == format[0]) 
    {
        return;
    }
    memset(aucLogBuff, 0, sizeof(aucLogBuff));
    vsnprintf((char *)aucLogBuff, SZ_LogBuFF_MAXSIZE, format, argp);
    printf("\n  Prompt : [%s %d]%s():", file, line, func);
    printf("%s\n", aucLogBuff);
}
#else
{
}
#endif

void __Assert__(const char *file, int line, const char *func, const char *format, va_list argp)
#ifdef SERIAL_DEBUG
{
    if (NULL == format|| 0 == format[0]) 
    {
        return;
    }
    memset(aucLogBuff, 0, sizeof(aucLogBuff));
    vsnprintf((char *)aucLogBuff, SZ_LogBuFF_MAXSIZE, format, argp);
    printf("\n  Assert : [%s %d]%s():", file, line, func);
    printf("%s\n", aucLogBuff);

}
#else
{
}
#endif


#ifdef SERIAL_DEBUG
void DebugComPort_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(SERIAL_DEBUG_COM_TX_GPIO_CLK | SERIAL_DEBUG_COM_RX_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

    /* Enable UART clock */
    SERIAL_DEBUG_COM_CLK_INIT(SERIAL_DEBUG_COM_CLK, ENABLE);   

    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = SERIAL_DEBUG_COM_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SERIAL_DEBUG_COM_TX_GPIO_PORT, &GPIO_InitStructure);

    /* Configure USART Rx as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = SERIAL_DEBUG_COM_RX_PIN;
    GPIO_Init(SERIAL_DEBUG_COM_RX_GPIO_PORT, &GPIO_InitStructure);


    /* USARTx configured as follow:
       - BaudRate = 115200 baud  
       - Word Length = 8 Bits
       - One Stop Bit
       - No parity
       - Hardware flow control disabled (RTS and CTS signals)
       - Receive and transmit enabled
       */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    

    /* USART configuration */
    USART_Init(SERIAL_DEBUG_COM, &USART_InitStructure);

    //USART_ITConfig(SERIAL_DEBUG_COM, USART_IT_RXNE, ENABLE);

    /* Enable USART */
    USART_Cmd(SERIAL_DEBUG_COM, ENABLE);
}
#endif


#ifdef SERIAL_DEBUG
/* Use no semihosting */
#pragma import(__use_no_semihosting)
struct __FILE
{  	
    int handle;
};
FILE __stdout;

_sys_exit(int x)
{
	x = x;
}

PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    while(!(SERIAL_DEBUG_COM->SR & USART_SR_TXE));
    USART_SendData(SERIAL_DEBUG_COM, (uint8_t) ch);
    while(!(SERIAL_DEBUG_COM->SR & USART_SR_TC)); 

    return ch;
}
#endif

