INC_DIR			= include
SRC_DIR			= src
MAIN_DIR		= main
SOURCES			= $(shell find $(SRC_DIR)/ -name '*.cc')
MAIN_SRC		= $(shell find $(MAIN_DIR)/ -name '*.cc')
# MAIN_SRC		= gentest.cc
OBJECTS			= $(SOURCES:.cc=.o)
MAIN_OBJ		= $(MAIN_SRC:.cc=.o)
DEPS 			= $(OBJECTS:.o=.d)
MAIN_DEPS		= $(MAIN_OBJ:.o=.d)
MAIN_TARGET		= george
CC				= g++
CFLAGS			= -std=c++11 -g -Wall
CPPFLAGS 		= $(addprefix -I, $(INC_DIR)) -pedantic
SDLFLAGS		= $(shell pkg-config x11 --libs) $(shell pkg-config --cflags --libs sdl2) -lSDL2_ttf
THREADFLAGS		= -pthread

.PHONY: all clean

all: $(MAIN_TARGET)

$(MAIN_TARGET): $(OBJECTS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(SDLFLAGS) $(THREADFLAGS)
-include $(MAIN_DEPS) $(DEPS)

%.o: %.cc
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $< $(SDLFLAGS) $(THREADFLAGS)

clean:
	rm -f $(OBJECTS) $(MAIN_OBJ) $(DEPS) $(MAIN_DEPS) $(MAIN_TARGET)
