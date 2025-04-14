#ifndef CANVAS_H
#define CANVAS_H

#define MAX_UNDO_REDO 100

// Canvas dimensions
extern char **canvas; // Pointer to dynamically allocated canvas
extern int canvasWidth, canvasHeight; // Current canvas dimensions
extern int cursorX, cursorY; // Cursor position

// Undo/Redo stacks
extern char ***undoStack; // Pointer to dynamically allocated undo stack
extern char ***redoStack; // Pointer to dynamically allocated redo stack
extern int undoTop;
extern int redoTop;

// Function declarations
void initCanvas();
void freeCanvas();
void renderCanvas(int clearScreen);
void clearCanvas();
void drawPoint(int x, int y, char ch);
void moveTo(int x, int y);
void lineTo(int x, int y);
void pushUndo();
void undo();
void redo();
void initUndoRedoStacks();
void freeUndoRedoStacks();
void getTerminalSize(int *width, int *height);
void drawRectangle(int x, int y, int width, int height);
void drawCircle(int x, int y, int radius);
void pushSnapshot(); // Pushes the current canvas state to the undo stack
void restoreSnapshot(char ***snapshot); // Restores a canvas state from a snapshot
void exportCanvas(const char *filename);
void importCanvas(const char *filename);
void fillRectangle(int x, int y, int width, int height);
void fillCircle(int x, int y, int radius);
void clearRect(int x, int y, int width, int height);
void writeText(int x, int y, const char *text);

#endif // CANVAS_H
