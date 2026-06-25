#ifndef MODULES_PASSIVEBUZZER_PASSIVE_BUZZER_H_
#define MODULES_PASSIVEBUZZER_PASSIVE_BUZZER_H_

#include <stm32f4xx_hal.h>

class PassiveBuzzer {
public:
	void init(TIM_HandleTypeDef* pT, uint8_t ch);
	void soundBuzzer();
	void silenceBuzzer();

private:
	TIM_HandleTypeDef* pvmTimer = nullptr;
	uint8_t channel = 0;
};




#endif /* MODULES_PASSIVEBUZZER_PASSIVE_BUZZER_H_ */
