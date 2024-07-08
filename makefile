# coheny405@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = demo

SOURCES = demo.cpp Complex.cpp

HEADERS = Node.hpp Tree.hpp Iterator.hpp Complex.hpp

TEST_HEADERS = doctest.h Node.hpp Tree.hpp Iterator.hpp Complex.hpp

TEST_SOURCES = Test.cpp Complex.cpp TestCounter.cpp

TEST_TARGET = test

# Replace .cpp with .o in SOURCES
OBJECTS = $(SOURCES:.cpp=.o)

TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile .cpp files to .o files
demo.o: demo.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

Complex.o: Complex.cpp Complex.hpp
	$(CXX) $(CXXFLAGS) -c $<

Test.o: Test.cpp $(TEST_HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_OBJECTS) $(TEST_TARGET)

.PHONY: all clean