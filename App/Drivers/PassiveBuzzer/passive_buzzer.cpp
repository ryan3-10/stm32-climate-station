#include "../../Drivers/PassiveBuzzer/passive_buzzer.h"

#include "utils.h"

void PassiveBuzzer::init(TIM_HandleTypeDef* pt, uint8_t ch) {
	pvmTimer = pt;
	ch = channel;
}

void PassiveBuzzer::soundBuzzer() {
	HAL_TIM_PWM_Start(pvmTimer, channel);
	state = BUZZER_STATE::ON;
}

void PassiveBuzzer::silenceBuzzer() {
	HAL_TIM_PWM_Stop(pvmTimer, channel);
	state = BUZZER_STATE::OFF;
}

void PassiveBuzzer::runPattern() {
	switch (pattern.state) {
	case PATTERN_STATE::IDLE:
		pattern.index = 0;
		soundBuzzer();
		pattern.state = PATTERN_STATE::ACTIVE;
		pattern.timestamp = Utils::getTick();
	case PATTERN_STATE::ACTIVE:
		if (Utils::timeElapsed(pattern.timestamp) >= pattern.stepDurs[pattern.index]) {
			pattern.index = pattern.index < pattern.length - 1 ? pattern.index + 1 : 0;
			toggleBuzzer();
			pattern.timestamp = Utils::getTick();
		}
	}
}

void PassiveBuzzer::stopPattern() {
	silenceBuzzer();
	pattern.state = PATTERN_STATE::IDLE;
}
