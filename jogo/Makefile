# Variáveis de compilação
CC = gcc
CFLAGS = -I./SDL2/include
LDFLAGS = -L./SDL2/lib
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# Arquivos fonte
SRCS := $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

# Nome do executável
ifeq ($(OS),Windows_NT)
	TARGET = programa.exe
else
	TARGET = programa
endif

# Detectar o sistema operativo
ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell uname -s)
endif

# Regras para Linux e Windows
linux: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDLIBS)

linux-libs:
	sudo apt-get update
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev

windows:
	gcc -o $(TARGET) $(SRCS) -I ./SDL2/include -L ./SDL2/lib/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# Limpar arquivos .o e o executável ao compilar
.PHONY: clean
clean:
ifeq ($(detected_OS),Windows)
	cmd /C del /Q $(subst /,\,$(OBJS))
else
	rm -f $(OBJS)
endif

.PHONY: clean linux-libs linux windows