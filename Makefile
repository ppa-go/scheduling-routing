# Seach for .c files in sources directory
vpath %.c sources

# Macro for compilation
CC=gcc
LD=gcc
EXEC=scheduling-routing
CCFLAGS=-g -Wall

all : $(EXEC) clean

$(EXEC) : main.o build_one_solution.o calculate_tardiness.o chrono.o find_first_group.o find_solution.o flowshop.o group.o instance.o input.o job.o mutation.o nearest_neighboor.o neh.o output.o routing.o site.o solution.o sort.o
	$(LD) $^ -o $@

%.o : %.c	
	$(CC) -c $< -o $@ $(CCFLAGS) 
		
clean :
	rm -rf *.o 
