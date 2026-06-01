#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#include "data_structs.h"

class SettingsConfig {
public:
	LogConfig getLogData() const { return log; }
	TempAlertConfig getTempAlertData() const { return tempAlert; }
	HumAlertConfig getHumAlertData() const { return humAlert; }

	void setLogData(const LogConfig& l) { log = l; }
	void setTempAlertData(const TempAlertConfig& a) { tempAlert = a; }
	void setHumAlertData(const HumAlertConfig& a) { humAlert = a; }

private:
	LogConfig log;
	TempAlertConfig tempAlert;
	HumAlertConfig humAlert;
};



#endif /* INC_SETTINGS_H_ */
