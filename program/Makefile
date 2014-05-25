### Makefile ###

## Set up directories

SRC_DIR = sources
INC_DIR = headers
OBJ_DIR = obj
BIN_DIR = bin

## Define variables for compilation

CC = gcc
LD = gcc
EXEC = $(BIN_DIR)/program.exe
CCFLAGS = -g -Wall

## Define rules

# @ : nothing printed in the terminal

all : $(EXEC)

$(EXEC) : $(OBJ_DIR)/main.o $(OBJ_DIR)/build_one_solution.o $(OBJ_DIR)/calculate_tardiness.o $(OBJ_DIR)/chrono.o $(OBJ_DIR)/find_first_group.o $(OBJ_DIR)/find_solution.o $(OBJ_DIR)/flowshop.o $(OBJ_DIR)/group.o $(OBJ_DIR)/instance.o $(OBJ_DIR)/input.o $(OBJ_DIR)/job.o $(OBJ_DIR)/mutation.o $(OBJ_DIR)/nearest_neighbor.o $(OBJ_DIR)/neh.o $(OBJ_DIR)/output.o $(OBJ_DIR)/routing.o $(OBJ_DIR)/site.o $(OBJ_DIR)/solution.o $(OBJ_DIR)/sort.o
	@$(LD) $^ -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) -c $< -o $@ $(CCFLAGS)

# .PHONY : because the rule "clean" does not generate any file
.PHONY : clean
clean :
	@rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*.exe

