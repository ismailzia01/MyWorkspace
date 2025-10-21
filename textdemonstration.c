this is a demonstration of my project in C
This is my custom text editor written in C.  
It's a lightweight version inspired by the Kilo editor — a very minimal form of Vim.  

It took me 3 weeks and several small programs to build this project,  
helping me learn terminal control, input handling, and memory management.  

🔹 Features:
- Runs entirely inside the terminal  
- Raw mode input (no line buffering)  
- Real-time screen rendering  
- Cursor movement and scrolling  
- Supports text editing and file saving  
- Clean and minimal interface  

🔹 Core Functions Implemented:
- enableRawMode() / disableRawMode() – for low-level terminal control  
- editorReadKey() – to handle keypress inputs  
- editorProcessKeypress() – to manage user commands  
- editorDrawRows() – for dynamic screen rendering  
- editorRefreshScreen() – to update the display efficiently  
- editorOpen() / editorSave() – for file handling  
- abAppend() – for building output buffer dynamically  

This project was purely for learning — to strengthen my knowledge of  
C, terminal I/O, and system programming concepts.

