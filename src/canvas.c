#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "canvas.h"
#include <ctype.h> // For character case conversion

char **canvas = NULL; // Pointer to dynamically allocated canvas
int canvasWidth = 0, canvasHeight = 0; // Current canvas dimensions
int cursorX = 0, cursorY = 0;

// Undo/Redo stacks
char ***undoStack = NULL;
char ***redoStack = NULL;
int undoTop = -1;
int redoTop = -1;

// Define 5x5 character patterns for alphanumeric and some special characters
const int CHAR_WIDTH = 5;
const int CHAR_HEIGHT = 5;

const int CHAR_MAP[128][5][5] = {
    // Default empty character (space)
    [' '] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
    // Letter A
    ['A'] = {
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
    },
    // Letter B
    ['B'] = {
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 0},
    },
    // Letter C
    ['C'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    // Letter D
    ['D'] = {
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
    },
    // Letter E
    ['E'] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
    },
    // Letter F
    ['F'] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
    },
    // Letter G
    ['G'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    // Letter H
    ['H'] = {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
    },
    // Letter I
    ['I'] = {
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
    },
    // Letter J
    ['J'] = {
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    // Letter K
    ['K'] = {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1},
    },
    // Letter L
    ['L'] = {
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
    },
    // Letter M
    ['M'] = {
        {1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
    },
    // Letter N
    ['N'] = {
        {1, 0, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1},
    },
    // Letter O
    ['O'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    // Letter P
    ['P'] = {
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
    },
    // Letter Q
    ['Q'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {0, 1, 1, 1, 1},
    },
    // Letter R
    ['R'] = {
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 0},
        {1, 0, 1, 0, 0},
        {1, 0, 0, 1, 0},
    },
    // Letter S
    ['S'] = {
        {0, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0},
    },
    // Letter T
    ['T'] = {
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
    },
    // Letter U
    ['U'] = {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    // Letter V
    ['V'] = {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
    },
    // Letter W
    ['W'] = {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 1},
        {1, 0, 0, 0, 1},
    },
    // Letter X
    ['X'] = {
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
    },
    // Letter Y
    ['Y'] = {
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
    },
    // Letter Z
    ['Z'] = {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {1, 1, 1, 1, 1},
    },
    // Number 0
    ['0'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    // Number 1
    ['1'] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
    },
    // Number 2
    ['2'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
    },
    // Number 3
    ['3'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 0, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    // Number 4
    ['4'] = {
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0},
    },
    // Number 5
    ['5'] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0},
    },
    // Number 6
    ['6'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    // Number 7
    ['7'] = {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
    },
    // Number 8
    ['8'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    // Number 9
    ['9'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    // Special Character @
    ['@'] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 1, 1, 1},
    },
    ['('] = {
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
    },
    [')'] = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
    },
    [','] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
    },
    ['.'] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
    },
    ['+'] = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
    },
    ['-'] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
    ['*'] = {
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
    },
    ['/'] = {
        {0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
    },
    // Special Character #
    ['#'] = {
        {0, 1, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 0, 1, 0},
    },
    // Special Character $
    ['$'] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
    },
    // Special Character %
    ['%'] = {
        {1, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
    },
    // Special Character &
    ['&'] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 1},
    },
    // Special Character !
    ['!'] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
    },
    // Special Character ?
    ['?'] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
    },
    // Add more characters as needed...
};

void freeCanvas() {
    if (canvas) {
        for (int i = 0; i < canvasHeight; i++) {
            free(canvas[i]);
        }
        free(canvas);
        canvas = NULL;
    }
}

void initCanvas() {
    int termWidth, termHeight;
    getTerminalSize(&termWidth, &termHeight);

    // Leave one row for command input
    termHeight -= 2;

    // Free the previous canvas if it exists
    freeCanvas();

    // Allocate memory for the new canvas
    canvasWidth = termWidth;
    canvasHeight = termHeight;
    canvas = (char **)malloc(canvasHeight * sizeof(char *));
    for (int i = 0; i < canvasHeight; i++) {
        canvas[i] = (char *)malloc(canvasWidth * sizeof(char));
    }

    // Initialize the canvas with spaces
    for (int i = 0; i < canvasHeight; i++) {
        for (int j = 0; j < canvasWidth; j++) {
            canvas[i][j] = ' ';
        }
    }
}

void renderCanvas(int clearScreen) {
    if (clearScreen) {
        system("cls||clear"); // Clear terminal on Windows or Unix
    }

    for (int i = 0; i < canvasHeight; i++) {
        for (int j = 0; j < canvasWidth; j++) {
            putchar(canvas[i][j]);
        }
        putchar('\n');
    }
}

void clearCanvas() {
    for (int i = 0; i < canvasHeight; i++) {
        for (int j = 0; j < canvasWidth; j++) {
            canvas[i][j] = ' '; // Clear the canvas (set all positions to space)
        }
    }
    cursorX = cursorY = 0; // Reset the cursor position
}

void drawPoint(int x, int y, char ch) {
    if (x >= 0 && x < canvasWidth && y >= 0 && y < canvasHeight) {
        canvas[y][x] = ch;
    }
}


void getTerminalSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *width = csbi.dwSize.X;  // Console width
        *height = csbi.dwSize.Y; // Console height
    }
}

void moveTo(int x, int y) {
    pushSnapshot();  // Save current canvas state before moving
    cursorX = x;
    cursorY = y / 2; // Adjust vertical scale for 1:2 aspect ratio
}

void lineTo(int x, int y) {
    printf("Drawing line from (%d, %d) to (%d, %d)\n", cursorX, cursorY * 2, x, y);

    y /= 2; // Adjust vertical scale for 1:2 aspect ratio
    int dx = abs(x - cursorX);
    int dy = abs(y - cursorY);
    int sx = (cursorX < x) ? 1 : -1;
    int sy = (cursorY < y) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        if (cursorX >= 0 && cursorX < canvasWidth && cursorY >= 0 && cursorY < canvasHeight) {
            canvas[cursorY][cursorX] = '*';
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

    cursorX = x;
    cursorY = y;
    // printf("Updated cursor to: (%d, %d)\n", cursorX, cursorY);
}

void pushSnapshot() {
    if (undoTop < MAX_UNDO_REDO - 1) {
        // Clear the redo stack when a new command is executed
        for (int i = 0; i <= redoTop; i++) {
            for (int j = 0; j < canvasHeight; j++) {
                free(redoStack[i][j]);
            }
            free(redoStack[i]);
        }
        redoTop = -1;

        // Save the current canvas state to the undo stack
        undoTop++;
        undoStack[undoTop] = (char **)malloc(canvasHeight * sizeof(char *));
        for (int i = 0; i < canvasHeight; i++) {
            undoStack[undoTop][i] = (char *)malloc(canvasWidth * sizeof(char));
            memcpy(undoStack[undoTop][i], canvas[i], canvasWidth * sizeof(char));
        }
    } else {
        printf("Undo stack is full. Cannot save more states.\n");
    }
}

void restoreSnapshot(char ***snapshot) {
    for (int i = 0; i < canvasHeight; i++) {
        memcpy(canvas[i], snapshot[i], canvasWidth * sizeof(char));
    }
}

void undo() {
    if (undoTop >= 0) { // Ensure there is a state to undo to
        // Save the current canvas state to the redo stack
        if (redoTop < MAX_UNDO_REDO - 1) {
            redoStack[++redoTop] = (char **)malloc(canvasHeight * sizeof(char *));
            for (int i = 0; i < canvasHeight; i++) {
                redoStack[redoTop][i] = (char *)malloc(canvasWidth * sizeof(char));
                memcpy(redoStack[redoTop][i], canvas[i], canvasWidth * sizeof(char));
            }
        }

        // Restore the canvas state from the undo stack
        restoreSnapshot(undoStack[undoTop]);

        // Free the restored state from the undo stack
        for (int i = 0; i < canvasHeight; i++) {
            free(undoStack[undoTop][i]);
        }
        free(undoStack[undoTop]);
        undoStack[undoTop--] = NULL; // Decrement undoTop and clear the pointer
    } else {
        printf("No more actions to undo.\n");
    }
}

void redo() {
    if (redoTop >= 0) { // Ensure there is a state to redo to
        // Save the current canvas state to the undo stack
        if (undoTop < MAX_UNDO_REDO - 1) {
            undoStack[++undoTop] = (char **)malloc(canvasHeight * sizeof(char *));
            for (int i = 0; i < canvasHeight; i++) {
                undoStack[undoTop][i] = (char *)malloc(canvasWidth * sizeof(char));
                memcpy(undoStack[undoTop][i], canvas[i], canvasWidth * sizeof(char));
            }
        }

        // Restore the canvas state from the redo stack
        restoreSnapshot(redoStack[redoTop]);

        // Free the restored state from the redo stack
        for (int i = 0; i < canvasHeight; i++) {
            free(redoStack[redoTop][i]);
        }
        free(redoStack[redoTop]);
        redoStack[redoTop--] = NULL; // Decrement redoTop and clear the pointer
    } else {
        printf("No more actions to redo.\n");
    }
}

void initUndoRedoStacks() {
    undoStack = (char ***)malloc(MAX_UNDO_REDO * sizeof(char **));
    redoStack = (char ***)malloc(MAX_UNDO_REDO * sizeof(char **));
    for (int i = 0; i < MAX_UNDO_REDO; i++) {
        undoStack[i] = NULL;
        redoStack[i] = NULL;
    }
}

void freeUndoRedoStacks() {
    for (int i = 0; i <= undoTop; i++) {
        if (undoStack[i]) {
            for (int j = 0; j < canvasHeight; j++) {
                free(undoStack[i][j]);
            }
            free(undoStack[i]);
        }
    }
    for (int i = 0; i <= redoTop; i++) {
        if (redoStack[i]) {
            for (int j = 0; j < canvasHeight; j++) {
                free(redoStack[i][j]);
            }
            free(redoStack[i]);
        }
    }
    free(undoStack);
    free(redoStack);
}

void drawRectangle(int x, int y, int width, int height) {
    pushSnapshot();
    y /= 2; // Adjust vertical scale for 1:2 aspect ratio
    height /= 2; // Adjust height for 1:2 aspect ratio
    for (int i = 0; i < width; i++) {
        drawPoint(x + i, y, '*'); // Top edge
        drawPoint(x + i, y + height - 1, '*'); // Bottom edge
    }
    for (int i = 0; i < height; i++) {
        drawPoint(x, y + i, '*'); // Left edge
        drawPoint(x + width - 1, y + i, '*'); // Right edge
    }
}

void drawCircle(int x, int y, int radius) {
    pushSnapshot();
    y /= 2; // Adjust vertical scale for 1:2 aspect ratio
    radius /= 2; // Adjust radius for 1:2 aspect ratio
    int dx = 0, dy = radius;
    int d = 3 - 2 * radius;
    while (dy >= dx) {
        drawPoint(x + dx, y + dy, '*');
        drawPoint(x - dx, y + dy, '*');
        drawPoint(x + dx, y - dy, '*');
        drawPoint(x - dx, y - dy, '*');
        drawPoint(x + dy, y + dx, '*');
        drawPoint(x - dy, y + dx, '*');
        drawPoint(x + dy, y - dx, '*');
        drawPoint(x - dy, y - dx, '*');
        if (d <= 0) {
            d = d + 4 * dx + 6;
        } else {
            d = d + 4 * (dx - dy) + 10;
            dy--;
        }
        dx++;
    }
}

void exportCanvas(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    for (int i = 0; i < canvasHeight; i++) {
        for (int j = 0; j < canvasWidth; j++) {
            fputc(canvas[i][j] == '*' ? '1' : '0', file);
        }
    }

    fclose(file);
    printf("Canvas exported to %s successfully.\n", filename);
}

void importCanvas(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s for reading.\n", filename);
        return;
    }

    int ch, x = 0, y = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (x >= canvasWidth) {
            x = 0;
            y++;
        }
        if (y >= canvasHeight) {
            break;
        }
        canvas[y][x++] = (ch == '1') ? '*' : ' ';
    }

    fclose(file);
    printf("Canvas imported from %s successfully.\n", filename);
}

void fillRectangle(int x, int y, int width, int height) {
    pushSnapshot();
    y /= 2; // Adjust vertical scale for 1:2 aspect ratio
    height /= 2; // Adjust height for 1:2 aspect ratio
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            drawPoint(x + j, y + i, '*'); // Fill the rectangle with '*'
        }
    }
}

void fillCircle(int x, int y, int radius) {
    pushSnapshot();
    y /= 2; // Adjust vertical scale for 1:2 aspect ratio
    radius /= 2; // Adjust radius for 1:2 aspect ratio
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx * dx + dy * dy <= radius * radius) {
                drawPoint(x + dx, y + dy, '*'); // Fill the circle with '*'
            }
        }
    }
}

void clearRect(int x, int y, int width, int height) {
    pushSnapshot();
    y /= 2; // Adjust vertical scale for 1:2 aspect ratio
    height /= 2; // Adjust height for 1:2 aspect ratio
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            drawPoint(x + j, y + i, ' '); // Clear the rectangle with space characters
        }
    }
}

void writeText(int x, int y, const char *text) {
    pushSnapshot(); // Save the current canvas state
    printf("Writing text: %s\n", text);
    for (int i = 0; text[i] != '\0'; i++) {
        char original = text[i];
        char ch = toupper(original);

        printf("Index %d: %c (ASCII: %d) → upper: %c\n", i, original, original, ch);

        if (x + CHAR_WIDTH > canvasWidth) {
            x = 0;
            y += CHAR_HEIGHT + 1;
        }

        if (y + CHAR_HEIGHT > canvasHeight) {
            printf("Breaking: not enough vertical space\n");
            break;
        }

        int unsupported = 1;
        if (ch >= 0 && ch < 128) {
            for (int r = 0; r < CHAR_HEIGHT; r++) {
                for (int c = 0; c < CHAR_WIDTH; c++) {
                    if (CHAR_MAP[ch][r][c]) {
                        unsupported = 0;
                        break;
                    }
                }
                if (!unsupported) break;
            }
        }

        if (unsupported) {
            printf("Unsupported char: %c\n", ch);
            ch = ' ';
        }

        for (int row = 0; row < CHAR_HEIGHT; row++) {
            for (int col = 0; col < CHAR_WIDTH; col++) {
                if (CHAR_MAP[ch][row][col]) {
                    drawPoint(x + col, y + row, '*');
                }
            }
        }

        printf("Rendered char: %c at (%d, %d)\n", ch, x, y);
        x += CHAR_WIDTH + 1;
    }
}
