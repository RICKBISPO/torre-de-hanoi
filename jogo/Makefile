# Variáveis de compilação
CC = gcc
CFLAGS = -I./SDL2/include
LDFLAGS = -L./SDL2/lib
LDLIBS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

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
linux: linux-libs $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDLIBS)

linux-libs:
	sudo apt-get update
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev

windows: 
	gcc -o $(TARGET) $(SRCS) -I ./SDL2/include -L ./SDL2/lib/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

windows-libs:
	
# 	Criar diretórios para as bibliotecas
	if not exist SDL2 mkdir SDL2
	if not exist SDL2\include\SDL2 mkdir SDL2\include\SDL2
	if not exist SDL2\lib mkdir SDL2\lib

# 	Baixar as bibliotecas
	powershell -Command "Invoke-WebRequest -OutFile SDL2/SDL2-devel-2.0.12-mingw.tar.gz -Uri https://www.libsdl.org/release/SDL2-devel-2.0.12-mingw.tar.gz"
	powershell -Command "Invoke-WebRequest -OutFile SDL2/SDL2_image-devel-2.0.5-mingw.tar.gz -Uri https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz"
	powershell -Command "Invoke-WebRequest -OutFile SDL2/SDL2_ttf-devel-2.0.15-mingw.tar.gz -Uri https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-mingw.tar.gz"
	
# 	Extrair as bibliotecas
	tar -xzf SDL2/SDL2-devel-2.0.12-mingw.tar.gz -C SDL2
	tar -xzf SDL2/SDL2_image-devel-2.0.5-mingw.tar.gz -C SDL2
	tar -xzf SDL2/SDL2_ttf-devel-2.0.15-mingw.tar.gz -C SDL2
	
#	Include
	if exist .\SDL2\SDL2-2.0.12\i686-w64-mingw32\include\SDL2\* move .\SDL2\SDL2-2.0.12\i686-w64-mingw32\include\SDL2\* .\SDL2\include\SDL2
	if exist .\SDL2\SDL2_image-2.0.5\i686-w64-mingw32\include\SDL2\* move .\SDL2\SDL2_image-2.0.5\i686-w64-mingw32\include\SDL2\* .\SDL2\include\SDL2
	if exist .\SDL2\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2\* move .\SDL2\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2\* .\SDL2\include\SDL2

#	Lib
	if exist .\SDL2\SDL2-2.0.12\i686-w64-mingw32\lib\* move .\SDL2\SDL2-2.0.12\i686-w64-mingw32\lib\* .\SDL2\lib
	if exist .\SDL2\SDL2_image-2.0.5\i686-w64-mingw32\lib\* move .\SDL2\SDL2_image-2.0.5\i686-w64-mingw32\lib\* .\SDL2\lib
	if exist .\SDL2\SDL2_ttf-2.0.15\i686-w64-mingw32\lib\* move .\SDL2\SDL2_ttf-2.0.15\i686-w64-mingw32\lib\* .\SDL2\lib

# #	dll
# 	if exist .\SDL2\SDL2-2.0.12\i686-w64-mingw32\bin\SDL2.dll move .\SDL2\SDL2-2.0.12\i686-w64-mingw32\bin\SDL2.dll .\\
# 	if exist .\SDL2\SDL2_image-2.0.5\i686-w64-mingw32\bin\SDL2_image.dll move .\SDL2\SDL2_image-2.0.5\i686-w64-mingw32\bin\SDL2_image.dll .\\
# 	if exist .\SDL2\SDL2_ttf-2.0.15\i686-w64-mingw32\bin\SDL2_ttf.dll move .\SDL2\SDL2_ttf-2.0.15\i686-w64-mingw32\bin\SDL2_ttf.dll .\\

#	Remover diretórios e arquivos desnecessários
	powershell -Command "Remove-Item -Recurse -Force -Path .\SDL2\SDL2-2.0.12"
	powershell -Command "Remove-Item -Recurse -Force -Path .\SDL2\SDL2_image-2.0.5"
	powershell -Command "Remove-Item -Recurse -Force -Path .\SDL2\SDL2_ttf-2.0.15"

	powershell -Command "Remove-Item -Force -Path .\SDL2\SDL2-devel-2.0.12-mingw.tar.gz"
	powershell -Command "Remove-Item -Force -Path .\SDL2\SDL2_image-devel-2.0.5-mingw.tar.gz"
	powershell -Command "Remove-Item -Force -Path .\SDL2\SDL2_ttf-devel-2.0.15-mingw.tar.gz"


# Limpar arquivos .o e o executável ao compilar
.PHONY: clean
clean:
ifeq ($(detected_OS),Windows)
	cmd /C del /Q $(subst /,\,$(OBJS))
else
	rm -f $(OBJS)
endif

.PHONY: clean linux-libs linux windows-libs windows