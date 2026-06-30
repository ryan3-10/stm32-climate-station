#include "file_manager.h"
#include <algorithm>
#include <fatfs.h>
#include <stdio.h>
#include <string.h>

FRESULT FileManager::createFileIfNotExist(const char* fileName) {
	status = f_open(&file, fileName, FA_CREATE_NEW);
	return status;
}

FRESULT FileManager::deleteNode(const char* nodeName) {
	status = f_unlink(nodeName);
	return status;
}

FRESULT FileManager::writeToFile(const char* fileName, const char* text) {
	f_open(&file, fileName, FA_WRITE | FA_OPEN_APPEND);

	UINT bytesWrote;
	status = f_write(&file, text, strlen(text), &bytesWrote);

	f_close(&file);

	return status;
}

FRESULT FileManager::readFromFile(const char* fileName, char* output, uint32_t numBytes) {
	status = f_open(&file, fileName, FA_READ);

	//Can either use f_read OR f_gets to get data out of files
	//f_gets is a wrapper on f_read that does some string formatting
	char* rres = f_gets(output, numBytes, &file);
	f_close(&file);

	return status;
}


FRESULT FileManager::init() {
	// Mount the filesystem
	status = f_mount(&fatFs, "", 1); //1=mount now
	return status;
}

//    //Let's get some statistics from the SD card
//    DWORD free_clusters, free_sectors, total_sectors;
//
//    FATFS* getFreeFs;
//
//    fres = f_getfree("", &free_clusters, &getFreeFs);
//    if (fres != FR_OK) {
//		printf("f_getfree error (%i)\r\n", fres);
//		while(1);
//    }
//
//    //Formula comes from ChaN's documentation
//    total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
//    free_sectors = free_clusters * getFreeFs->csize;
//
//    printf("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);
//
//
//
//
//
//
//
//      //We're done, so de-mount the drive
//      f_mount(NULL, "", 0);



