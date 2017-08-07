CXX := g++
CXXFLAGS := -std=c++14 -Wall -o out

default: out run

out: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	$(RM) out

run:
	./out
