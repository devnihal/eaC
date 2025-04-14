#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canvas.h"
#include <conio.h> // For _getch()

#define MAX_INPUT 256
#define COMMAND_PROMPT ">> "

// Terminal dimensions
int lastWidth = 0, lastHeight = 0;

// Function to check terminal resize
void checkResize(int imported) {
    int currentWidth, currentHeight;
    getTerminalSize(&currentWidth, &currentHeight);

    if ((currentWidth != lastWidth || currentHeight != lastHeight) && !imported) {
        lastWidth = currentWidth;
        lastHeight = currentHeight;
        initCanvas(); // Reinitialize the canvas on resize
    }
}

// Cleanup resources and exit
void cleanupAndExit() {
    freeCanvas();
    freeUndoRedoStacks();
    exit(0);
}

// Parse and execute commands
void parseCommand(char *input) {
    int x = 0, y = 0, width, height, radius;
    char filename[MAX_INPUT];
    char text[MAX_INPUT];
    if (strncmp(input, "moveTo", 6) == 0) {
        pushSnapshot();
        if (sscanf(input, "moveTo(%d, %d)", &x, &y) == 2) {
            moveTo(x, y);
        } else {
            printf("Invalid command format. Use: moveTo(x, y)\n");
        }
    } else if (strncmp(input, "lineTo", 6) == 0) {
        pushSnapshot();
        if (sscanf(input, "lineTo(%d, %d)", &x, &y) == 2) {
            lineTo(x, y);
        } else {
            printf("Invalid command format. Use: lineTo(x, y)\n");
        }
    } else if (strncmp(input, "rectangle", 9) == 0) {
        pushSnapshot();
        if (sscanf(input, "rectangle(%d, %d, %d, %d)", &x, &y, &width, &height) == 4) {
            drawRectangle(x, y, width, height);
        } else {
            printf("Invalid command format. Use: rectangle(x, y, width, height)\n");
        }
    } else if (strncmp(input, "circle", 6) == 0) {
        pushSnapshot();
        if (sscanf(input, "circle(%d, %d, %d)", &x, &y, &radius) == 3) {
            drawCircle(x, y, radius);
        } else {
            printf("Invalid command format. Use: circle(x, y, radius)\n");
        }
    } else if (strncmp(input, "fillRectangle", 13) == 0) {
        if (sscanf(input, "fillRectangle(%d, %d, %d, %d)", &x, &y, &width, &height) == 4) {
            fillRectangle(x, y, width, height);
        } else {
            printf("Invalid command format. Use: fillRectangle(x, y, width, height)\n");
        }
    } else if (strncmp(input, "fillCircle", 10) == 0) {
        if (sscanf(input, "fillCircle(%d, %d, %d)", &x, &y, &radius) == 3) {
            fillCircle(x, y, radius);
        } else {
            printf("Invalid command format. Use: fillCircle(x, y, radius)\n");
        }
    } else if (strncmp(input, "clearRect", 9) == 0) {
        pushSnapshot();
        if (sscanf(input, "clearRect(%d, %d, %d, %d)", &x, &y, &width, &height) == 4) {
            clearRect(x, y, width, height);
        } else {
            printf("Invalid command format. Use: clearRect(x, y, width, height)\n");
        }
    } else if (strcmp(input, "clear") == 0) {
        pushSnapshot();
        clearCanvas();
    } else if (strcmp(input, "undo") == 0) {
        undo();
    } else if (strcmp(input, "redo") == 0) {
        redo();
    } else if (strcmp(input, "exit") == 0) {
        cleanupAndExit();
    } else if (strncmp(input, "export(", 7) == 0) {
        if (sscanf(input, "export(%[^)])", filename) == 1) {
            exportCanvas(filename);
        } else {
            printf("Invalid command format. Use: export(filename.eac)\n");
        }
    } else if (strncmp(input, "writeText", 9) == 0) {
        if (sscanf(input, "writeText(\"%[^\"]\", %d, %d)", text, &x, &y) == 3) {
            writeText(x, y, text);
        } else if (sscanf(input, "writeText(\"%[^\"]\")", text) == 1) {
            writeText(0, 0, text); // Default to (0, 0) if x and y are not provided
        } else {
            printf("Invalid command format. Use: writeText(\"text\", x, y) or writeText(\"text\")\n");
        }
    } else if (strcmp(input, "devs") || strcmp(input, "credits")){
        importCanvas("drawings/credit.eac");
    } else {
        printf("Unknown command: %s\n", input);
    }
}

int main(int argc, char *argv[]) {
    char input[MAX_INPUT];
    int imported = 0; // Flag to indicate if a file was imported

    // Initialize canvas and undo/redo stacks
    initCanvas();
    initUndoRedoStacks();
    pushSnapshot();

    // Check if a file argument is provided
    if (argc == 2) {
        printf("Importing file: %s\n", argv[1]);
        importCanvas(argv[1]);
        imported = 1;
    }

    while (1) {
        checkResize(imported);
        renderCanvas(1);
    
        printf("\n%s", COMMAND_PROMPT);
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0; // Trim newline at end
    
        if (strcmp(input, "exit") == 0) {
            break;
        }
    
        parseCommand(input);
    }
    

    // Cleanup resources before exiting
    cleanupAndExit();
    return 0;
}
