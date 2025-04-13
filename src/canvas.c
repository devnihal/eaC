#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "canvas.h"

char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];

int cursorX = 0, cursorY = 0;

// Function to move cursor to (x, y)
void moveTo(int x, int y) {
    cursorX = x;
    cursorY = y;
}

// Function to draw a line from the current position to (x, y)
void lineTo(int x, int y) {
    int dx = abs(x - cursorX);
    int dy = abs(y - cursorY);
    int sx = cursorX < x ? 1 : -1;
    int sy = cursorY < y ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // Draw at the current cursor position
        if (cursorX >= 0 && cursorX < CANVAS_WIDTH && cursorY >= 0 && cursorY < CANVAS_HEIGHT) {
            canvas[cursorY][cursorX] = '*';  // Draw point
        }

        if (cursorX == x && cursorY == y) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            cursorX += sx;
        }
        if (e2 < dx) {
            err += dx;
            cursorY += sy;
        }
    }
}

// Function to clear the canvas
void clearCanvas() {
    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            canvas[i][j] = ' ';
        }
    }
}

// Function to get the terminal size (for Windows)
void getTerminalSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *width = csbi.dwSize.X;  // Console width
        *height = csbi.dwSize.Y; // Console height
    }
}

// Function to initialize the canvas based on terminal size
void initCanvas() {
    int termWidth, termHeight;
    getTerminalSize(&termWidth, &termHeight);

    // Adjust height to leave space for the command prompt
    int adjustedHeight = termHeight - 1;

    for (int i = 0; i < adjustedHeight; i++) {
        for (int j = 0; j < termWidth; j++) {
            canvas[i][j] = ' ';
        }
    }
}

// Function to render (display) the canvas in the terminal
void renderCanvas() {
    int termWidth, termHeight;
    getTerminalSize(&termWidth, &termHeight);

    // Adjust height to leave space for the command prompt
    int adjustedHeight = termHeight - 2;

    system("cls||clear");  // Clear terminal (works on both Windows and Unix)

    for (int i = 0; i < adjustedHeight; i++) {
        for (int j = 0; j < termWidth; j++) {
            putchar(canvas[i][j]);
        }
        putchar('\n');
    }
}

// Function to draw a single point at (x, y) with character `ch`
void drawPoint(int x, int y, char ch) {
    if (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
        canvas[y][x] = ch;
    }
}
