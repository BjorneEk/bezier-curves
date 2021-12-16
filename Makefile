# $@ = target file
# $< = first dependency
# $^ = all dependencies

# detect all .o files based on their .c source

CC = gcc
INCLUDE_DIR = lib
CFLAGS = -F /Library/Frameworks -framework SDL2 -I$(INCLUDE_DIR)
C_SOURCES = $(wildcard $(INCLUDE_DIR)/*.c *.c)
DEPS = $(wildcard lib/*.h *.h)
OBJ = ${C_SOURCES:.c=.o}

# First rule is the one executed when no parameters are fed to the Makefile


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bezier: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	$(RM) *.bin *.o *.dis *.elf
	$(RM) lib/*.o
