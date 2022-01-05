VERSION := 1.0.0
CPP := g++
SRCDIR := src
BINDIR := bin
INCDIR := -I include -I /usr/include/freetype2

SRCS := $(shell find $(SRCDIR) -type f -name *.cpp)
OJBS := $(patsubst $(SRCDIR)/%, $(BINDIR)/%, $(SRCS:.cpp=.o))
CFLAGS := -std=c++17 -g -Wall -Wpedantic
LDFLAGS := -lpthread -lglfw -lGL -lGLEW  -lfreetype
TARGET := $(BINDIR)/mc_runner_v$(VERSION)

.PHONY: run clean

run: $(TARGET)
	@echo " Running..."
	./$(TARGET)

clean:
	@echo " Cleaning..."
	@echo " rm -f $(OJBS) $(TARGET)"; rm -f $(OJBS) $(TARGET)

$(TARGET): $(OJBS)
	@echo " Linking..."
	@echo " $(CPP) $^ -o $@ $(LDFLAGS)"; $(CPP) $^ -o $@ $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@echo " $(CPP) $(CFLAGS) $(INCDIR) -c -o $@ $<"; $(CPP) $(CFLAGS) $(INCDIR) -c -o $@ $<
