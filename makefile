ifeq ($(OS),Windows_NT)
COMPILE_WINDOWS=1
else
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
COMPILE_LINUX=1
endif
ifeq ($(UNAME_S),Darwin)
COMPILE_MAC=1
endif
endif

COMPILER  = g++

CFLAGS    = -g -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers
CFLAGS   += -std=c++11 -Os

ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS =
else
  LDFLAGS =
endif
LDFLAGS  += -s -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread

ifeq ($(OS), Windows_NT)
LIBS      = -lmingw32 -lSDL2main
endif
LIBS     += -lSDL2

INCLUDE   = -I./include

BINDIR    = ./bin
TARGET    = $(BINDIR)/$(shell basename `readlink -f .`)

SRCDIR    = ./src
ifeq "$(strip $(SRCDIR))" ""
  SRCDIR  = .
endif
SOURCES   = $(wildcard $(SRCDIR)/*.cpp)

OBJDIR    = ./obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR  = .
endif
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS)
	-mkdir -p $(BINDIR)
	$(COMPILER) -o $@ $^ $(LIBS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
