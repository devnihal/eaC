# Makefile for EAC - Executable ASCII Canvas

CC = gcc
CFLAGS = -Wall -Wextra
SRC = src/main.c src/canvas.c
OUT = builds/eac.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	del /q builds\* 2>nul || rm -f builds/*
