#include "file_manager.h"
#include <fatfs.h>
#include <stdio.h>
#include <string.h>

void FileManager::createFileIfNotExist(const char* fileName) {
	FIL file;
	auto fres = f_open(&file, fileName, FA_CREATE_NEW);

	if (fres == FR_OK) {
		printf("Succesfully created file '%s\n", fileName);
	} else if (fres == FR_EXIST) {
		printf("File %s already exists\n", fileName);
	}
	else {
		printf("Failed to create file %s. Error: (%i)\n", fileName, fres);
	}

	f_close(&file);
}

void FileManager::writeToFile(const char* fileName, const char* text) {
	FIL fil;
	f_open(&fil, fileName, FA_WRITE | FA_OPEN_APPEND);

	UINT bytesWrote;
	auto fres = f_write(&fil, text, strlen(text), &bytesWrote);

	if (fres == FR_OK) {
		printf("Wrote %i bytes to '%s'!\r\n", bytesWrote, fileName);
	} else {
		printf("f_write error (%i)\r\n", fres);
	}

	f_close(&fil);
}

void FileManager::init() {
	//Open the file system
	auto fres = f_mount(&fatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
		printf("f_mount error (%i)\r\n", fres);
	}
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
//    //Now let's try to open file "test.txt"
//    fres = f_open(&fil, "test.txt", FA_READ);
//    if (fres != FR_OK) {
//	  printf("f_open error (%i)\r\n", fres);
//	  while(1);
//    }
//    printf("I was able to open 'test.txt' for reading!\r\n");
//
//    //Read 30 bytes from "test.txt" on the SD card
//    BYTE readBuf[30];
//
//    //We can either use f_read OR f_gets to get data out of files
//    //f_gets is a wrapper on f_read that does some string formatting for us
//    TCHAR* rres = f_gets((TCHAR*)readBuf, 30, &fil);
//    if(rres != 0) {
//      printf("Read string from 'test.txt' contents: %s\r\n", readBuf);
//    } else {
//      printf("f_gets error (%i)\r\n", fres);
//    }
//
//    //Be a tidy kiwi - don't forget to close your file!
//    f_close(&fil);
//
//
//
//      //We're done, so de-mount the drive
//      f_mount(NULL, "", 0);



