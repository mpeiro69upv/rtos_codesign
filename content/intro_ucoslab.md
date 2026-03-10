
## OBJETIVOS
En esta práctica vamos a abordar los fundamentos de trabajo de un sistema operativo en tiempo real –RTOS.
Las prácticas se fundamentan en el uso de MicroC/OS-II, también conocido como uCOSII.
En esta asignatura uCOSII se asocia con la arquitectura de un softcore o microprocesador software de Intel, conocido como NIOS.

Se sobreentiende que para la realización de la práctica el alumno está familiarizado con el diseño de microprocesadores NIOS y sus periféricos mediante las herramientas de Intel_FPGA Platform Designer.
Asimismo, es necesario conocer IDE de ECLIPSE de Intel_FPGA, donde desarrollaremos nuestros ejemplos de programación con RTOS.

Las prácticas de uCOSII están pensadas inicialmente para poder ser ejecutadas sobre una tarjeta DE1-SoC con un fichero .sopc que permita acceder a todos los recursos hardware de dicha tarjeta, es decir la FPGA no solo dispondrá de NIOSII como procesador sino que existirán el resto de periféricos asociados a drivers que permitan el acceso a los recursos como memoria (FLASH, DRAM,…), VGA, teclado, LCD, Ethernet, audio y resto de componentes de DE1-SoC.

Sin embargo, también es posible ejecutar las prácticas en un entorno de simulación utilizando ModelSim, lo que permite desarrollar y probar el código sin necesidad de hardware físico. Esta flexibilidad facilita el aprendizaje y la experimentación con conceptos de sistemas operativos en tiempo real.

### Objetivos específicos

- **Comprensión de conceptos RTOS**: Familiarizarse con los principios fundamentales de los sistemas operativos en tiempo real
- **Manejo de MicroC/OS-II**: Aprender a utilizar las funcionalidades principales del kernel uCOSII
- **Integración hardware-software**: Entender la interacción entre el RTOS y la arquitectura NIOS
- **Desarrollo práctico**: Crear aplicaciones multitarea con gestión de recursos compartidos

## INICIO DE LA SESIÓN
Inicialmente vamos a crear nuestro primer proyecto con uCOSII, denominado LAB_RTOS. 

1. Descargue los ficheros SOPCINFO y SOF desde PoliformaT. Inicie Quartus. Programe el dispositivo mediante el fichero DE1_SoC_Media_Computer.sof.
2. Inicie ECLIPSE desde QuartusII mediante Tools->NIOSII Software Build Tools for Eclipse, el workspace indicado debe ser /DE1_SoC_Media_Computer/software.
3. Desde ECLIPSE File->New->NiosII Application and BSP from Template. Cargue el fichero .sopcinfo proporcionado en la práctica.
4. Como nombre de proyecto escriba LAB_RTOS y como Template seleccione Hello MicroC/OS-II. Esta Template realiza la portabilidad de UCOS sobre nuestro proyecto NIOS.

Compile el proyecto LAB_RTOS y ejecútelo en la consola de NIOSII. Observe los mensajes que aparecen en consola: “Hello from Task1”..”Hello from Task2”.

[Volver a Índice](index.md)