VERSION := 1.0.0
CPP := clang++
SRCDIR := src
BINDIR := bin
INCDIR := -I $(SRCDIR) -I /usr/include/freetype2

SRCS := $(shell find $(SRCDIR) -type f -name *.cpp)
OJBS := $(patsubst $(SRCDIR)/%, $(BINDIR)/%, $(SRCS:.cpp=.o))
CFLAGS := -std=c++17 -g -Wall -Wpedantic
LDFLAGS := -lglfw -lGL -lGLEW  -lfreetype
TARGET := $(BINDIR)/cpp_gl_test$(VERSION)

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
