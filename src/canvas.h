#ifndef CANVAS_H
#define CANVAS_H

#define CANVAS_WIDTH 80  // Set your canvas width
#define CANVAS_HEIGHT 24 // Set your canvas height

extern char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];  // Canvas array

extern int cursorX, cursorY;  // Cursor position

// Function declarations
void moveTo(int x, int y);
void lineTo(int x, int y);
void clearCanvas();
void getTerminalSize(int *width, int *height);
void initCanvas();
void renderCanvas();
void drawPoint(int x, int y, char ch);

#endif // CANVAS_H
