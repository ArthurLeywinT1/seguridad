# Keylogger en C

Este es un keylogger simple escrito en C para sistemas operativos basados en Linux. Captura y registra las teclas presionadas en un archivo de texto. Está diseñado para propósitos de monitoreo y depuración.

## Instrucciones de Uso

  1. Preparación del Entorno
    Antes de ejecutar el programa requisitos
    Sistema Operativo: Linux 
    Permisos de Superusuario

  2. Compilación del Programa
      Instalación del Compilador C:
      Si no tienes un compilador de C instalado, puedes instalar gcc (GNU Compiler Collection) ejecutando: sudo apt-get install gcc
      En otras distribuciones de Linux, usa el gestor de paquetes correspondiente.
      Compilación del Código:
      Coloca el archivo keylogger.c en un directorio de tu elección.
      Abre una terminal y navega hasta el directorio donde se encuentra el archivo keylogger.c.
      Compila el programa usando el siguiente comando: gcc -o keylogger keylogger.c
      Esto generará un ejecutable llamado keylogger en el mismo directorio.
  
  3. Ejecución del Programa
       Ejecutar como Superusuario:
       Debido a que el programa necesita acceso a dispositivos de entrada que solo están disponibles para el superusuario, ejecuta el programa con sudo:./keylogger
       Verificar la Salida:
       Una vez que el programa esté ejecutándose, comenzará a capturar todas las teclas presionadas en el sistema.
       El programa creará un archivo de texto llamado keylogger.txt en la ubicación especificada por LOGFILEPATH 
       Todas las teclas presionadas se registrarán en este archivo en tiempo real.
  
  4. Finalización del Programa
      Detener el Keylogger:
      Para detener el keylogger, simplemente presiona Ctrl+C en la terminal donde está ejecutándose. Esto terminará el proceso.
  
  5. Análisis de la Salida
      Revisar el Log:
      Abre el archivo keylogger.txt en cualquier editor de texto para revisar las teclas que se han registrado.
      Cada tecla presionada se registra tal como fue ingresada, incluyendo mayúsculas, caracteres especiales, y teclas como Enter, Backspace, y Tab.
  
  6. Limpieza
      Eliminar el Ejecutable:
      Si deseas eliminar el programa, simplemente borra el archivo keylogger generado y cualquier archivo de registro creado: rm keylogger keylogger.txt
     
