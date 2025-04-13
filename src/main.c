// #include <stdio.h>
// #include <stdlib.h>
// #include <windows.h>
// #include <string.h>
// #include "canvas.h"

// #define MAX_INPUT 256

// int lastWidth = 0;
// int lastHeight = 0;

// void checkResize() {
//     int currentWidth, currentHeight;
//     getTerminalSize(&currentWidth, &currentHeight);

//     if (currentWidth != lastWidth || currentHeight != lastHeight) {
//         lastWidth = currentWidth;
//         lastHeight = currentHeight;
//         initCanvas();
//     }
// }

// int main() {
//     char input[MAX_INPUT];
//     initCanvas();

//     while (1) {
//         checkResize();

//         renderCanvas();

//         if (!fgets(input, sizeof(input), stdin)) {
//             break;
//         }

        
//         input[strcspn(input, "\n")] = '\0';

//         if (strcmp(input, "exit") == 0) {
//             break;
//         } else if (strcmp(input, "clear") == 0) {
//             clearCanvas();
//         } else if (strcmp(input, "point") == 0) {
//             drawPoint(10, 5, '*'); // Example usage for now
//         } else {
//             printf("Unknown command: %s\n", input);
//         }
//     }

//     return 0;
// }



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canvas.h"

#define MAX_INPUT 256

int lastWidth = 0;
int lastHeight = 0;

// Function to check if terminal was resized
void checkResize() {
    int currentWidth, currentHeight;
    getTerminalSize(&currentWidth, &currentHeight);

    if (currentWidth != lastWidth || currentHeight != lastHeight) {
        lastWidth = currentWidth;
        lastHeight = currentHeight;
        initCanvas();  // Reinitialize canvas with new terminal size
    }
}

// Function to parse user input commands and execute drawing functions
void parseCommand(char *input) {
    int x, y;
    if (strncmp(input, "moveTo", 6) == 0) {
        sscanf(input, "moveTo(%d, %d)", &x, &y);
        moveTo(x, y);
    } else if (strncmp(input, "lineTo", 6) == 0) {
        sscanf(input, "lineTo(%d, %d)", &x, &y);
        lineTo(x, y);
    } else if (strcmp(input, "clear") == 0) {
        clearCanvas();
    } else if (strcmp(input, "exit") == 0) {
        return;  // Clean exit
    } else {
        printf("Unknown command: %s\n", input);
    }
}

int main() {
    char input[MAX_INPUT];
    initCanvas();

    // Main program loop
    while (1) {
        checkResize();  // Check for terminal resize

        renderCanvas();  // Render the canvas

        printf("\n> ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        parseCommand(input);  // Parse and execute the command
    }

    return 0;
}
