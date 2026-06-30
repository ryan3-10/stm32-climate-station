#include <fatfs.h>

#ifndef ADAPTERS_INC_FILE_MANAGER_H_
#define ADAPTERS_INC_FILE_MANAGER_H_

class FileManager {
public:
	FRESULT createFileIfNotExist(const char* fileName);
	FRESULT deleteNode(const char* nodeName);
	FRESULT writeToFile(const char* fileName, const char* text);
	FRESULT readFromFile(const char* fileName, char* output, uint32_t numBytes);
	FRESULT mount();
	bool isHardwareErr() const;

private:
	FATFS fatFs;
	FIL file;
	FRESULT status;
};



#endif /* ADAPTERS_INC_FILE_MANAGER_H_ */
