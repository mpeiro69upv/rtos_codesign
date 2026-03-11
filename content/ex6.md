---
title: "6. Tareas Nadal y Grinch"
---

Llegados a este punto de la práctica, el espíritu navideño nos invade y decidimos crear dos tareas nuevas; una dibuja un árbol de navidad en la pantalla VGA y la otra nos fastidia el dibujo.

Construya la task TaskNadal con el sigiuente código.

### Tarea tasknadal

```c
#include "..\inc\tasknadal.h"

/* Prints "BON NADAL" and sleeps for x seconds */
void TaskNadal(void* pdata)
{
  char visualiza_string[40] = "Hello from NADAL";
  char blank[40]="                                      \0";

  char visualiza_string_nadal[15][40]=
  {                   "                 ",
                      "        X        ",
                      "       XXX       ",
                      "      XXXXX      ",
                      "     XXXXXXX     ",
                      "    XXXXXXXXX    ",
                      "   XXXXXXXXXXX   ",
                      "  XXXXXXXXXXXXX  ",
                      "       XXX       ",
                      "                 ",
                      " MERRY CHRISTMAS ",
                      "    BON NADAL    ",
                      "                 ",
                      "                 ",
                      "                 "};

  int nadal_pos=10;

  while (1)
  {
    printf("%s\n",visualiza_string);

    
    Led_ON_All(LED_ptr);

    //clean text on black box
    for (int var = 3; var < 60; ++var) {
      VGA_text (40, var, blank,character_buffer);
    }

    for (int var = 0; var < 15; ++var) {
      VGA_text (50, nadal_pos+var, visualiza_string_nadal[var],character_buffer);
    }

   OSTimeDlyHMSM(0, 0, 4, 0);
    
  }
}
```

Compile y capture los resultados obtenidos.
Construya la tarea Grinch y de nuevo capture los resultados obtenidos.

**Archivos para descargar:**

- [tasknadal.h](files_ucosii/tasknadal.h) - Archivo de cabecera para la tarea Nadal
- [tasknadal.c](files_ucosii/tasknadal.c) - Archivo fuente de la tarea Nadal  
- [taskgrinch.h](files_ucosii/taskgrinch.h) - Archivo de cabecera para la tarea Grinch
- [taskgrinch.c](files_ucosii/taskgrinch.c) - Archivo fuente de la tarea Grinch

Puede usar las funciones de chequeo de errores alt_ucos_error_code.c y su fichero de cabecera alt_ucos_error_code.h tras los códigos de uso de servicios de UCOS que proporcionen variables de error como retorno de llamadas al servicio.

**Archivos de control de errores:**

- [alt_ucosii_simple_error_check.h](files_ucosii/alt_ucosii_simple_error_check.h) - Archivo de cabecera para control de errores UCOS
- [alt_ucosii_simple_error_check.c](files_ucosii/alt_ucosii_simple_error_check.c) - Archivo fuente para control de errores UCOS

Incluya la librería stdlib.h en pract1_rtos.h, necesaria para el correcto funcionamiento de alt_ucos_error_code.c
•	¿Qué periodo tienen las tareas nadal y grinch? ¿Se ven durante todo el periodo?
•	¿Qué hacen las funciones de chequeo de errores? ¿dónde las utilizaría?

[Ir Ejercicio 7](ex7.md)
[Volver a Indice](index.md)