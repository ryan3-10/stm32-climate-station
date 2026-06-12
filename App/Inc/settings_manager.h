#ifndef INC_SETTINGS_MANAGER_H_
#define INC_SETTINGS_MANAGER_H_

#include "data_structs.h"

struct Settings {
	LogConfig log{};
	TempAlertConfig tempAlert{};
	HumAlertConfig humAlert{};
};

class SettingsManager {
public:
	SettingsManager() = default;
	LogConfig getLogConfig() { return settings.log; }
	TempAlertConfig getTempConfig() { return settings.tempAlert; }
	HumAlertConfig getHumConfig() { return settings.humAlert; }
	void setLogConfig(const LogConfig& config) { settings.log = config; }
	void setTempConfig(const TempAlertConfig& config) { settings.tempAlert = config; }
	void setHumConfig(const HumAlertConfig& config) { settings.humAlert = config; }

private:
	Settings settings;
};


#endif /* INC_SETTINGS_MANAGER_H_ */
