#include "stm32f10x.h"                  // Device header
#include "My_include.h"
void timer_doorLock_Init(void);
u8 Time_doorLock = 0;
int main(void){
	// GPIO_Pin_Init(PA0,GPIO_Mode_IPU);							// �������ƿ���

	
	// ���ſ��Ƽ̵��� ��ʼ������  �������  ���ϵ綯���̵���   ʹ�̵���Ϊ���ع���
	GPIO_Pin_Init(PB13,GPIO_Mode_Out_PP);
	PBout(13) = 0;
	// static u8 Time_doorLock = 0;
	
	timer_doorLock_Init();
	
	while(1){
//		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0){			
//		
//		
//		/* */
//			
//		while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0))
//			;
//		Delay_ms(30);		// ������

//		}
	
	
	}

}


void timer_doorLock_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision 	= 	TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode 		= 	TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period 			= 	(36000 - 1);						// ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler 		= 	(2000 - 1);							// PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 	0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	
	TIM_Cmd(TIM4, ENABLE);
	
	
}


void TIM4_IRQHandler(void){
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) == SET){
		Time_doorLock++;
		if(Time_doorLock == 10){
			Time_doorLock = 0;
			// 12sʱ�䵽 �Ŵ��ϵ� ��ʹ��TIM4 �Զ������ر�
			PBout(13) = 1;				// �Ŵ��ϵ�  ���ɿ���
 		}
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);		// ע�����д���û��ִ�� ��PB13 = 1��оƬʧ�磬����û��ʧ��ʱ��ϵͳ��Ӱ��
}



