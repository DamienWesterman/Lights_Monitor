####################################################################################################
# This file is part of a solution for Josh.ai's coding challenge.
#
# Applicant:    Damien Westerman
# Position:     C++ Developer
# File:         Makefile
# Description:  Build system for the project
#
####################################################################################################

STRIP_CMD := strip

SRC_DIR := ./src
OBJ_DIR := ./obj
INCLUDE_DIR := ./include

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
HEADERS := $(wildcard $(INCLUDE_DIR)/*.hpp)
TARGET := ./lights_monitor

CFLAGS += -I$(INCLUDE_DIR)
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wno-unknown-pragmas # Suppress unknown pragmas in cmdparser.hpp
CFLAGS += -std=c++14
ifeq (true,$(DEBUG))
CFLAGS += -DDEBUG
endif

.DEFAULT: run
.PHONY: run build clean help
.DELETE_ON_ERROR: clean help
run: build
	@echo "Running target..."
	@echo "=========================================================================\n\n\n"
	@$(TARGET) $(ARGS)

build: $(OBJ_DIR) $(TARGET)
	@chmod 711 $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(CFLAGS)
ifneq (true,$(DEBUG))
	$(STRIP_CMD) -s $@
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

help:
	@echo "****************************************************************"
	@echo "Damien's C++ Coding Challenge Solution Make System"
	@echo "****************************************************************"
	@echo
	@echo "Targets:"
	@echo "   make all   : compile all cpp files in src/ into ./lights_monitor"
	@echo "                and launch the project"
	@echo "   make build : compile all cpp files in src/ into ./lights_monitor"
	@echo "   make clean : cleans the project"
	@echo "   make help  : displays this screen"
	@echo
	@echo "Make Command Line Variables:"
	@echo "   DEBUG=true/false : False by default. True will leave debug info"
	@echo "                      in ./lights_monitor and enable extra logging"
	@echo "   ARGS='string'    : Arguments to pass to the executable if doing"
	@echo "                      'make run'"
