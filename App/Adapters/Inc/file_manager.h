#include <fatfs.h>

#ifndef ADAPTERS_INC_FILE_MANAGER_H_
#define ADAPTERS_INC_FILE_MANAGER_H_

class FileManager {
public:
	void createFileIfNotExist(const char* fileName);
	void writeToFile(const char* fileName, const char* text);
	void init();

private:
	FATFS fatFs;
};



#endif /* ADAPTERS_INC_FILE_MANAGER_H_ */
