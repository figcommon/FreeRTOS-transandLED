#include "led.h" 

//LED驱动	初始化PF9 F10.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	__HAL_RCC_GPIOA_CLK_ENABLE();

  //GPIOA6,A7初始化设置
  GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//普通输出模式
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;		//100MHz
  GPIO_InitStructure.Pull = GPIO_PULLUP;							//上拉
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);					//初始化
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6 | GPIO_PIN_7,GPIO_PIN_SET);	//GPIO 设置高，灯灭

}






