#include "main.h"
char AT_cmd[10];
char i = 0;
char str_flag = 0;
/************************************************************/
/*                    初始化UART串口                        */
/*                uartNo为需要设置的串口编号                */
/*                   sysclk为系统时钟频率                   */
/*                baud为需要设置的串口的波特率              */
/*                intStatus: 为初始化中断的状态Y-MC�           */
/*                1表示开中断 其它表示关中断                */
/************************************************************/
void UART_INIT(uint8 uartNo, int32 sysclk, int32 baud, uint8 intStatus)
{
    register uint16 ubgs;
    if(uartNo > 2)
    {  //若传进的通道号大于2，则按照2来设置
        uartNo = 2;
    }
    
	//使能UART接口功能
	if(uartNo==0)
		MCF_GPIO_PUAPAR=MCF_GPIO_PUAPAR_UTXD0_UTXD0      
				   	   |MCF_GPIO_PUAPAR_URXD0_URXD0;
    else if(uartNo==1)
	    MCF_GPIO_PUBPAR=MCF_GPIO_PUBPAR_UTXD1_UTXD1
    			       |MCF_GPIO_PUBPAR_URXD1_URXD1;
    else
   		MCF_GPIO_PUCPAR=MCF_GPIO_PUCPAR_UTXD2_UTXD2
    			       |MCF_GPIO_PUCPAR_URXD2_URXD2;
    	
    //复位接收器和发送器以及模式寄存器
    MCF_UART_UCR(uartNo) = MCF_UART_UCR_RESET_TX;  //复位发送器
    MCF_UART_UCR(uartNo) = MCF_UART_UCR_RESET_RX;  //复位接收器
    MCF_UART_UCR(uartNo) = MCF_UART_UCR_RESET_MR;  //复位模式寄存器
    //配置UART模式:无奇偶校验、8位数据、正常通道模式、1停止位
    MCF_UART_UMR(uartNo) = (0
                          | MCF_UART_UMR_PM_NONE
                          | MCF_UART_UMR_BC_8 );
    MCF_UART_UMR(uartNo) = (0
                          | MCF_UART_UMR_CM_NORMAL
                          | MCF_UART_UMR_SB_STOP_BITS_1);
                          
    //选择预分频后的内部总线时钟作为收发器的时钟源
    MCF_UART_UCSR(uartNo) = (0
				           |MCF_UART_UCSR_RCS_SYS_CLK
		  		           |MCF_UART_UCSR_TCS_SYS_CLK);
    
    //屏蔽所有的UART中断
    MCF_UART_UIMR(uartNo) = 0;
    //计算波特率并设置:UBG = fsys/(波特率*32)
    ubgs = (uint16)(sysclk/(baud * 32));
    MCF_UART_UBG1(uartNo) = (uint8)((ubgs & 0xFF00) >> 8);
    MCF_UART_UBG2(uartNo) = (uint8) (ubgs & 0x00FF);
    
    //使能接收器和发送器
    MCF_UART_UCR(uartNo) = (0
                          | MCF_UART_UCR_RX_ENABLED
                          | MCF_UART_UCR_TX_ENABLED);
    
    //决定是否开放UARTx接收中断
    if(1 == intStatus)
    {  //开串行接收中断
        MCF_UART_UIMR(uartNo) = 0x02;
		if(uartNo==0)
		{
			MCF_INTC0_IMRL&=~MCF_INTC_IMRL_MASKALL;       //使能总中断
			MCF_INTC0_IMRL&=~MCF_INTC_IMRL_INT_MASK13;    //使能UART0中断
			MCF_INTC0_ICR13=MCF_INTC_ICR_IP(6)+MCF_INTC_ICR_IL(2);	 //设置中断优先级
		}
		else if(uartNo==1)
		{
			MCF_INTC0_IMRL&=~MCF_INTC_IMRL_MASKALL;       //使能总中断
			MCF_INTC0_IMRL&=~MCF_INTC_IMRL_INT_MASK14;    //使能UART1中断
			MCF_INTC0_ICR14=MCF_INTC_ICR_IP(5)+MCF_INTC_ICR_IL(2);  //设置中断优先级	
		}
		else
		{
			MCF_INTC0_IMRL&=~MCF_INTC_IMRL_MASKALL;       //使能总中断
			MCF_INTC0_IMRL&=~MCF_INTC_IMRL_INT_MASK15;    //使能UART2中断
			MCF_INTC0_ICR15=MCF_INTC_ICR_IP(4)+MCF_INTC_ICR_IL(2); //设置中断优先级		
		}

    }
    else
    {  //禁串行接收中断
        MCF_UART_UIMR(uartNo) = 0x00;
		if(uartNo==0)
		{
			MCF_INTC0_IMRL|=MCF_INTC_IMRL_INT_MASK13;    //禁止UART0中断
		}
		else if(uartNo==1)
		{
			MCF_INTC0_IMRL|=MCF_INTC_IMRL_INT_MASK14;    //禁止UART1中断
		}
		else
		{
			MCF_INTC0_IMRL|=MCF_INTC_IMRL_INT_MASK15;    //禁止UART2中断
		}
    }
}

/************************************************************/
/*                    UART发送一个字节                      */
/*                uartNo为用来发送的串口编号                */
/*                   data为需要发送的数据                   */
/************************************************************/
void UART_Send1byte(uint8 uartNo, uint8 data)
{
    if(uartNo > 2)
    {  //若传进的通道号大于2，则按照2来发送
        uartNo = 2;
    }
    
    //等待FIFO中有空闲缓冲区可用
    while (!(MCF_UART_USR(uartNo) & MCF_UART_USR_TXRDY))
    {
    }
    //发送数据
    MCF_UART_UTB(uartNo) = data;
}

/************************************************************/
/*                    UART接收一个字节                      */
/*                uartNo为用来接收的串口编号                */
/************************************************************/
uint8 UART_Receive1byte(uint8 uartNo)
{
    if(uartNo > 2)
    {  //若传进的通道号大于2，则按照2来接收
        uartNo = 2;
    }

    //等待接收数据
    while (!(MCF_UART_USR(uartNo) & MCF_UART_USR_RXRDY)) 
    {
    }
    
    //返回接收到的数据
    return MCF_UART_URB(uartNo);	
}

/************************************************************/
/*                    UART发送字符串函数                    */
/*                uartNo为用来发送的串口编号                */
/*                p为需要发送的字符串的指针                 */
/************************************************************/
void UART_SendString(uint8 uartNo, char *p)
{
	while(*p!=0x00)       //判断字符串是否发送完毕
	{
		UART_Send1byte(uartNo,*p++); 
	}
}

/************************************************************/
/*                   UART0中断接收函数                      */
/************************************************************/
__declspec(interrupt:0) void UART0_inter(void)//13
{
	uint8 temp;
	temp=UART_Receive1byte(0);
	if((temp == 'A') || (str_flag == 1))
	{
		str_flag = 1;
		switch(temp)
		{
			case 0xff://紧急停车
				{
					PIT0_stop();
					set_motor_highduty(0,0);
					while(1);	
				}
			
		}
		if(temp = ';')
		{
			str_flag = 0;
		}
		/*
		if(temp != ';')
		{
			AT_cmd[i] = temp;
			i++;
		}
		else
		{
			AT_cmd[i] = 0;
			i = 0;
			UART_SendString(0,AT_cmd);
			str_flag = 0;
		}
		*/
	}
}
/************************************************************/
/*                    UART发送虚拟示波器函数                */
/*                uartNo为用来发送的串口编号                */
/*                data为要发送的整型数值                    */
/************************************************************/
void UART_Sendgraph(uint8 uartNO,uint8 channel,int data)
{
	UART_Send1byte(uartNO,0xA0);//帧头
	UART_Send1byte(uartNO,channel);//功能码决定通道
	UART_Send1byte(uartNO,6);
	UART_Send1byte(uartNO,data>>8);
	UART_Send1byte(uartNO,data);
	UART_Send1byte(uartNO,0xFF);//帧尾
}
void UART_Sendint(uint8 uartNO,int num)
{
	char str[16];
	sprintf(str,"%d",num);
	UART_SendString(uartNO,str);
}