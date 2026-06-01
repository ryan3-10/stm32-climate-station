#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#include "data_structs.h"

class SettingsConfig {
public:
	Logconfig getLogData() const { return log; }
	AlertConfig getAlertData() const { return alert; }

	void setLogData(const Logconfig& l) { log = l; }
	void setAlertData(const AlertConfig& a) { alert = a; }

private:
	Logconfig log;
	AlertConfig alert;
};



#endif /* INC_SETTINGS_H_ */
