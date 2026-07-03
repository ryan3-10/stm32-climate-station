#include "file_manager.h"
#include <fatfs.h>
#include <string.h>

void FileManager::runHealthCheck() {
	// Unfortunately all we can do with the current library.
	// Need to reset the program if this becomes unhealthy during runtime
	if (!isMounted) {
		mount();
	}
}

FRESULT FileManager::createFileIfNotExist(const char* fileName) {
	status = f_open(&file, fileName, FA_OPEN_ALWAYS);

	if (status == FR_OK)
		status = f_close(&file);

	return status;
}

FRESULT FileManager::deleteNode(const char* nodeName) {
	status = f_unlink(nodeName);
	return status;
}

FRESULT FileManager::writeToFile(const char* fileName, const char* text) {
	status = f_open(&file, fileName, FA_WRITE | FA_OPEN_APPEND);

	UINT bytesWrote;

	if (status == FR_OK)
		status = f_write(&file, text, strlen(text), &bytesWrote);

	if (status == FR_OK)
		f_close(&file);

	return status;
}

FRESULT FileManager::readFromFile(const char* fileName, char* output, uint32_t numBytes) {
	status = f_open(&file, fileName, FA_READ);

	//Can either use f_read OR f_gets to get data out of files
	//f_gets is a wrapper on f_read that does some string formatting
	f_gets(output, numBytes, &file);

	if (status == FR_OK)
		f_close(&file);

	return status;
}


FRESULT FileManager::mount() {
	// Mount the filesystem
	status = f_mount(&fatFs, "", 1); //1 = mount now

	if(status == FR_OK) {
		isMounted = true;
	}

	return status;
}

FRESULT FileManager::unmount() {
	status = f_mount(NULL, "", 0); // NULL = unmount

	if (status == FR_OK) {
		isMounted = false;
	}

	return status;
}

FRESULT FileManager::getStats(uint32_t& totalSectors, uint32_t& freeSectors) {
	uint32_t freeClusters;
	FATFS* fatPtr = &fatFs;
	status = f_getfree("", &freeClusters, &fatPtr);

	//Formula comes from ChaN's documentation
	if (status == FR_OK) {
		totalSectors = (fatPtr->n_fatent - 2) * fatPtr->csize;
		freeSectors = freeClusters * fatPtr->csize;
	}

	return status;
}


