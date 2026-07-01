#include "health_checkable.h"
#include <fatfs.h>

#ifndef ADAPTERS_INC_FILE_MANAGER_H_
#define ADAPTERS_INC_FILE_MANAGER_H_

class FileManager : public HealthCheckable {
public:
	FRESULT createFileIfNotExist(const char* fileName);
	FRESULT deleteNode(const char* nodeName);
	FRESULT writeToFile(const char* fileName, const char* text);
	FRESULT readFromFile(const char* fileName, char* output, uint32_t numBytes);
	FRESULT mount();
	FRESULT unmount();
	FRESULT getStats(uint32_t& totalSectors, uint32_t& freeSectors);
	bool isHardwareErr() const;
	const char* getErrorCode() const override { return "Sd"; }
	virtual bool isOk() const override { return !isHardwareErr(); }
	void runHealthCheck() override;

private:
	FATFS fatFs;
	FIL file;
	FRESULT status;
	bool isMounted;
};



#endif /* ADAPTERS_INC_FILE_MANAGER_H_ */
