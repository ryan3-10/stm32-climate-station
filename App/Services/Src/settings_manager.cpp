#include "settings_manager.h"

void SettingsManager::notifyObservers() const {
	for (uint8_t i = 0; i < count; ++i) {
		observers.at(i)->onSettingsChange(settings);
	}
}




