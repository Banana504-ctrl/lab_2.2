CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -I.
WINLIBS = -lgdi32 -lcomctl32

TARGET_CONSOLE = lab2.exe
TARGET_GUI = lab2_gui.exe

all: $(TARGET_CONSOLE)

$(TARGET_CONSOLE): main.cpp ui.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_CONSOLE) main.cpp ui.cpp

gui: $(TARGET_GUI)

$(TARGET_GUI): main_gui.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_GUI) main_gui.cpp $(WINLIBS)

test:
	$(CXX) $(CXXFLAGS) -o test_runner.exe tests/test_runner.cpp
	./test_runner.exe

clean:
	del /Q *.exe 2>nul || rm -f *.exe

.PHONY: all clean test gui