#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<stdlib.h>

struct termios orig;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig);//get current terminal attributes
    atexit(disableRawMode);//autometically restore at exit

    struct termios raw = orig;
    raw.c_lflag &= ~(ICANON | ECHO);//turn of canonical mode
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);//set attributes immediately
}

int main() {
    enableRawMode();

    printf("press any key(Esc to exit) \n");
    char c;

    while(1) {
        read(STDIN_FILENO, &c, 1);
        if(c == 27) break;//Esc key
        printf("You pressed : '%c' (%d)\n",c, c);
    }

}