CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = src/main.c src/canvas.c
OUT_DIR = builds
OUT = $(OUT_DIR)/eac

all: $(OUT)

$(OUT): $(SRC)
	@$(if exist "$(OUT_DIR)",,mkdir "$(OUT_DIR)")
	$(CC) $(CFLAGS) -o "$(OUT)" $(SRC)
	@echo "Build complete: $(OUT)"

run: all
	@echo "Running $(OUT)..."
	@"./$(OUT)"

clean:
	rm -rf "$(OUT_DIR)"
	@echo "Cleaned up build directory."

rebuild: clean all