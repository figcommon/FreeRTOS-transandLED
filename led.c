#include "led.h" 

//LED����	��ʼ��PF9 F10.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	__HAL_RCC_GPIOA_CLK_ENABLE();

  //GPIOA6,A7��ʼ������
  GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//��ͨ���ģʽ
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;		//100MHz
  GPIO_InitStructure.Pull = GPIO_PULLUP;							//����
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);					//��ʼ��
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6 | GPIO_PIN_7,GPIO_PIN_SET);	//GPIO ���øߣ�����

}






