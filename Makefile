CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra
SRC = src/main.cpp src/Shell.cpp src/MemoryAllocator.cpp
TARGET = MiniShell

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
