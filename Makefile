CPP := clang++
SRCDIR := src
BINDIR := bin
INCDIR := -I $(SRCDIR) -I /usr/include/freetype2

SRCS := $(shell find $(SRCDIR) -type f -name *.cpp)
OJBS := $(patsubst $(SRCDIR)/%, $(BINDIR)/%, $(SRCS:.cpp=.o))
CFLAGS := -std=c++17 -g -Wall -Wpedantic
LDFLAGS := -lglfw -lGL -lGLEW  -lfreetype
TARGET := $(BINDIR)/byte_me_v1

.PHONY: run clean

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SRCS)
	$(CPP) $^ -o $@ $(LDFLAGS) $(CFLAGS) $(INCDIR)

# $(BINDIR)/%.o: $(SRCDIR)/%.cpp
# 	@mkdir -p $(@D)
# 	$(CPP) $(CFLAGS) $(INCDIR) -c -o $@ $<
