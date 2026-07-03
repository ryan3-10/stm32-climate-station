#include "app.h"
#include "application.h"

namespace {
	Application application;
}

void run_app() {
	application.run();
}

void init_app(I2C_HandleTypeDef* hi2c, TIM_HandleTypeDef* pvmTimer) {
	application.init(hi2c, pvmTimer);
}
