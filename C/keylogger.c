#include<termios.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define CTRL_KEY(k) ((k) & 0x1f)

struct termios orig;

void disableRawMode() {
    tcsetattr(STDERR_FILENO, TCSAFLUSH, &orig);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig);
    atexit(disableRawMode);

    struct termios raw = orig;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void processKeyPress() {

    char c;
    while(1) {
        read(STDIN_FILENO, &c, 1);
        if(c == CTRL_KEY('q')) exit(0);
        printf("%d ['%c']\n", c, c);
    }
}

int main() {
    
    enableRawMode();

    processKeyPress();

    return 0;
}