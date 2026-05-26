#ifndef APP_H_
#define APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f4xx_hal.h>

void run_app(I2C_HandleTypeDef* hi2c);

#ifdef __cplusplus
}
#endif

#endif /* APP_H_ */
