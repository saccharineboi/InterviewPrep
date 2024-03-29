CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

SRCS = $(wildcard chapter_1/*.cpp \
	   			  chapter_2/*.cpp \
				  chapter_3/*.cpp \
				  chapter_4/*.cpp \
				  algorithms/*.cpp)
TEST_SRCS = $(wildcard data_structures/tests/*.cpp)

all: $(SRCS:.cpp=.out)
tests: $(TEST_SRCS:.cpp=.test)

%.out: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

%.test: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o $(SRCS:.cpp=.out) $(TEST_SRCS:.cpp=.test)

.PHONY: test
test: tests
	@for test in $(TEST_SRCS:.cpp=.test) ; do \
		echo "Running $$test..." ; \
		./$$test || exit 1 ; \
	done
