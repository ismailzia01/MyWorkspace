#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include<ctype.h>      // Provides character handling functions (e.g., isalpha, isdigit)
#include<errno.h>      // Defines macros for reporting and retrieving error conditions through error codes
#include<fcntl.h>
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
#define KILO_QUIT_TIMES 3

enum editorKey {
    BACKSPACE = 127,
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

enum editorHighlight {
    HL_NORMAL = 0,
    HL_COMMENT,
    HL_MLCOMMENT,
    HL_KEYWORD1,
    HL_KEYWORD2,
    HL_STRING,
    HL_NUMBER,
    HL_MATCH
};

#define HL_HIGHLIGHT_NUMBERS (1<<0)
#define HL_HIGHLIGHT_STRINGS (1<<1)

/***data***/

struct editorSyntax {
    char *filetype;
    char **filematch;
    char **keywords;
    char *singleline_comment_start;
    char *multiline_comment_start;
    char *multiline_comment_end;
    int flags;
};

typedef struct erow {
    int idx;
    int size; 
    int rsize;
    char *chars;
    char *render;
    unsigned char *hl;
    int hl_open_comment;
}erow;

struct editorConfig {
    int cx, cy, rx;                  // Cursor x (column) and y (row) position in the editor
    int rowoff;
    int coloff;
    int screenrows;              // Number of rows visible in the terminal window
    int screencols;   
    int numrows;
    erow *row;           // Number of columns visible in the terminal window
    int dirty;           // Flag to track if file has been modified
    char *filename;
    char statusmsg[80];
    time_t statusmsg_time;
    struct editorSyntax *syntax;
    struct termios orig_termios; // Stores original terminal attributes to restore on exit
};

struct editorConfig E;           // Global instance holding the editor's current state

/***filetypes***/

char *C_HL_extensions[] = { ".c", ".h", ".cpp", NULL };
char *C_HL_keywords[] = {
    "switch", "if", "while", "for", "break", "continue", "return", "else",
    "struct", "union", "typedef", "static", "enum", "class", "case",

    "int|", "long|", "double|", "float|", "char|", "unsigned|", "signed|",
    "void|", NULL
};

struct editorSyntax HLDB[] = {
    {
        "c",
        C_HL_extensions,
        C_HL_keywords,
        "//", "/*", "*/",
        HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS
    },
};

#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))

/***prototypes ***/
void editorSetStatusMessage(const char *fmt, ...);
void editorRefreshScreen();
char *editorPrompt(char *prompt, void (*callback)(char *, int));

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
}

int getCursorPosition(int *rows, int *columns) { // Gets current cursor position from terminal
    char buf[32];                // Buffer to store response from terminal
    unsigned int i = 0;          // Index for buffer
    if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1; // Requests cursor position report

    while(i < sizeof(buf) - 1) { // Reads response into buffer
        if(read(STDIN_FILENO, &buf[i], 1) != 1) break;
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

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) { // Fallback if ioctl fails
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1; // Moves cursor to bottom-right
        return getCursorPosition(rows, columns); // Gets actual position
    } else {
        *columns = ws.ws_col;    // Sets columns from ioctl
        *rows = ws.ws_row;       // Sets rows from ioctl
        return 0;                // Success
    }
}

/***syntax highlighting***/

int is_separator(int c) {
    return isspace(c) || c == '\0' || strchr(",.()+-/*=~%<>[];", c) != NULL;
}

void editorUpdateSyntax(erow *row) {
    row->hl = realloc(row->hl, row->rsize);
    memset(row->hl, HL_NORMAL, row->rsize);

    if (E.syntax == NULL) return;

    char **keywords = E.syntax->keywords;

    char *scs = E.syntax->singleline_comment_start;
    char *mcs = E.syntax->multiline_comment_start;
    char *mce = E.syntax->multiline_comment_end;

    int scs_len = scs ? strlen(scs) : 0;
    int mcs_len = mcs ? strlen(mcs) : 0;
    int mce_len = mce ? strlen(mce) : 0;

    int prev_sep = 1;
    int in_string = 0;
    int in_comment = (row->idx > 0 && E.row[row->idx - 1].hl_open_comment);

    int i = 0;
    while (i < row->rsize) {
        char c = row->render[i];
        unsigned char prev_hl = (i > 0) ? row->hl[i - 1] : HL_NORMAL;

        if (scs_len && !in_string && !in_comment) {
            if (!strncmp(&row->render[i], scs, scs_len)) {
                memset(&row->hl[i], HL_COMMENT, row->rsize - i);
                break;
            }
        }

        if (mcs_len && mce_len && !in_string) {
            if (in_comment) {
                row->hl[i] = HL_MLCOMMENT;
                if (!strncmp(&row->render[i], mce, mce_len)) {
                    memset(&row->hl[i], HL_MLCOMMENT, mce_len);
                    i += mce_len;
                    in_comment = 0;
                    prev_sep = 1;
                    continue;
                } else {
                    i++;
                    continue;
                }
            } else if (!strncmp(&row->render[i], mcs, mcs_len)) {
                memset(&row->hl[i], HL_MLCOMMENT, mcs_len);
                i += mcs_len;
                in_comment = 1;
                continue;
            }
        }

        if (E.syntax->flags & HL_HIGHLIGHT_STRINGS) {
            if (in_string) {
                row->hl[i] = HL_STRING;
                if (c == '\\' && i + 1 < row->rsize) {
                    row->hl[i + 1] = HL_STRING;
                    i += 2;
                    continue;
                }
                if (c == in_string) in_string = 0;
                i++;
                prev_sep = 1;
                continue;
            } else {
                if (c == '"' || c == '\'') {
                    in_string = c;
                    row->hl[i] = HL_STRING;
                    i++;
                    continue;
                }
            }
        }

        if (E.syntax->flags & HL_HIGHLIGHT_NUMBERS) {
            if ((isdigit(c) && (prev_sep || prev_hl == HL_NUMBER)) ||
                (c == '.' && prev_hl == HL_NUMBER)) {
                row->hl[i] = HL_NUMBER;
                i++;
                prev_sep = 0;
                continue;
            }
        }

        if (prev_sep) {
            int j;
            for (j = 0; keywords[j]; j++) {
                int klen = strlen(keywords[j]);
                int kw2 = keywords[j][klen - 1] == '|';
                if (kw2) klen--;

                if (!strncmp(&row->render[i], keywords[j], klen) &&
                    is_separator(row->render[i + klen])) {
                    memset(&row->hl[i], kw2 ? HL_KEYWORD2 : HL_KEYWORD1, klen);
                    i += klen;
                    break;
                }
            }
            if (keywords[j] != NULL) {
                prev_sep = 0;
                continue;
            }
        }

        prev_sep = is_separator(c);
        i++;
    }

    int changed = (row->hl_open_comment != in_comment);
    row->hl_open_comment = in_comment;
    if (changed && row->idx + 1 < E.numrows)
        editorUpdateSyntax(&E.row[row->idx + 1]);
}

int editorSyntaxToColor(int hl) {
    switch (hl) {
        case HL_COMMENT:
        case HL_MLCOMMENT: return 36;
        case HL_KEYWORD1: return 33;
        case HL_KEYWORD2: return 32;
        case HL_STRING: return 35;
        case HL_NUMBER: return 31;
        case HL_MATCH: return 34;
        default: return 37;
    }
}

void editorSelectSyntaxHighlight() {
    E.syntax = NULL;
    if (E.filename == NULL) return;

    char *ext = strrchr(E.filename, '.');

    for (unsigned int j = 0; j < HLDB_ENTRIES; j++) {
        struct editorSyntax *s = &HLDB[j];
        for (int i = 0; s->filematch[i]; i++) {
            int is_ext = (s->filematch[i][0] == '.');
            if ((is_ext && ext && !strcmp(ext, s->filematch[i])) ||
                (!is_ext && strstr(E.filename, s->filematch[i]))) {
                E.syntax = s;

                int filerow;
                for (filerow = 0; filerow < E.numrows; filerow++) {
                    editorUpdateSyntax(&E.row[filerow]);
                }

                return;
            }
        }
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

int editorRowRxToCx(erow *row, int rx) {
    int cur_rx = 0;
    int cx;
    for (cx = 0; cx < row->size; cx++) {
        if (row->chars[cx] == '\t')
            cur_rx += (KILO_TAB_STOP - 1) - (cur_rx % KILO_TAB_STOP);
        cur_rx++;

        if (cur_rx > rx) return cx;
    }
    return cx;
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

    editorUpdateSyntax(row);
}

void editorInsertRow(int at, char *s, size_t len) {
    if (at < 0 || at > E.numrows) return;

    E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));
    memmove(&E.row[at + 1], &E.row[at], sizeof(erow) * (E.numrows - at));
    for (int j = at + 1; j <= E.numrows; j++) E.row[j].idx++;

    E.row[at].idx = at;

    E.row[at].size = len;
    E.row[at].chars = malloc(len + 1);
    memcpy(E.row[at].chars, s, len);
    E.row[at].chars[len] = '\0';

    E.row[at].rsize = 0;
    E.row[at].render = NULL;
    E.row[at].hl = NULL;
    E.row[at].hl_open_comment = 0;
    editorUpdateRow(&E.row[at]);

    E.numrows++;
    E.dirty++;
}

void editorFreeRow(erow *row) {
    free(row->render);
    free(row->chars);
    free(row->hl);
}

void editorDelRow(int at) {
    if (at < 0 || at >= E.numrows) return;
    editorFreeRow(&E.row[at]);
    memmove(&E.row[at], &E.row[at + 1], sizeof(erow) * (E.numrows - at - 1));
    for (int j = at; j < E.numrows - 1; j++) E.row[j].idx--;
    E.numrows--;
    E.dirty++;
}

void editorRowInsertChar(erow *row, int at, int c) {
    if(at < 0 || at > row->size) at = row->size;
    row->chars = realloc(row->chars, row->size + 2);
    memmove(&row->chars[at + 1], &row->chars[at], row->size -at + 1);
    row->size++;
    row->chars[at] = c;
    editorUpdateRow(row);
    E.dirty++;
}

void editorRowAppendString(erow *row, char *s, size_t len) {
    row->chars = realloc(row->chars, row->size + len + 1);
    memcpy(&row->chars[row->size], s, len);
    row->size += len;
    row->chars[row->size] = '\0';
    editorUpdateRow(row);
    E.dirty++;
}

void editorRowDelChar(erow *row, int at) {
    if (at < 0 || at >= row->size) return;
    memmove(&row->chars[at], &row->chars[at + 1], row->size - at);
    row->size--;
    editorUpdateRow(row);
    E.dirty++;
}

/***editor operations ***/
void editorInsertChar(int c) {
    if(E.cy == E.numrows) {
        editorInsertRow(E.numrows, "", 0);
    }
    editorRowInsertChar(&E.row[E.cy], E.cx, c);
    E.cx++;
}

void editorInsertNewline() {
    if (E.cx == 0) {
        editorInsertRow(E.cy, "", 0);
    } else {
        erow *row = &E.row[E.cy];
        editorInsertRow(E.cy + 1, &row->chars[E.cx], row->size - E.cx);
        row = &E.row[E.cy];
        row->size = E.cx;
        row->chars[row->size] = '\0';
        editorUpdateRow(row);
    }
    E.cy++;
    E.cx = 0;
}

void editorDelChar() {
    if (E.cy == E.numrows) return;
    if (E.cx == 0 && E.cy == 0) return;

    erow *row = &E.row[E.cy];
    if (E.cx > 0) {
        editorRowDelChar(row, E.cx - 1);
        E.cx--;
    } else {
        E.cx = E.row[E.cy - 1].size;
        editorRowAppendString(&E.row[E.cy - 1], row->chars, row->size);
        editorDelRow(E.cy);
        E.cy--;
    }
}

/***file i/o***/

char *editorRowsToString(int *buflen) {
    int totlen = 0;
    int j;
    for(j = 0; j < E.numrows; j++) 
        totlen += E.row[j].size + 1;
    *buflen = totlen;

    char *buf = malloc(totlen);
    char *p = buf;
    for(j = 0; j < E.numrows; j++) {
        memcpy(p, E.row[j].chars, E.row[j].size);
        p += E.row[j].size;
        *p = '\n';
        p++;
    }

    return buf;
}

void editorOpen(char *filename) {
    free(E.filename);
    E.filename = strdup(filename);

    editorSelectSyntaxHighlight();

    FILE *fp = fopen(filename, "r");
    if(!fp) die("fopen");
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen ;// Length of the line including null terminator
    //linelen = getline(&line, &linecap, fp);
    while((linelen = getline(&line, &linecap, fp)) != -1){
        while(linelen > 0 && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
            linelen--;
        
        editorInsertRow(E.numrows, line, linelen);
    }
    free(line);
    fclose(fp);
    E.dirty = 0;
}

void editorSave() {
    if (E.filename == NULL) {
        E.filename = editorPrompt("Save as: %s (ESC to cancel)", NULL);
        if (E.filename == NULL) {
            editorSetStatusMessage("Save aborted");
            return;
        }
        editorSelectSyntaxHighlight();
    }

    int len;
    char *buf = editorRowsToString(&len);

    int fd = open(E.filename, O_RDWR | O_CREAT, 0644);
    if(fd != -1){
        if(ftruncate(fd, len) != -1) {
            if(write(fd, buf, len) == len) {
                close(fd);
                free(buf);
                E.dirty = 0;
                editorSetStatusMessage("%d bytes written to disk", len);
                return;
            }
        }
        close(fd);
    }
    free(buf);
    editorSetStatusMessage("Can't save! I/O error: %s", strerror(errno));
}

/***find***/

void editorFindCallback(char *query, int key) {
    static int last_match = -1;
    static int direction = 1;

    static int saved_hl_line;
    static char *saved_hl = NULL;

    if (saved_hl) {
        memcpy(E.row[saved_hl_line].hl, saved_hl, E.row[saved_hl_line].rsize);
        free(saved_hl);
        saved_hl = NULL;
    }

    if (key == '\r' || key == '\x1b') {
        last_match = -1;
        direction = 1;
        return;
    } else if (key == ARROW_RIGHT || key == ARROW_DOWN) {
        direction = 1;
    } else if (key == ARROW_LEFT || key == ARROW_UP) {
        direction = -1;
    } else {
        last_match = -1;
        direction = 1;
    }

    if (last_match == -1) direction = 1;
    int current = last_match;
    int i;
    for (i = 0; i < E.numrows; i++) {
        current += direction;
        if (current == -1) current = E.numrows - 1;
        else if (current == E.numrows) current = 0;

        erow *row = &E.row[current];
        char *match = strstr(row->render, query);
        if (match) {
            last_match = current;
            E.cy = current;
            E.cx = editorRowRxToCx(row, match - row->render);
            E.rowoff = E.numrows;

            saved_hl_line = current;
            saved_hl = malloc(row->rsize);
            memcpy(saved_hl, row->hl, row->rsize);
            memset(&row->hl[match - row->render], HL_MATCH, strlen(query));
            break;
        }
    }
}

void editorFind() {
    int saved_cx = E.cx;
    int saved_cy = E.cy;
    int saved_coloff = E.coloff;
    int saved_rowoff = E.rowoff;

    char *query = editorPrompt("Search: %s (Use ESC/Arrows/Enter)", 
                              editorFindCallback);
    
    if (query) {
        free(query);
    } else {
        E.cx = saved_cx;
        E.cy = saved_cy;
        E.coloff = saved_coloff;
        E.rowoff = saved_rowoff;
    }
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

            char *c = &E.row[filerow].render[E.coloff];
            unsigned char *hl = &E.row[filerow].hl[E.coloff];
            int current_color = -1;
            int j;
            for (j = 0; j < len; j++) {
                if (iscntrl(c[j])) {
                    char sym = (c[j] <= 26) ? '@' + c[j] : '?';
                    abAppend(ab, "\x1b[7m", 4);
                    abAppend(ab, &sym, 1);
                    abAppend(ab, "\x1b[m", 3);
                    if (current_color != -1) {
                        char buf[16];
                        int clen = snprintf(buf, sizeof(buf), "\x1b[%dm", current_color);
                        abAppend(ab, buf, clen);
                    }
                } else if (hl[j] == HL_NORMAL) {
                    if (current_color != -1) {
                        abAppend(ab, "\x1b[39m", 5);
                        current_color = -1;
                    }
                    abAppend(ab, &c[j], 1);
                } else {
                    int color = editorSyntaxToColor(hl[j]);
                    if (color != current_color) {
                        current_color = color;
                        char buf[16];
                        int clen = snprintf(buf, sizeof(buf), "\x1b[%dm", color);
                        abAppend(ab, buf, clen);
                    }
                    abAppend(ab, &c[j], 1);
                }
            }
            abAppend(ab, "\x1b[39m", 5);
        }
        
        abAppend(ab, "\x1b[K", 3); // Clears line from cursor to end
        abAppend(ab, "\r\n", 2); // Adds newline except for last row
        }
}

void editorDrawStatusBar(struct abuf *ab) {
    abAppend(ab, "\x1b[7m", 4);
    char status[80], rstatus[80];
    int len = snprintf(status, sizeof(status), "%.20s - %d lines %s", 
                       E.filename ? E.filename: "[No Name]", E.numrows,
                       E.dirty ? "(modified)" : "");
    int rlen = snprintf(rstatus, sizeof(rstatus), "%s | %d/%d", 
                        E.syntax ? E.syntax->filetype : "no ft", E.cy + 1, E.numrows);
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

char *editorPrompt(char *prompt, void (*callback)(char *, int)) {
    size_t bufsize = 128;
    char *buf = malloc(bufsize);

    size_t buflen = 0;
    buf[0] = '\0';

    while (1) {
        editorSetStatusMessage(prompt, buf);
        editorRefreshScreen();

        int c = editorReadKey();
        if (c == DEL_KEY || c == CTRL_KEY('h') || c == BACKSPACE) {
            if (buflen != 0) buf[--buflen] = '\0';
        } else if (c == '\x1b') {
            editorSetStatusMessage("");
            if (callback) callback(buf, c);
            free(buf);
            return NULL;
        } else if (c == '\r') {
            if (buflen != 0) {
                editorSetStatusMessage("");
                if (callback) callback(buf, c);
                return buf;
            }
        } else if (!iscntrl(c) && c < 128) {
            if (buflen == bufsize - 1) {
                bufsize *= 2;
                buf = realloc(buf, bufsize);
            }
            buf[buflen++] = c;
            buf[buflen] = '\0';
        }

        if (callback) callback(buf, c);
    }
}

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
        } else if(row && E.cx == row->size) {
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
    static int quit_times = KILO_QUIT_TIMES;

    int c = editorReadKey();   // Reads key from input

    switch(c) {
        case '\r':
            editorInsertNewline();
        break;
        
        case CTRL_KEY('q'): // CTRL-Q: quit editor
            if (E.dirty && quit_times > 0) {
                editorSetStatusMessage("WARNING!!! File has unsaved changes. "
                    "Press Ctrl-Q %d more times to quit.", quit_times);
                quit_times--;
                return;
            }
            write(STDOUT_FILENO, "\x1b[2J", 4); // Clears screen
            write(STDOUT_FILENO, "\x1b[H", 3);  // Moves cursor to top-left
            exit(0);                           // Exits program
            break;

        case CTRL_KEY('s'):
            editorSave();
            break;

        case HOME_KEY:
            E.cx = 0;
            break;
        case END_KEY:
            if(E.cy < E.numrows)
                E.cx = E.row[E.cy].size;
            break;

        case CTRL_KEY('f'):
            editorFind();
            break;

        case BACKSPACE:
        case CTRL_KEY('h'):
        case DEL_KEY:
            if (c == DEL_KEY) editorMoveCursor(ARROW_RIGHT);
            editorDelChar();
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

        case CTRL_KEY('l'):
        case '\x1b':
            break;
        default:
            editorInsertChar(c);
            break;
    }

    quit_times = KILO_QUIT_TIMES;
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
    E.dirty = 0;    // Initialize dirty flag
    E.filename = NULL;
    E.statusmsg[0] = '\0';
    E.statusmsg_time = 0;
    E.syntax = NULL;
    if(getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize"); // Gets terminal size
    E.screenrows -= 2;
}

int main(int argc, char *argv[]) { // Main entry point of the program
    enableRawMode(); // Enables raw mode for terminal input
    initEditor();    // Initializes editor state
    
    if(argc >= 2) {
        editorOpen(argv[1]);    // Opens a default line in the editor

    }

    editorSetStatusMessage("HELP: Ctrl-S = save | Ctrl-Q = quit | Ctrl-F = find");

    while(1) {       // Main loop
        editorRefreshScreen();   // Refreshes screen
        editorProcessKeypress(); // Processes user input
    }
    return 0;        // Program should never reach here
}
