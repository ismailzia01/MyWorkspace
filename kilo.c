#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include<ctype.h>      // Provides character handling functions (e.g., isalpha, isdigit)
#include<errno.h>      // Defines macros for reporting and retrieving error conditions through error codes
#include<stdio.h>      // Standard Input/Output functions (e.g., printf, scanf, FILE operations)
#include<stdarg.h>
#include<stdlib.h>     // Standard library functions (e.g., memory allocation, process control)
#include<string.h>     // String handling functions (e.g., strcpy, strlen, strcmp)
#include<sys/ioctl.h>  // Terminal control functions, used for getting terminal window size
#include<sys/types.h>  // Defines data types used in system calls (e.g., ssize_t, pid_t)
#include<termios.h>    // Terminal I/O interfaces, used for configuring terminal modes (raw/canonical)
#include<time.h>
#include<unistd.h>     // POSIX API, provides access to the POSIX operating system API (e.g., read, write, close)

/***defines***/
#define CTRL_KEY(k) ((k) & 0x1f) // Macro to convert character to its corresponding control key value (e.g., CTRL-Q)
#define KILO_VERSION "0.0.1"     // String literal representing the version of the Kilo editor
#define KILO_TAB_STOP 8
enum editorKey {
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

/***data***/

typedef struct erow {
    int size; 
    int rsize;
    char *chars;
    char *render;
}erow;
struct editorConfig {
    int cx, cy, rx;                  // Cursor x (column) and y (row) position in the editor
    int rowoff;
    int coloff;
    int screenrows;              // Number of rows visible in the terminal window
    int screencols;   
    int numrows;
    erow *row;           // Number of columns visible in the terminal window
    char *filename;
    char statusmsg[80];
    time_t statusmsg_time;
    struct termios orig_termios; // Stores original terminal attributes to restore on exit
};

struct editorConfig E;           // Global instance holding the editor's current state

/***terminal***/
void die(const char *s) {        // Handles fatal errors: clears screen, prints error, and exits
    write(STDOUT_FILENO, "\x1b[2J", 4); // ANSI escape code to clear the entire screen
    write(STDOUT_FILENO, "\x1b[H", 3);  // ANSI escape code to move cursor to top-left
    perror(s);                          // Prints error message describing the last error
    exit(1);                            // Exits the program with error code 1
}

void disableRawMode() {          // Restores terminal to its original mode (canonical, echo, etc.)
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {           // Sets terminal to raw mode (no echo, no canonical mode, etc.)
    if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr"); // Gets current terminal attributes
    atexit(disableRawMode);      // Ensures terminal is restored when program exits

    struct termios raw = E.orig_termios; // Copy of original terminal settings
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); // Disables various input flags
    raw.c_oflag &= ~(OPOST);     // Disables all output processing
    raw.c_cflag |= (CS8);        // Sets character size to 8 bits per byte
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); // Disables echo, canonical mode, extended input, and signals
    raw.c_cc[VMIN] = 0;          // Minimum number of bytes before read() returns
    raw.c_cc[VTIME] = 1;         // Maximum time to wait before read() returns (tenths of a second)

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr"); // Applies new terminal settings
}

int editorReadKey() {           // Reads a single keypress from standard input (stdin)
    int nread;                   // Number of bytes read
    char c;                      // Character read from input
    while((nread = read(STDIN_FILENO, &c, 1)) != 1) { // Reads one byte at a time until successful
        if(nread == -1 && errno != EAGAIN) die("read"); // Handles read errors except EAGAIN
    }

    if(c == '\x1b') { // If the key is an escape character, it may be an escape sequence
        char seq[3]; // Buffer to store escape sequence

        if(read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b'; // Read first byte of sequence
        if(read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b'; // Read second byte of sequence

        if(seq[0] == '[') { // CSI (Control Sequence Introducer)
            if(seq[1] >= '0' && seq[1] <= '9') { // Extended escape sequence
                if(read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b'; // Read third byte
                if(seq[2] == '~'){ // Check for tilde, which ends some sequences
                    switch(seq[1]){
                        case '1': return HOME_KEY;      // Home key
                        case '3': return DEL_KEY;       // Delete key
                        case '4': return END_KEY;       // End key
                        case '5': return PAGE_UP;       // Page up
                        case '6': return PAGE_DOWN;     // Page down
                        case '7': return HOME_KEY;      // Alternate home
                        case '8': return END_KEY;       // Alternate end
                    }
                }
            } else { // Arrow keys and other simple sequences
                switch(seq[1]) {
                    case 'A': return ARROW_UP;          // Up arrow
                    case 'B': return ARROW_DOWN;        // Down arrow
                    case 'C': return ARROW_RIGHT;       // Right arrow
                    case 'D': return ARROW_LEFT;        // Left arrow
                    case 'H': return HOME_KEY;          // Home key
                    case 'F': return END_KEY;           // End key
                }
            }
        } else if(seq[0] == 'O') { // Some terminals use 'O' for home/end
            switch(seq[1]){
                case 'H': return HOME_KEY;              // Home key
                case 'F': return END_KEY;               // End key
            }
        }
        return '\x1b'; // If not recognized, return escape character
    } else {
        return c; // Return regular character
    }

    return c; // Should not reach here, but return character as fallback
}

int getCursorPosition(int *rows, int *columns) { // Gets current cursor position from terminal
    char buf[32];                // Buffer to store response from terminal
    unsigned int i = 0;          // Index for buffer
    if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1; // Requests cursor position report

    while(i < sizeof(buf) - 1) { // Reads response into buffer
        if(read(STDOUT_FILENO, &buf[i], 1) != 1) break;
        if(buf[i] == 'R') break; // End of response
        i++;
    }

    buf[i] = '\0';               // Null-terminate buffer

    if (buf[0] != '\x1b' || buf[1] != '[') return -1; // Checks for valid response
    if (sscanf(&buf[2], "%d;%d", rows, columns) != 2) return -1; // Parses row and column
    return 0;                    // Success
}

int getWindowSize(int *rows, int *columns) { // Gets terminal window size (rows and columns)
    struct winsize ws;           // Structure to hold window size info

    if (1 || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) { // Fallback if ioctl fails
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1; // Moves cursor to bottom-right
        return getCursorPosition(rows, columns); // Gets actual position
    } else {
        *columns = ws.ws_col;    // Sets columns from ioctl
        *rows = ws.ws_row;       // Sets rows from ioctl
        return 0;                // Success
    }
}
/***row operations***/

int editorRowCxToRx(erow *row, int cx) {
    int rx = 0;
    int j;
    for(j = 0; j < cx; j++) {
        if(row->chars[j] == '\t') {
            rx += (KILO_TAB_STOP -1) - (rx % KILO_TAB_STOP);
        }
        rx++;
    }
    return rx;
}
void editorUpdateRow(erow *row) {
    int tabs = 0;
    int j;
    for(j = 0; j < row->size; j++) 
        if(row->chars[j] == '\t') tabs++;
    free(row->render);
    row->render = malloc(row->size + tabs*(KILO_TAB_STOP -1) + 1);
    
    int idx = 0;
    for(j = 0; j < row->size; j++) {
        if(row->chars[j] == '\t') {
            row->render[idx++] = ' ';
            while(idx % KILO_TAB_STOP != 0) row->render[idx++] = ' ';
        } else {
            row->render[idx++] = row->chars[j];
        }
    }
    row->render[idx] = '\0';
    row->rsize = idx;
}

void editorAppendRow(char *s, size_t len) {
    E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));
    int at = E.numrows;
    E.row[at].size = len;
    E.row[at].chars = malloc(len + 1);
    memcpy(E.row[at].chars, s, len);
    E.row[at].chars[len] = '\0';

    E.row[at].rsize = 0;
    E.row[at].render = NULL;
    editorUpdateRow(&E.row[at]);

    E.numrows++;
}

/***file i/o***/

void editorOpen(char *filename) {
    free(E.filename);
    E.filename = strdup(filename);
    FILE *fp = fopen(filename, "r");
    if(!fp) die("fopen");
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen ;// Length of the line including null terminator
    //linelen = getline(&line, &linecap, fp);
    while((linelen = getline(&line, &linecap, fp)) != -1){
        while(linelen > 0 && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
            linelen--;
        
        editorAppendRow(line, linelen);
    }
    free(line);
    fclose(fp);
    
}

/***append buffer***/
struct abuf {
    char *b;     // Pointer to dynamically allocated buffer
    int len;     // Current length of buffer
};

#define ABUF_INIT {NULL, 0} // Macro to initialize abuf structure

void abAppend(struct abuf *ab, const char *s, int len) { // Appends string s of length len to abuf
    char *new = realloc(ab->b, ab->len + len); // Reallocates buffer to fit new data

    if(new == NULL) return;      // Handles allocation failure
    memcpy(&new[ab->len], s, len); // Copies new data to end of buffer
    ab->b = new;                 // Updates buffer pointer
    ab->len += len;              // Updates buffer length
}

void abFree(struct abuf *ab) {   // Frees memory allocated for abuf
    free(ab->b);                 // Frees buffer
}

/***output***/
void editorScroll() {
    E.rx = 0;
    if(E.cy < E.numrows) {
        E.rx = editorRowCxToRx(&E.row[E.cy], E.cx);
    }
    if(E.cy < E.rowoff) {
        E.rowoff = E.cy;
    }
    if(E.cy >= E.rowoff + E.screenrows) {
        E.rowoff = E.cy - E.screenrows + 1;
    }
    if(E.rx < E.coloff) {
        E.coloff = E.rx;
    }
    if(E.rx >= E.coloff + E.screencols) {
        E.coloff = E.rx - E.screencols + 1;
    }
}
void editorDrawRows(struct abuf *ab) { // Draws each row of the editor to the append buffer
    int y;                      // Row index
    for(y = 0; y < E.screenrows; y++) {
        int filerow = y + E.rowoff;
        if(filerow >= E.numrows) {
            if(E.numrows == 0 && y == E.screenrows / 3) { // Displays welcome message at one-third down the screen
            char welcome[80];       // Buffer for welcome message
            int welcomelen = snprintf(welcome, sizeof(welcome),
            "Kilo editor -- version %s", KILO_VERSION); // Formats welcome message
            if(welcomelen > E.screencols) welcomelen = E.screencols; // Truncates if too long
            int padding = (E.screencols - welcomelen)/2; // Centers message
            if(padding) {
                abAppend(ab, "~", 1); // Adds tilde at start of line
                padding--;
            }
            while(padding--) abAppend(ab, " ", 1); // Adds spaces for centering
            abAppend(ab, welcome, welcomelen); // Adds welcome message
        } else {
            abAppend(ab, "~", 1); // Adds tilde for empty lines
            }
        } else {
            int len = E.row[filerow].rsize - E.coloff;
            if (len < 0) len = 0;
            if (len > E.screencols) len = E.screencols;
            abAppend(ab, &E.row[filerow].render[E.coloff], len);
        }
        
        abAppend(ab, "\x1b[K", 3); // Clears line from cursor to end
        abAppend(ab, "\r\n", 2); // Adds newline except for last row
        }
}

void editorDrawStatusBar(struct abuf *ab) {
    abAppend(ab, "\x1b[7m", 4);
    char status[80], rstatus[80];
    int len = snprintf(status, sizeof(status), "%.20s - %d lines", E.filename ? E.filename: "[No Name]", E.numrows);
    int rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d", E.cy + 1, E.numrows);
    if(len > E.screencols) len = E.screencols;
    abAppend(ab, status, len);
    while(len < E.screencols ) { 
        if(E.screencols - len == rlen) {
            abAppend(ab, rstatus, rlen);
            break;
        } else {
            abAppend(ab, " ", 1);
            len++;
        }
    }
    abAppend(ab, "\x1b[m", 3);
    abAppend(ab, "\r\n", 2);
}

void editorDrawMessageBar(struct abuf *ab) {
    abAppend(ab, "\x1b[K", 3);
    int msglen = strlen(E.statusmsg);
    if(msglen > E.screencols) msglen = E.screencols;
    if(msglen && time(NULL) - E.statusmsg_time < 5)
        abAppend(ab, E.statusmsg, msglen);
}

void editorRefreshScreen() { // Redraws the entire editor screen
    editorScroll();
    
    struct abuf ab = ABUF_INIT; // Initializes append buffer

    abAppend(&ab, "\x1b[?25l", 6); // Hides cursor
    abAppend(&ab, "\x1b[H", 3);    // Moves cursor to top-left

    editorDrawRows(&ab);           // Draws editor rows into buffer
    editorDrawStatusBar(&ab);
    editorDrawMessageBar(&ab);
    
    char buf[32];                  // Buffer for cursor position escape code
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (E.cy - E.rowoff) + 1, (E.rx- E.coloff) + 1); // Sets cursor position
    abAppend(&ab, buf, strlen(buf));

    abAppend(&ab, "\x1b[?25h", 6); // Shows cursor

    write(STDOUT_FILENO, ab.b, ab.len); // Writes buffer to terminal
    abFree(&ab);                        // Frees buffer memory
}

void editorSetStatusMessage(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(E.statusmsg, sizeof(E.statusmsg), fmt, ap);
    va_end(ap);
    E.statusmsg_time = time(NULL);
}

/***input***/
void editorMoveCursor(int key) { // Moves cursor in response to WASD keys
    erow *row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];
  
    switch (key) {
    case ARROW_LEFT: // Move left
    if(E.cx != 0) {
        E.cx--;
    } else if(E.cy > 0) {
        E.cy--;
        E.cx = E.row[E.cy].size;
    }
      break;
    case ARROW_RIGHT: // Move right 
        if(row && E.cx < row->size){
            E.cx++;
        } else if(row && E.cx < row->size) {
            E.cy++;
            E.cx = 0;
        }
        
      break;
    case ARROW_UP: // Move up
    if(E.cy != 0) {
        E.cy--;
    }
      break;
    case ARROW_DOWN: // Move down
    if(E.cy < E.numrows) {
        E.cy++;
    }
      break;
  }
  row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];
  int rowlen = row ? row->size : 0;
  if(E.cx > rowlen) {
    E.cx = rowlen;
  }

}

void editorProcessKeypress() { // Processes a single keypress from user
int c = editorReadKey();   // Reads key from input

    switch(c) {
        case CTRL_KEY('q'): // CTRL-Q: quit editor
            write(STDOUT_FILENO, "\x1b[2J", 4); // Clears screen
            write(STDOUT_FILENO, "\x1b[H", 3);  // Moves cursor to top-left
            exit(0);                           // Exits program
            break;

        case HOME_KEY:
            E.cx = 0;
            break;
        case END_KEY:
            if(E.cy < E.numrows)
                E.cx = E.row[E.cy].size;
            break;

        case PAGE_UP:
        case PAGE_DOWN:
            {
                if (c == PAGE_UP) {
                E.cy = E.rowoff;
                } else if (c == PAGE_DOWN) {
                E.cy = E.rowoff + E.screenrows - 1;
                if (E.cy > E.numrows) E.cy = E.numrows;
                }
                int times = E.screenrows;
                while(times--) {
                    editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
                }
            }
            break;
        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
            editorMoveCursor(c); // Moves cursor based on key
            break;
    }
}

/***init***/
void initEditor() { // Initializes editor state and gets terminal size
    E.cx = 0;       // Initializes cursor x position
    E.cy = 0;       // Initializes cursor y position
    E.rx = 0;
    E.rowoff = 0;
    E.coloff = 0;
    E.numrows = 0;  // Initializes number of rows in editor
    E.row = NULL;
    E.filename = NULL;
    E.statusmsg[0] = '\0';
    E.statusmsg_time = 0;
    if(getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize"); // Gets terminal size
    E.screenrows -= 2;
}

int main(int argc, char *argv[]) { // Main entry point of the program
    enableRawMode(); // Enables raw mode for terminal input
    initEditor();    // Initializes editor state
    
    if(argc >= 2) {
        editorOpen(argv[1]);    // Opens a default line in the editor

    }

    editorSetStatusMessage("HELP: Ctrl-Q = quit");

    while(1) {       // Main loop
        editorRefreshScreen();   // Refreshes screen
        editorProcessKeypress(); // Processes user input
    }
    return 0;        // Program should never reach here
}