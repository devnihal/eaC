# ✨ EAC - Executable ASCII Canvas

**EAC (Executable ASCII Canvas)** is a command-line based drawing tool inspired by the JavaScript Canvas API. It allows users to draw graphics using ASCII characters directly in the terminal, by inputting commands like `moveTo(x, y)` and `lineTo(x, y)`. This is a lightweight, fun, and educational project built in C for learning and demonstrating graphics programming principles using only the terminal.

---

## 🌟 Objective

To create a CLI-based drawing environment that emulates canvas-style drawing through code commands. The goal is to offer a minimal yet visually intuitive "canvas" experience using only ASCII characters.

---

## 🧠 Core Concept

Much like the HTML5 `<canvas>` element in JavaScript, EAC lets you draw using code. It provides a canvas at the top of the terminal window (based on terminal size) and a command prompt at the bottom where you can type drawing instructions. Each command updates the canvas in real-time.

---

## 🚀 Features

- 👡️ **`moveTo(x, y)`** – Moves the drawing cursor to the specified coordinates.
- ✍️ **`lineTo(x, y)`** – Draws a straight line from the current cursor position to the given point using Bresenham’s line algorithm.
- □ **`rectangle(x, y, width, height)`** – Draws a rectangle using the top-left corner as a reference.
- ⚪ **`circle(x, y, radius)`** – Draws a circle centered at `(x, y)` with the given radius.
- ■ **`fillRectangle(x, y, width, height)`** – Draws a filled rectangle from the top-left corner.
- ⚫ **`fillCircle(x, y, radius)`** – Draws a filled circle centered at `(x, y)`.
- 📝 **`writeText("text", x, y)`** – Renders styled uppercase ASCII characters onto the canvas at a specified location.
- 🧼 **`clear`** – Clears the canvas and resets the cursor.
- 🔄 **Undo/Redo** – Allows stepping backward or forward through the canvas history using `undo()` and `redo()`.
- 💾 **Export/Import** – Save or restore canvas state to/from `.eac` files.
- 🖼️ **Real-time rendering** – Canvas updates instantly after each command, giving a live-draw experience.
- ⌨️ **Command prompt interface** – Accepts structured commands (`writeText(...)`, `lineTo(...)`, etc.) like a REPL.
- 🧠 **Memory-efficient ASCII buffer** – Optimized 2D array canvas system with dedicated stacks for state snapshots.

---

## 🏗️ File Structure

```
eaC/
├── src/
│   ├── main.c         # Main loop, input handling
│   ├── canvas.c       # Drawing logic and rendering
│   └── canvas.h       # Canvas function declarations and macros
├── builds/
│   └── eac.exe        # Compiled executable
├── drawings/
│   └── sample.eac     # Saved drawing scripts
└── README.md          # Project documentation
```

---

## 💻 How It Works

1. **Canvas Initialization**: Detects terminal size and allocates canvas space accordingly.
2. **Command Mode**: The last line of the terminal acts as a command input line.
3. **ASCII Rendering**: All drawings are rendered using `'*'` on a 2D character array.
4. **Canvas Refresh**: Uses `system("cls||clear")` to simulate screen refresh.

---
## 🧰 Dependencies

- **Compiler**: Requires `gcc` or any C compiler.
- **Build System**: `make` (optional, but recommended for easier builds).
- **Operating System**:
  - Windows (tested with `cmd` and `PowerShell`).
  - Linux (tested with `bash`).
- **Terminal**:
  - A terminal that supports ANSI escape codes for clearing the screen (`system("cls||clear")`).
- **Standard C Libraries**:
  - `stdio.h`, `stdlib.h`, `string.h`, and `windows.h` (for Windows-specific terminal handling).

---

## ⚙️ Usage

To utilize this project, you first need to acquire the source code. You can achieve this through either of the following standard methods:

**1. Obtaining the Source Code:**

**a) Cloning the Git Repository (Recommended):**

For users with Git installed, cloning the repository is the preferred method as it allows for easy updating and contribution:

```bash
git clone [https://github.com/devnihal/eaC.git](https://github.com/devnihal/eaC.git)
cd eaC
```

**b) Downloading and Extracting the ZIP Archive:**

Alternatively, you can download a snapshot of the codebase as a ZIP file:

1.  Click the following link to download the ZIP archive:
    [Download ZIP](https://github.com/devnihal/eaC/archive/refs/heads/main.zip)
2.  Your browser will download a file named `main.zip`.
3.  Upon completion, extract the contents of this ZIP file to your desired location (e.g., a directory named `eaC`).

After obtaining the source code via either method, navigate into the project's root directory:

```bash
cd eaC
```

You can now proceed with the manual build and execution steps outlined below.

### 🧪 Run Manually (Windows/Linux)

1.  **Compile the Code**:
    - Using `make` (if available):
      ```bash
      make
      ```
    - Alternatively, compile manually:
      - On Windows:
        ```bash
        gcc src/main.c src/canvas.c -o builds/eac.exe
        ```
      - On Linux:
        ```bash
        gcc src/main.c src/canvas.c -o builds/eac
        ```

2.  **Run the Program**:
    - Using `make run` (if `make` is available):
      ```bash
      make run
      ```
    - Alternatively, run manually:
      - On Windows:
        ```bash
        ./builds/eac.exe
        ```
      - On Linux:
        ```bash
        ./builds/eac
        ```

3.  **Import Drawings**:
    - You can provide a `.eac` file to import and render its contents:
      ```bash
      ./builds/eac drawings/sample.eac
      ```

4.  **Use Commands**:
    - Enter commands like `moveTo(x, y)`, `lineTo(x, y)`, `fillRectangle(x, y, width, height)`, etc., to draw on the canvas.
---

## 🗣Commands

| Command Syntax               | Description                                                                 |
|------------------------------|-----------------------------------------------------------------------------|
| `moveTo(x, y)`               | Moves the cursor to `(x, y)`.                                               |
| `lineTo(x, y)`               | Draws a line from the current position to `(x, y)`.                         |
| `rectangle(x, y, width, height)` | Draws a rectangle with the top-left corner at `(x, y)`, width `width`, and height `height`. |
| `circle(x, y, radius)`       | Draws a circle centered at `(x, y)` with radius `radius`.                   |
| `fillRectangle(x, y, width, height)` | Draws a filled rectangle with the top-left corner at `(x, y)`, width `width`, and height `height`. |
| `fillCircle(x, y, radius)`   | Draws a filled circle centered at `(x, y)` with radius `radius`.            |
| `clear`                      | Clears the canvas.                                                         |
| `clearRect(x, y, width, height)` | Clears a rectangular area at (x,y) with specified width and height. |
| `undo`                       | Undoes the last action.                                                    |
| `redo`                       | Redoes the last undone action.                                             |
| `exit`                       | Exits the program.                                                         |

---

## 👥 Authors & Team  

### 🏆 Lead Developer  
- **👨🏻‍💻 Mohammed Nihal** ([@devnihal](https://github.com/devnihal)) – **Creator & Lead Developer** 🚀  

### 💻 Development Team  
-  **👩🏻‍💻Fathima Nadha** ([@nadha24](https://github.com/nadha24)) – Co-Developer 💡

-  **🧑🏻‍💻 Ajai Bhaskar** ([@ajaiaju39](https://github.com/ajaiaju39)) – Co-Developer 💡  

-  **👩🏻‍💻 Nihla PN** ([@nihla42](https://github.com/nihla42)) - Co-Developer 💡
-  **👩🏻‍💻 Sreepriya N** ([@Sreepriya58](https://github.com/Sreepriya58)) - Co-Developer 💡
-  **👩🏻‍💻 Sanha** ([@Sanha5](https://github.com/Sanha5)) - Co-Developer 💡

---

## 🙌 Contributions

Want to improve EAC? Fork it, build it, and open a pull request!

---

## 📌 License

This project is licensed under the **MIT License**.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

**THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.**

---

