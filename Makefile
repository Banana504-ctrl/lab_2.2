CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -I.

TARGET = lab2.exe

SOURCES = main.cpp ui.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test:
	$(CXX) $(CXXFLAGS) -o test_runner.exe tests/test_runner.cpp
	./test_runner.exe

clean:
	del /Q *.o *.exe 2>nul || rm -f *.o *.exe

.PHONY: all clean test