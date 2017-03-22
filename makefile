# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -lreadline

# the build target executable:
TARGET = PolinomioCalc
LIBRARY = Monomio.h Monomio.c LinkedList.h LinkedList.c

#all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(LIBRARY) -o $(TARGET) $(TARGET).c $(CFLAGS)

clean:
	$(RM) $(TARGET)
