# root
# |- build
# |- include
# |- src
# directory structure vars
I_DIR=include
SRC_DIR=src
BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj
OBJ_D_DIR=$(BUILD_DIR)/objdebug
BIN_DIR=$(BUILD_DIR)

# default file extension
# SRC_EXT=C cc cpp CPP c++ cp cxx c # if you have multiple extensions at src/
SRC_EXT=cc
# H_EXT=H h++ hh hxx hpp

# remove command
rm=rm -Rf

# list all dirs directly inside the include dir
INCLUDES=$(sort $(dir $(wildcard $(foreach d,$(I_DIR),$d/*/))))
# SOURCES=$(foreach e,$(SRC_EXT),$(wildcard $(SRC_DIR)/*.$e)) # if you have multiple extensions at src/
# list all source files inside src
SOURCES=$(wildcard $(SRC_DIR)/*.$(SRC_EXT))
# creates a list of .o files using the files names from src
OBJECTS=$(SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
OBJECTS_D=$(SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_D_DIR)/%.o)

# compiler options and flags
CC=g++
CFLAGS=$(foreach d,$(INCLUDES),-I$d) -std=c++17 -Wall
CC_DEBUG_FLAGS=$(CFLAGS) -ggdb

# linker options and flags
LINKER=g++
LFLAGS=$(foreach d,$(INCLUDES),-I$d) -Wall -lm
L_DEBUG_LFLAGS=$(LFLAGS) -ggdb

# exe files
OUT=$(BIN_DIR)/out_test.out
OUT_DEBUG=$(BIN_DIR)/out_debug.out

# possible calls for make
.PHONY: clean debug run

# default call
doit: prep def

# run the default exe
run:
	./$(OUT) -r compact  -d yes

# rules for the default call
def:$(OUT)

$(OUT): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "==== Linking complete ===="

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.$(SRC_EXT)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "==== Compiled "$<" successfully ===="

# creates the build dir
prep:
	@mkdir -p $(BUILD_DIR) $(OBJ_DIR) $(OBJ_D_DIR) $(BIN_DIR)

# clear the build dir
clean:
	@$(rm) $(wildcard $(BIN_DIR)/*)
	@echo "Cleaned build dir"

# builds and link the debug exe
debug: prep $(OUT_DEBUG)

$(OUT_DEBUG): $(OBJECTS_D)
	@$(LINKER) $(OBJECTS_D) $(LFLAGS) -o $@
	@echo "==== Debug Linking complete ===="

$(OBJECTS_D): $(OBJ_D_DIR)/%.o : $(SRC_DIR)/%.$(SRC_EXT)
	$(CC) $(CC_DEBUG_FLAGS) -c $< -o $@
	@echo "==== Debug Compiled ===="
