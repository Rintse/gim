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
CFLAGS			= -std=c++11 -g -Wall
CPPFLAGS 		= $(addprefix -I, $(INC_DIR)) -pedantic

.PHONY: all clean

all: $(MAIN_TARGET)

$(MAIN_TARGET): $(OBJECTS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ -lncurses
-include $(MAIN_DEPS) $(DEPS)

%.o: %.cc
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -lcurses -o $@ -c $<

clean:
	rm -f $(OBJECTS) $(MAIN_OBJ) $(DEPS) $(MAIN_DEPS) $(MAIN_TARGET)
