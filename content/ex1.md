## EJERCICIO 1. CREACIÓN DE TAREAS

Modifique el nombre del fichero principal `hello_ucosii.c` por `pract1_rtos.c`.

Estudie el fichero ejemplo proporcionado y cree dos tareas adicionales, una con periodo de 1 seg y otra con periodo de 5 seg, con la misma funcionalidad que las tareas 1 y 2 ejemplo. Cada tarea debe mandar un mensaje `"Hello from task i"` con `i` = número de tarea. Las nuevas tareas tendrán prioridades 3 y 4 y sus pilas de tareas con el mismo tamaño que las tareas previas.

Compile y observe los resultados obtenidos. Recuerde capturar pantalla y redactar el documento de entrega de la práctica.

### Ejemplo de código de referencia

El siguiente fragmento muestra la estructura típica del fichero `hello_ucosii.c` de la template de uCOS-II, con dos tareas de ejemplo. Úsalo como base para añadir las nuevas tareas:

```c
#include <stdio.h>
#include "includes.h"

/* Tamaño de pila de cada tarea */
#define TASK_STACKSIZE  2048

/* Pilas de tareas */
OS_STK task1_stk[TASK_STACKSIZE];
OS_STK task2_stk[TASK_STACKSIZE];
OS_STK task3_stk[TASK_STACKSIZE];
OS_STK task4_stk[TASK_STACKSIZE];

/* Prioridades de las tareas */
#define TASK1_PRIORITY  1
#define TASK2_PRIORITY  2
#define TASK3_PRIORITY  3
#define TASK4_PRIORITY  4

/* Prototipos */
void task1(void* pdata);
void task2(void* pdata);
void task3(void* pdata);
void task4(void* pdata);

/* Tarea 1: periodo ~500 ms */
void task1(void* pdata)
{
	while (1)
	{
		printf("Hello from task1\n");
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
}

/* Tarea 2: periodo ~500 ms */
void task2(void* pdata)
{
	while (1)
	{
		printf("Hello from task2\n");
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
}

/* Tarea 3 (nueva): periodo 1 seg */
void task3(void* pdata)
{
	while (1)
	{
		printf("Hello from task3\n");
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

/* Tarea 4 (nueva): periodo 5 seg */
void task4(void* pdata)
{
	while (1)
	{
		printf("Hello from task4\n");
		OSTimeDlyHMSM(0, 0, 5, 0);
	}
}

int main(void)
{
	OSTaskCreateExt(task1, NULL, &task1_stk[TASK_STACKSIZE-1],
					TASK1_PRIORITY, TASK1_PRIORITY, task1_stk,
					TASK_STACKSIZE, NULL, 0);

	OSTaskCreateExt(task2, NULL, &task2_stk[TASK_STACKSIZE-1],
					TASK2_PRIORITY, TASK2_PRIORITY, task2_stk,
					TASK_STACKSIZE, NULL, 0);

	OSTaskCreateExt(task3, NULL, &task3_stk[TASK_STACKSIZE-1],
					TASK3_PRIORITY, TASK3_PRIORITY, task3_stk,
					TASK_STACKSIZE, NULL, 0);

	OSTaskCreateExt(task4, NULL, &task4_stk[TASK_STACKSIZE-1],
					TASK4_PRIORITY, TASK4_PRIORITY, task4_stk,
					TASK_STACKSIZE, NULL, 0);

	OSStart();  /* Inicia el scheduler de uCOS-II */

	return 0;
}
```

> **Nota:** `OSTimeDlyHMSM(h, m, s, ms)` suspende la tarea el tiempo indicado en horas, minutos, segundos y milisegundos. `OSStart()` arranca el scheduler y no retorna nunca.

### Cuestiones

- ¿Qué servicios son necesarios para crear una tarea?
- ¿Qué elementos necesita una tarea para ser creada?
- ¿Cuándo se inicia el scheduler de tareas de UCOS y las tareas empiezan a funcionar?

[Volver a Índice](index.md)
