#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#include "data_structs.h"

struct Settings {
	LogConfig log;
	TempAlertConfig tempAlert;
	HumAlertConfig humAlert;
};


#endif /* INC_SETTINGS_H_ */
