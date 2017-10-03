
#include "utils.h"

static uint8_t reboot=0;
RTC_HandleTypeDef hrtc;

void set_reboot(uint8_t r){
  reboot=r;
}

void init_vector_table(){
  SCB->VTOR = (FLASH_BASE | 0x4000);
}

void check_bootloader(){
  if(reboot){
    for(int i=0;i<30;i++){
      HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
      HAL_Delay(50);
    }

    hrtc.Instance = RTC;
    hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
    hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
    HAL_RTC_Init(&hrtc);
    HAL_RTCEx_BKUPWrite(&hrtc,RTC_BKP_DR10,0xdeaf);
    HAL_RTC_DeInit(&hrtc);
      
    HAL_NVIC_SystemReset();    
  }
}

void reenumerate_usb(){
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct;
 
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, 0);
  HAL_Delay(100);
  HAL_GPIO_DeInit(GPIOA,GPIO_PIN_12);

  __HAL_RCC_GPIOA_CLK_DISABLE();
}