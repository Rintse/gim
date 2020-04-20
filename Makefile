INC_DIR			= include
SRC_DIR			= src
MAIN_DIR		= main
SOURCES			= $(shell find $(SRC_DIR)/ -name '*.cc')
MAIN_SRC		= $(shell find $(MAIN_DIR)/ -name '*.cc')
OBJECTS			= $(SOURCES:.cc=.o)
MAIN_OBJ		= $(MAIN_SRC:.cc=.o)
DEPS 			= $(OBJECTS:.o=.d)
MAIN_DEPS		= $(MAIN_OBJ:.o=.d)
MAIN_TARGET		= george
CC				= g++
CFLAGS			= -std=c++11 -O3 -Wall
CPPFLAGS 		= $(addprefix -I, $(INC_DIR)) -pedantic
SDLFLAGS		= $(shell pkg-config --cflags --libs sdl2)

.PHONY: all clean

all: $(MAIN_TARGET)

$(MAIN_TARGET): $(OBJECTS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(SDLFLAGS)
-include $(MAIN_DEPS) $(DEPS)

%.o: %.cc
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $< $(SDLFLAGS)

clean:
	rm -f $(OBJECTS) $(MAIN_OBJ) $(DEPS) $(MAIN_DEPS) $(MAIN_TARGET)
