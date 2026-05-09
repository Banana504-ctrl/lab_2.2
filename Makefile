CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = lab2.exe

SOURCES = main.cpp ui.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(TARGET) $(OBJECTS) 2>nul || rm -f $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run