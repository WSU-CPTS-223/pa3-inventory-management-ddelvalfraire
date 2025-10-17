CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude
LDFLAGS = 

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TARGET = build/PA3
DATA_SRC = $(wildcard data/*.csv)
DATA_DST = $(DATA_SRC:data/%=build/data/%)

all: $(TARGET) $(DATA_DST)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/data/%.csv: data/%.csv | build/data
	cp $< $@

build build/data:
	mkdir -p $@

run: all
	./$(TARGET)

clean:
	rm -rf build

.PHONY: all run clean