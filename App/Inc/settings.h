#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#include "data_structs.h"

class SettingsConfig {
public:
	LogData getLogData() const { return log; }
	AlertData getAlertData() const { return alert; }

	void setLogData(const LogData& l) { log = l; }
	void setAlertData(const AlertData& a) { alert = a; }

private:
	LogData log;
	AlertData alert;
};



#endif /* INC_SETTINGS_H_ */
