/*
 * taskpicture.h
 *
 *  Created on: 20 de may. de 2024
 *      Author: mpeiro
 */

#ifndef INC_TASKPICTURE_H_
#define INC_TASKPICTURE_H_


#include "..\..\pract1_rtos.h"

#define BUF_HEAD_SIZE 54

FILE *fpzip;
char buffer[BUF_HEAD_SIZE];
char filezipname[30];


short int Read_BMP_ZipFile(char *file_name);
void TaskPicture(void* pdata);


#endif /* INC_TASKPICTURE_H_ */
