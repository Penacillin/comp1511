CC=gcc
CFLAGS= -c -Wall -Wextra -gdwarf-2 -std=c99
DEPS = captcha.h metrics.h preprocessors.h readers.h utilites.h data.h metric_calculator.h stats.h

OBJ = crack_captcha.o preprocessors.o copy_pixels.o  metrics.o print_image.o read_pbm.o utilities.o stack.o data.o metric_calculator.o

all: crack

crack: $(OBJ)
	$(CC)  $(OBJ) -o crack -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY : all clean

clean:
	rm -f *.o crack