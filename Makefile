
CFLAGS = g++ -std=c++17 -Wall -pedantic -g
LDFLAGS = -lGL -lGLEW -lglfw -lfreetype
TARGET = cppgltest

all: run

compile:
	$(CFLAGS) -o bin/$(TARGET) $(LDFLAGS) src/*.cpp -I /usr/include/freetype2 -L lib

run: compile
	./bin/$(TARGET)

clean:
	rm -f bin/$(TARGET)