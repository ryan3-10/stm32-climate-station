#include "passive_buzzer.h"

void PassiveBuzzer::init(TIM_HandleTypeDef* pt, uint8_t ch) {
	pvmTimer = pt;
	ch = channel;
}

void PassiveBuzzer::soundBuzzer() {
	HAL_TIM_PWM_Start(pvmTimer, channel);
}

void PassiveBuzzer::silenceBuzzer() {
	HAL_TIM_PWM_Stop(pvmTimer, channel);
}
