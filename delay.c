#include "delay.h"
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 	 
 
//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
//����delay_us,delay_ms
 
static u8  fac_us=0;//us��ʱ������			   
static u16 fac_ms=0;//ms��ʱ������


			   
//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8,SYSCLK:ϵͳʱ��
void delay_init(u8 SYSCLK)
{
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SYSCLK/8;		
	fac_ms=(u16)fac_us*1000;//ms sysclk 

}								    

//��ʱnus,nusΪҪ��ʱ��us��.	
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 												//ʱ�����	  		 
	SysTick->VAL=0x00;        												//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ���� 
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));							//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       		//�رռ�����
	SysTick->VAL =0X00;       												//��ռ�����	 
}
//��ʱnms
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:nms<=0xffffff*8*1000/SYSCLK,SYSCLK��λΪHz,nms��λΪms,��168M������,nms<=798ms 
void delay_xms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;										//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           										//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));							//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       		//�رռ�����
	SysTick->VAL =0X00;       												//��ռ�����	  	    
} 
//��ʱnms
void delay_ms(u16 nms)
{	 	 
	u8 repeat=nms/540;																
	u16 remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
	
} 