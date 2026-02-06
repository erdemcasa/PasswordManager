CXX      = clang++
CC       = clang
CXXFLAGS = -std=c++20 -O3 -Iinclude -Iexternal/sqlite -Iexternal/ftxui/include -Iexternal/ftxui/src -D_CRT_SECURE_NO_WARNINGS -DUNICODE -D_UNICODE -w
CFLAGS   = -O3 -Iexternal/sqlite -D_CRT_SECURE_NO_WARNINGS -w

FTXUI_SRC = $(shell find external/ftxui/src/ftxui -name "*.cpp" ! -name "*_test.cpp" ! -name "*fuzzer.cpp")
MY_SRC    = src/main.cpp src/database.cpp src/ui.cpp
SQLITE_C  = external/sqlite/sqlite3.c

TARGET = build/PasswordManager.exe

all: prepare $(TARGET)

prepare:
	mkdir -p build

$(TARGET):
	@echo "Compilation statique (plus besoin de DLL)..."
	# 1. On compile SQLite
	$(CC) $(CFLAGS) -c $(SQLITE_C) -o build/sqlite3.o
	# 2. On compile tout avec -static et les flags de lien
	$(CXX) $(CXXFLAGS) $(MY_SRC) $(FTXUI_SRC) build/sqlite3.o -o $(TARGET) -mconsole -Wl,-e,mainCRTStartup -static
	@echo "------------------------------------------------"
	@echo "TERMINÉ ! Ton .exe est maintenant 100% autonome."
	@echo "------------------------------------------------"

clean:
	rm -rf build