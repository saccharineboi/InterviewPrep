CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Og -g

SRCS = $(wildcard chapter_1/*.cpp)
SRCS += $(wildcard util/tests/*.cpp)

all: $(SRCS:.cpp=.out)

%.out: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o $(SRCS:.cpp=.out)
