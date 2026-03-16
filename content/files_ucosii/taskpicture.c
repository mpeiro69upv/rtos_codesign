/*
 * taskpicture.c
 *
 *  Created on: 20 de may. de 2024
 *      Author: mpeiro
 */



#include "..\inc\taskpicture.h"




	static int filezip_number=0;



void TaskPicture(void* pdata)
{

	while(1){


	printf("Hello from PictureFlash\n");

	OSMutexPend(MutexFlash,0,&err);

		sprintf(filezipname, "/mnt/rozipfs/imagen%02d.bmp", filezip_number++);
		fpzip = fopen (filezipname, "r");

		if (fpzip == NULL) {
			printf ("Error: could not open ZIP File\n");
			filezip_number=0;
		} else {
			printf ("Opened ZIP File %02d\n",filezip_number-1);
//			fclose (fpzip);
			OSSemPend(SemaphoreMemory,0,&err);
			alt_ucosii_check_return_code(err);
#ifndef UNBLOQUE
			PixelMem[filezip_number-1][0]=OSMemGet(ImageMemory, &err);
#else
			PixelMem[0][0]=OSMemGet(ImageMemory, &err); //CASO DE 1 BLOCK
#endif
			alt_ucosii_check_return_code(err);

			// query sobre la particion de memoria
					OSMemQuery(ImageMemory, &mem_data);
					printf("Number of memory blocks = %ld, Free = %ld, Used = %ld \n",mem_data.OSNBlks,mem_data.OSNFree,mem_data.OSNUsed);
					printf("Size (in bytes) of each memory block = %lu,\n",mem_data.OSBlkSize);
					printf("Pointer to the beginning address of the memory partition = %lu,\n",mem_data.OSAddr);
					printf("Pointer to the reserved memory block = %lu,\n",&PixelMem[filezip_number-1][0]);
					printf("Pointer to the beginning of the free list of memory blocks = %lu,\n",mem_data.OSFreeList);



			Read_BMP_ZipFile(filezipname);

	//		OSMemPut(ImageMemory, PixelMem[filezip_number-1]);
	//		OSSemPost(SemaphoreMemory);
	//		alt_ucosii_check_return_code(error);

		}

		OSMutexPost(MutexFlash);


    OSTimeDlyHMSM(0, 0, 1, 0);
	}
}


//Subrutina que lee un archivo BMP de la Flash
short int Read_BMP_ZipFile(char *file_name)
{
	unsigned short date, tmp;
	unsigned short file_tipoB;
	unsigned short file_tipoM;
	unsigned short inicio_byte0, inicio_byte1, inicio_byte2, inicio_byte3;
	int inicio_imagen = 0;
	unsigned short anchura_byte0, anchura_byte1, anchura_byte2, anchura_byte3;
	int anchura_imagen = 0;
	unsigned short altura_byte0, altura_byte1, altura_byte2, altura_byte3;
	int altura_imagen = 0;
	unsigned short bitsxpixel, bitsxpixel_byte0, bitsxpixel_byte1;
	int n=0;

	FILE *fpzip;
    char buffer[BUF_HEAD_SIZE];
    char bufferpix[3];

	fpzip = fopen (file_name, "r");
	fread (buffer, BUF_HEAD_SIZE, 1, fpzip);

    //Primero se lee la cabecera del archivo
    while (1) //cabecera simple n<54. Si incluye la paleta de colores n<122
    {
    	tmp = buffer [n];
    	date = tmp & 0x00ff;

    	switch(n)
    	{
    		case 0 :
    			file_tipoB = date;
    			if (file_tipoB == 0x42) break;
    			else {printf("Formato archivo incorrecto\n"); fclose (fpzip); return -3;}
    		case 1 :
    			file_tipoM = date;
    			if (file_tipoM == 0x4d) break;
    			else {printf("Formato archivo incorrecto\n"); fclose (fpzip); return -3;}
       		case 10: inicio_byte0 = date; break;
        	case 11: inicio_byte1 = date; break;
        	case 12: inicio_byte2 = date; break;
        	case 13:
        		inicio_byte3 = date;
        		inicio_imagen = ((inicio_byte3 << 24) | (inicio_byte2 << 16) | (inicio_byte1 << 8) | inicio_byte0);
         		break;
    		case 18: anchura_byte0 = date; break;
    		case 19: anchura_byte1 = date; break;
    		case 20: anchura_byte2 = date; break;
    		case 21:
    			anchura_byte3 = date;
    			anchura_imagen = ((anchura_byte3 << 24) | (anchura_byte2 << 16) | (anchura_byte1 << 8) | anchura_byte0);
     			break;
    		case 22: altura_byte0 = date; break;
    		case 23: altura_byte1 = date; break;
    		case 24: altura_byte2 = date; break;
    		case 25:
    			altura_byte3 = date;
    			altura_imagen = ((altura_byte3 << 24) | (altura_byte2 << 16) | (altura_byte1 << 8) | altura_byte0);
     			break;
    		case 28: bitsxpixel_byte0 = date; break;
    		case 29:
    			bitsxpixel_byte1 = date;
    			bitsxpixel = ((bitsxpixel_byte1 << 8) | bitsxpixel_byte0);
     			break;
    	}
    	n++;
    	if (n == inicio_imagen) break;
    }

    printf("Nombre Archivo = %s\n", file_name);
    printf("Anchura Imagen = %d\n", anchura_imagen);
    printf("Altura  Imagen = %d\n", altura_imagen);
    printf("Bits por pixel = %d\n", bitsxpixel);

	int offset, row, col;
	unsigned short int pixel_color;
	unsigned short int pixel_color_blue, pixel_color_green, pixel_color_red;
	unsigned short int pixel_lower, pixel_higher;

	for (row = (altura_imagen-1); row >= 0; row--)
	{
		col = 0;
		while (col <= (anchura_imagen-1))
		{
			switch (bitsxpixel)
			{
				case 24:
					fread (bufferpix, 3, 1, fpzip);
			    	date = bufferpix [0];
					pixel_color_blue = date & 0x00f8;
					date = bufferpix [1];
					pixel_color_green = date & 0x00fc;
					date = bufferpix [2];
					pixel_color_red = date & 0x00f8;
					pixel_color = ((pixel_color_red << 8) | (pixel_color_green << 3) | (pixel_color_blue >> 3));
					//printf("red=%x, green=%x, blue=%x, color=%x\n", pixel_color_red, pixel_color_green, pixel_color_blue, pixel_color);
					break;
				case 16:
					fread (bufferpix, 2, 1, fpzip);
					date = bufferpix [0];
					pixel_lower = date & 0x00ff;
					date = bufferpix [1];
					pixel_higher = date& 0x00ff;
					pixel_color = ((pixel_higher << 8) | pixel_lower);
					//printf("higher=%x, lower=%x, color=%x\n", pixel_higher, pixel_lower, pixel_color);
					break;
				default: printf("Formato de bits por pixel incorrecto\n");  fclose (fpzip); return -3;
			}
			offset = (row << 9) + col;
			// para 4 bloques
#ifndef UNBLOQUE
			PixelMem[filezip_number-1][offset]=pixel_color;
			//para 1 bloque
#else
			PixelMem[0][offset]=pixel_color;
#endif
			++col;
		}
	}

	fclose (fpzip);

	return 0;
}

