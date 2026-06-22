#include <fatfs.h>

#ifndef ADAPTERS_INC_FILE_MANAGER_H_
#define ADAPTERS_INC_FILE_MANAGER_H_

class FileManager {
public:
	void createFileIfNotExist(const char* fileName);
	void deleteNode(const char* nodeName);
	void writeToFile(const char* fileName, const char* text);
	void readFromFile(const char* fileName, char* output, uint32_t numBytes);
	void init();

private:
	FATFS fatFs;
	FIL file;
};



#endif /* ADAPTERS_INC_FILE_MANAGER_H_ */
