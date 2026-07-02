#ifndef DRIVERS_PASSIVEBUZZER_PASSIVE_BUZZER_H_
#define DRIVERS_PASSIVEBUZZER_PASSIVE_BUZZER_H_

#include <algorithm>
#include <array>
#include <stm32f4xx_hal.h>

constexpr inline std::array<uint32_t, 2> standardPattern1 = {500, 500};
constexpr inline std::array<uint32_t, 4> standardPattern2 = {200, 200, 200, 400};

class PassiveBuzzer {
public:
	void init(TIM_HandleTypeDef* pT, uint8_t ch);
	void soundBuzzer();
	void silenceBuzzer();
	void toggleBuzzer() { state ? silenceBuzzer() : soundBuzzer(); }
	void runPattern();
	void stopPattern();

	template <size_t length>
	void setPattern(const std::array<uint32_t, length>& durs) {
		// Length must be even (1 on step for each off step),
		// and length cannot be larger than the pattern array
		if (length % 2 != 0 || length > MAX_PATTERN_LENGTH) {
			return;
		}

		std::copy(durs.begin(), durs.end(), pattern.stepDurs.begin());
		pattern.length = length;
	}

private:
	static constexpr uint8_t MAX_PATTERN_LENGTH = 16;
	enum BUZZER_STATE : uint8_t {
		OFF,
		ON
	};

	enum PATTERN_STATE : uint8_t {
		IDLE,
		ACTIVE
	};

	struct Pattern {
		std::array<uint32_t, MAX_PATTERN_LENGTH> stepDurs {250, 250};
		uint8_t length;
		uint8_t index;
		uint32_t timestamp;
		PATTERN_STATE state;
	};

	TIM_HandleTypeDef* pvmTimer = nullptr;
	uint8_t channel = 0;
	Pattern pattern;
	BUZZER_STATE state;
};

#endif /* DRIVERS_PASSIVEBUZZER_PASSIVE_BUZZER_H_ */
