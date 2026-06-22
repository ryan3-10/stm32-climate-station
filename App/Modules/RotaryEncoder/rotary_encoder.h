#ifndef HARDWARE_INC_ROTARY_ENCODER_H_
#define HARDWARE_INC_ROTARY_ENCODER_H_

#include <stdint.h>

class RotaryEncoder {
public:
	int32_t readPos() const;
	bool buttonWasPressed() const;
};


#endif /* HARDWARE_INC_ROTARY_ENCODER_H_ */
