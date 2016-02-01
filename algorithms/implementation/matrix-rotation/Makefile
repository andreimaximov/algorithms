CXX := g++
CXXFLAGS := -std=c++11 -stdlib=libc++ -Wall

TARGET := a.out

default: build run

build:
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

run:
	./$(TARGET)
